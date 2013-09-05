// =====================================================================================
// 
//       Filename:  demo.cpp
// 
//    Description:  replacement for LRC (demo)
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
#include <algorithm>
#include <vector>
#include <map>
#include <limits>
#include <cmath>
#include <cassert>
#include "GaloisFieldValue.hpp"
using namespace std;

//----------------------------------------------------------------------
//  Input
//----------------------------------------------------------------------
// erasure code parameter
// required node number
// int n;
// minimum decodable chuck number
// int k;
// normally it should contains n and k
// vector<int> param;

// LRC parameter
// parameter k
int in_chunk_num = 6;
int group_num = 2;
int global_parities_num = 2;
// parameter n
int out_chunk_num = in_chunk_num + group_num + global_parities_num;

// encoding matrix
const int gf_width = 4;
vector< GaloisFieldValue<gf_width> > encoding_matrix;

// total node number
int node_num = 20;
// node_num node availability vector
vector<double> avail(node_num);

// required system availability
double delta = 0.99;

//----------------------------------------------------------------------
//  Output
//----------------------------------------------------------------------
// optimal assignment vector
// store the corresponding chuck index for each node
// -1 for not assigned
vector<int> opt_assignment;

//----------------------------------------------------------------------
//  Variables
//----------------------------------------------------------------------
// recoverable failure and its min regeneration cost list
// up to 2^n
// <recoverable_failure_state, cost>
vector< pair<long, int> > recoverable_failure_cost_list;

// availability list of the n selected nodes
vector<double> selected_avail(out_chunk_num);

// failure counter
struct counter {
		int total_cnt = 0;
		int global_parities_cnt = 0;
		vector<int> local_parities_cnt = {0};
		vector<int> native_chunks_cnt = {0};
} failure_cnt;				// ----------  end of struct counter ----------


// ===  FUNCTION  ======================================================================
//         Name:  update_failure_cnt
//  Description:  update failure counter
// =====================================================================================
void update_failure_cnt( const long failure_state )
{	
		for (auto i = 0; i < out_chunk_num; i++) {
				if (failure_state & 0x01 == 1) {
						total_cnt ++;
						if (i < global_parities_num) {
								failure_cnt.global_parities_cnt ++;
						} else if (i < global_parities_num + group_num) {
								failure_cnt.local_parities_cnt[i - global_parities_num] = 1;
						} else {
								failure_cnt.native_chunks_cnt[i - global_parities_num - group_num] ++;
						}
				}
		}
}

/*
template < typename T >
bool check_invertable( int size, vector< T >& matrix )
{
    	bool is_invertable = true;
		for (auto row = 0; row < size; row++) {
				int pivot_idx = -1;
				for (auto col = 0; col < size; col++) {
						if (matrix[row * size + col] != T(0)) {
								pivot_idx = col;
								break;
						}
				}
				if (pivot_idx == -1) {
						is_invertable = false;
				}
		}
		return is_invertable;
}

void get_solver_matrix( long failure_state, vector< GaloisFieldValue<gf_width> > &encoding_matrix, vector< GaloisFieldValue<gf_width> > &slover_matrix )
{
}
*/

// ===  FUNCTION  ======================================================================
//         Name:  check_recovable
//  Description:  check whether the current failure state is recoverable
// =====================================================================================
bool check_recoverable( const long failure_state )
{
		bool is_recovable = false;
		update_failure_cnt(failure_state);
		if (failure_cnt.total_cnt <= global_parities_num + 1) {
				is_recoverable = true;
		} else if (failure_cnt.total_cnt == global_parities_num + 2) {
				// Currently work for LRC(6, 2, 2)
				if (failure_cnt.local_parities_cnt[0] == 1 && failure_cnt.local_parities_cnt[1] == 1) {
						if (failed_group.native_chunks_cnt[0] = 1 && failure_cnt.native_chunks_cnt[1] == 1) {
								is_recoverable = true;
						}
				} else if (failure_cnt.local_parities_cnt[0] == 1 || failure_cnt.local_parities_cnt[1] == 1) {
						int group_fail_cnt[2];
						group_fail_cnt[0] = failed_group.native_chunks_cnt[0] + failed_group.local_parities_cnt[0];
						group_fail_cnt[1] = failed_group.native_chunks_cnt[1] + failed_group.local_parities_cnt[1];
						if (group_fail_cnt[0] == 2 && group_fail_cnt[1] == 2) {
								is_recoverable = true;
						}
				} else if (failure_cnt.local_parities_cnt[0] == 0 && failure_cnt.local_parities_cnt[1] == 0) {
						if (failure_cnt.native_chunks_cnt[0] == 2 && failure_cnt.native_chunks_cnt[1] == 2) {
								is_recoverable = true;
						}
				}
		} 
		return is_recoverable;
}

// ===  FUNCTION  ======================================================================
//         Name:  get_min_cost
//  Description:  obtain the min cost for the current failure state
// =====================================================================================
int get_min_cost( const long failure_state )
{
		update_failure_cnt(failure_state);
		int min_cost = 0;
		if (failure_cnt.global_parities_cnt > 0) {
				min_cost = in_chunk_num;
		} else {
				bool is_local_recovable = true;
				int failed_group = 0;
				for (auto i = 0; i < group_num; i++) {
						if (failure_cnt.native_chunks_cnt[i] + failure_cnt.local_parities_cnt[i] > 1) {
								is_local_recovable = false;
								min_cost = in_chunk_num;
						}
						if (failure_cnt.native_chunks_cnt[i] + failure_cnt.local_parities_cnt[i] > 0) {
								failed_group ++;
						}

				}
				if (is_local_recovable == true) {
						min_cost = failed_group * (in_chunk_num / group_num);
				}
		}
		return min_cost;
}

// ===  FUNCTION  ======================================================================
//         Name:  gen_recoverable_failure_cost_list
//  Description:  generate the list of recoverable failure and its min cost
// =====================================================================================
void
gen_recoverable_failure_cost_list (  )
{
		long failure_state = 0;	// failure_state is a n-bit bitmap
		long max_failure_state = (1 << out_chunk_num) - 1;
		while ( failure_state <= max_failure_state ) {
				bool is_recoverable = check_recoverable(failure_state);
				if ( is_recoverable == true ) {
						int min_cost = get_min_cost(failure_state);
						pair<long, int> failure_cost_pair(failure_state, min_cost);
						recoverable_failure_cost_list.push_back(failure_cost_pair);
				}
				failure_state ++;
		}
		return ;
}


// ===  FUNCTION  ======================================================================
//         Name:  gen_selected_node_avail_list
//  Description:  generate the availability list of the selected nodes
// =====================================================================================
void
gen_selected_node_avail_list ( const vector<int>& assignment )
{
		for ( auto idx = 0; idx < assignment.size(); idx++ ) {
				int chuck_idx = assignment[idx];
				selected_avail[idx] = avail[chunk_idx];
		}
		return ;
}


// ===  FUNCTION  ======================================================================
//         Name:  get_system_avail
//  Description:  get the system availability according to the current assignment
// =====================================================================================
double
get_system_avail ( const vector<int>& assignment )
{
        gen_selected_node_avail_list(assignment);
		double system_avail = 0.0;
		for ( vector< pair<long, int> >::const_iterator it = recoverable_failure_cost_list.begin(); it != recoverable_failure_cost_list.end(); it++ ) {
				long failure_state = it->first;
				double failure_state_avail = 1;
				for ( auto i = 0; i < out_chunk_num ; i++ ) {
						if ( failure_state & 0x01 == 1 ) {
								failure_state_avail *= (1 - selected_avail[i]);
						} else {
								failure_state_avail *= selected_avail[i];
						}
						failure_state >>= 1;
				}
				system_avail += failure_state_avail;
		}
		return system_avail;
}		// -----  end of function get_system_avail  -----


// ===  FUNCTION  ======================================================================
//         Name:  get_total_cost
//  Description:  get total regeneration cost for the current assignment
// =====================================================================================
double
get_total_cost ( const vector<int>& assignment )
{
        gen_selected_node_avail_list(assignment);
		double total_cost = 0.0;
		for ( vector< pair<long, int> >::const_iterator it = recoverable_failure_cost_list.begin(); it != recoverable_failure_cost_list.end(); it++ ) {
				long failure_state = it->first;
				int failure_state_cost = it->second;
				double failure_state_avail = 1;
				for ( auto i = 0; i < out_chunk_num ; i++ ) {
						if ( failure_state & 0x01 == 1 ) {
								failure_state_avail *= (1 - selected_avail[i]);
						}
						else {
								failure_state_avail *= selected_avail[i];
						}
						failure_state >>= 1;
				}
				total_cost += failure_state_avail * failure_state_cost;
		}
		return total_cost;
}		// -----  end of function get_total_cost  -----


bool next_combination( const int total_size, const int subset_size, vector<int>&subset )
{
//		int i;
//		for (i = 0; i < subset_size-1; i++) {
//				if (subset[i+1] == subset[i] + 1) {
//						subset[i] = i + 1;
//				} else {
//						break;
//				}
//		}
//		if (total_size < subset[i] - 1) {
//		}
		if (subset[0] >= total_size - subset_size) {
				return false;
		}
		int pivot_idx;
		for (pivot_idx = subset_size-1; pivot_idx > 0; pivot_idx --) {
				if (a[pivot_idx] - pivot_idx < total_size - subset_size) {
						break;
				}
		}
		int pivot = subset[pivot_idx];
		for (auto i = pivot; i < subset_size; i++) {
				subset[pivot_idx] = ++pivot;
		}
		return true;
}


int
main ( int argc, char *argv[] )
{
//		SpecifiedCode someCode(param);
//		ErasureCode& code = someCode;
//		gen_recoverable_failure_list(code);
//		gen_min_cost_list(code);

		gen_recoverable_failure_cost_list();

		vector<int> assignment;
		for (i = 0; i < out_chunk_num; i++) {
				assignment[i] = i;
		}

		double min_total_cost = numeric_limits<double>::infinity();
		do {
			do {
					double system_avail = get_system_avail(assignment);
					// check whether the availability violates the SLA
					if ( system_avail >= delt ) {
							double total_cost = get_total_cost(assignment);
							if ( total_cost < min_total_cost ) {
									min_total_cost = total_cost;
        	                        opt_assignment = assignment;
							}
					}
			} while ( std::next_permutation(assignment.begin(), assignment.end()) );
		} while ( next_combination(node_num, out_chunk_num, assignment) )

		return EXIT_SUCCESS;
}				// ----------  end of function main  ----------

