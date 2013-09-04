// =====================================================================================
// 
//       Filename:  LocalReconstructionCode.cpp
// 
//    Description:  Local Reconstruction Code (LRC) used by MS Azure
// 
//        Version:  1.0
//        Created:  2013/9/3 ¤U¤È 06:30:34
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Shuai YUAN (galoisplusplus), yszheda AT gmail DOT com
//        Company:  
// 
// =====================================================================================

#include <LocalReconstructionCode.hpp>

//--------------------------------------------------------------------------------------
//       Class:  LocalReconstructionCode
//      Method:  LocalReconstructionCode
// Description:  constructor
//--------------------------------------------------------------------------------------
LocalReconstructionCode::LocalReconstructionCode ( int in_chunk_num, int group_num, int global_parities_num ): 
		ErasureCode(in_chunk_num, in_chunk_num+group_num+global_parities_num), group_num(group_num), global_parities_num(global_parities_num)
{
}  // -----  end of method LocalReconstructionCode::LocalReconstructionCode  (constructor)  -----

//--------------------------------------------------------------------------------------
//       Class:  LocalReconstructionCode
//      Method:  LocalReconstructionCode
// Description:  constructor
//--------------------------------------------------------------------------------------
LocalReconstructionCode::LocalReconstructionCode ( int in_chunk_num, int group_num, int global_parities_num, vector< vector<GaloisFieldValue<LRC_gf_width> > > ): 
		ErasureCode(in_chunk_num, in_chunk_num+group_num+global_parities_num, encoding_matrix), group_num(group_num), global_parities_num(global_parities_num)
{
}  // -----  end of method LocalReconstructionCode::LocalReconstructionCode  (constructor)  -----

//--------------------------------------------------------------------------------------
//       Class:  LocalReconstructionCode
//      Method:  ~LocalReconstructionCode
// Description:  destructor
//--------------------------------------------------------------------------------------
LocalReconstructionCode::~LocalReconstructionCode ()
{
}  // -----  end of method LocalReconstructionCode::~LocalReconstructionCode  (destructor)  -----

//--------------------------------------------------------------------------------------
//       Class:  LocalReconstructionCode
//      Method:  update_failure_cnt
// Description:  
//--------------------------------------------------------------------------------------
void LocalReconstructionCode::update_failure_cnt( long failure_state )
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

// helper func
// need to be encapsulated

inline matrix_idx(int row, int col, int col_num)
{
		return row*col_num + col;
}

template < typename T >
bool check_invertable( int size, T* matrix )
{
		bool is_invertable = true;
		for (auto row = 0; row < size; row++) {
				int pivot_idx = -1;
				for (auto col = 0; col < size; col++) {
						if (matrix[ matrix_idx(row, col, size) ] != T(0)) {
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

template < typename T >
bool check_invertable( int size, vector< vector<T> >& matrix )
{
		bool is_invertable = true;
		for (auto row = 0; row < size; row++) {
				int pivot_idx = -1;
				for (auto col = 0; col < size; col++) {
						if (matrix[row][col] != T(0)) {
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


void gen_solver_matrix( int out_chunk_num, long failure_state, GaloisFieldValue<gf_width>* encoding_matrix, GaloisFieldValue<gf_width>* solver_matrix )
{

}


//--------------------------------------------------------------------------------------
//       Class:  LocalReconstructionCode
//      Method:  check_recoverable
// Description:  
//--------------------------------------------------------------------------------------
bool LocalReconstructionCode::check_recoverable( long failure_state )
{
		update_failure_cnt(failure_state);
		if (failure_cnt.total_cnt <= global_parities_num + 1) {
				return true;
		} else if (failure_cnt.total_cnt == global_parities_num + 2) {

		} else {
				return false;
		}
}

//--------------------------------------------------------------------------------------
//       Class:  LocalReconstructionCode
//      Method:  get_min_cost
// Description:  
//--------------------------------------------------------------------------------------
int LocalReconstructionCode::get_min_cost( long failure_state )
{
		int min_cost = 0;
		update_failure_cnt(failure_state);
		if (failure_cnt.global_parities_cnt > 0) {
				min_cost = in_chunk_num;
		} else {
				bool is_local_recovable = true;
				int failed_group = 0;
				for (auto i = 0; i < group_num; i++) {
						if (native_chunks_cnt[group_num] + local_parities_cnt[group_num] > 1) {
								is_local_recovable = false;
								min_cost = in_chunk_num;
						}
						if (native_chunks_cnt[group_num] + local_parities_cnt[group_num] > 0) {
								failed_group ++;
						}

				}
				if (is_local_recovable == true) {
						min_cost = failed_group * (in_chunk_num / group_num);
				}
		}
		return min_cost;
}
