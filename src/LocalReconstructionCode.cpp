// =====================================================================================
// 
//       Filename:  LocalReconstructionCode.cpp
// 
//    Description:  Local Reconstruction Code (LRC) used by MS Azure
// 
//        Version:  1.0
//        Created:  2013/9/3 �U�� 06:30:34
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
LocalReconstructionCode::LocalReconstructionCode ( int in_chunk_num, int group_num, int global_parities_num, vector<GaloisFieldValue<LRC_gf_width> > ): 
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
