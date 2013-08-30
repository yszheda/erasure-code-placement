// =====================================================================================
// 
//       Filename:  naive.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  2013/8/26 下午 08:33:37
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Shuai YUAN (galoisplusplus), yszheda AT gmail DOT com
//        Company:  
// 
// =====================================================================================
#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <cmath>

using namespace std;

//----------------------------------------------------------------------
//  Input
//----------------------------------------------------------------------
// erasure code parameter
// normally it should contains n and k
vector<int> param;
// required node number
int n;
// minimum decodable chuck number
int k;
// encoding matrix
// int width;
// gf<int> should be a template class
vector< vector< gf<gf_width> > > encoding_matrix;
// total node number
int N;
// N node availability vector
vector<double> avail(N);
// required system availability
double delta;

//----------------------------------------------------------------------
//  Output
//----------------------------------------------------------------------
// optimal assignment vector
// store the corresponding chuck index for each node
// -1 for not assigned
vector<int> opt_assignment(N);

//----------------------------------------------------------------------
//  Variables
//----------------------------------------------------------------------
// failure status
// bool is_failed[N];
// recoverable failure list
// up to 2^n
vector<long> recoverable_failure_list;
// min regeneration cost list
// <recoverable_failure_state, cost>
map<long, int> min_cost_list;
// availability list of the n selected nodes
vector<double> selected_avail(n);

// ===  FUNCTION  ======================================================================
//         Name:  gen_recoverable_failure_list
//  Description:  
// 	Input: 
// 	erasure code parameter
// 	encoding matrix
// 	Output: 
// 	recoverable_failure_list
// =====================================================================================
void
gen_recoverable_failure_list ( const ErasureCode& code )
{
		long failure_state = 1;	// failure_state is a n-bit bit vector
		long max_failure_state = (1 << n) - 1;
		while ( failure_state <= max_failure_state ) {
				// check whether the failure can be recovered through the encoding matrix
				bool is_recoverable = code.check_recoverable(failure_state);
				if ( is_recoverable == true ) {
						recoverable_failure_list.push_back(failure_state);
				}
				failure_state ++;
		}
		return ;
}		// -----  end of function gen_recoverable_failure_list  -----



// ===  FUNCTION  ======================================================================
//         Name:  gen_min_regeneration_cost_list
//  Description:  
// Input: 
// erasure code parameter
// encoding matrix
// recoverable_failure_list
// Output: 
// min_cost_list
// =====================================================================================
void
gen_min_cost_list ( const ErasureCode& code )
{
		for ( vector<long>::const_iterator it = recoverable_failure_list.begin(); it != recoverable_failure_list.end(); it++ ) {
				long failure_state = (*it);
				double min_cost = code.get_min_cost(failure_state);
				min_cost_list[failure_state] = min_cost;
		}
		return ;
}		// -----  end of function gen_min_regeneration_cost_list  -----


// ===  FUNCTION  ======================================================================
//         Name:  gen_selected_node_avail_list
//  Description:  
// Input: 
// N node availability vector
// assignment vector
// Output: 
// selected_avail
// =====================================================================================
void
gen_selected_node_avail_list ( vector<int>& assignment )
{
		for ( auto idx = 0; idx < N; idx++ ) {
				if ( assignment[idx] > 0 ) {
						int chuck_idx = static_cast<int>( log2(assignment[idx]) );
						static_assert(chuck_idx < n, "Wrong chuck_idx!");
						selected_avail[chuck_idx] = avail[idx];
				}
		}
		return ;
}		// -----  end of function gen_selected_node_avail_list  -----


// ===  FUNCTION  ======================================================================
//         Name:  get_system_avail
//  Description:  
// Input: 
// recoverable_failure_list
// N node availability vector
// assignment vector
// Output: 
// system availability
// =====================================================================================
double
get_system_avail ( vector<int>& assignment )
{
		double system_avail = 0.0;
        gen_selected_node_avail_list(assignment);
		for ( vector<long>::const_iterator it = recoverable_failure_list.begin(); it != recoverable_failure_list.end(); it++ ) {
				long failure_state = (*it);
				double failure_state_avail = 1;
				for ( auto i = 0; i < n ; i++ ) {
						if ( failure_state & 0x01 == 1 ) {
								failure_state_avail *= (1 - selected_avail[i]);
						} else {
								failure_state_avail *= selected_avail[i];
						}
				}
				system_avail += failure_state_avail;
		}
		return system_avail;
}		// -----  end of function get_system_avail  -----


// ===  FUNCTION  ======================================================================
//         Name:  get_total_cost
//  Description:  
// Input: 
// min_cost_list
// N node availability vector
// assignment vector
// Output: 
// total_regeneration_cost
// =====================================================================================
double
get_total_cost ( vector<int>& assignment )
{
		double total_cost = 0.0;
        gen_selected_node_avail_list(assignment);
		for ( map<long, int>::const_iterator it = min_cost_list.begin(); it != min_cost_list.end(); it++ ) {
				long failure_state = it->first;
				double failure_state_cost = it->second;
				double failure_state_avail = 1;
				for ( auto i = 0; i < n ; i++ ) {
						if ( failure_state & 0x01 == 1 ) {
								failure_state_avail *= (1 - selected_avail[i]);
						}
						else {
								failure_state_avail *= selected_avail[i];
						}
				}
				total_cost += failure_state_avail * failure_state_cost;
		}
		return total_cost;
}		// -----  end of function get_total_cost  -----



int
main ( int argc, char *argv[] )
{
		SpecifiedCode someCode(param);
		ErasureCode& code = someCode;
		gen_recoverable_failure_list(code);
		gen_min_cost_list(code);

		double min_total_cost = numeric_limits<double>::infinity();
        vector<int> assignment(N);
//      vector<int> opt_assignment(N);
        foreach combination of assignment
		{
				double system_avail = get_system_avail();
				// check whether the availability violates the SLA
				if ( system_avail >= delt ) {
						double total_cost = get_total_cost();
						if ( total_cost < min_total_cost ) {
								min_total_cost = total_cost;
                                opt_assignment = assignment;
						}
				}
		}

		return EXIT_SUCCESS;
}				// ----------  end of function main  ----------

