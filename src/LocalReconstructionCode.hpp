// =====================================================================================
// 
//       Filename:  LocalReconstructionCode.hpp
// 
//    Description:  Local Reconstruction Code (LRC) used by MS Azure
// 
//        Version:  1.0
//        Created:  2013/9/2 ¤U¤È 09:26:43
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Shuai YUAN (galoisplusplus), yszheda AT gmail DOT com
//        Company:  
// 
// =====================================================================================

#ifndef  LOCALRECONSTRUCTIONCODE_H
#define  LOCALRECONSTRUCTIONCODE_H

#include <iostream>
#include <vector>
#include "GaloisFieldValue.hpp"
using namespace std;

const unsigned int LRC_gf_width = 4;
// =====================================================================================
//        Class:  LocalReconstructionCode
//  Description:  
// =====================================================================================
class LocalReconstructionCode: public ErasureCode<LRC_gf_width>
{
		public:
				// ====================  LIFECYCLE     =======================================
//				LocalReconstructionCode ();                             // constructor
				LocalReconstructionCode ( int in_chunk_num, int group_num, int global_parities_num );
				LocalReconstructionCode ( int in_chunk_num, int group_num, int global_parities_num, vector<GaloisFieldValue<LRC_gf_width> >& encoding_matrix );
				~LocalReconstructionCode ();                            // destructor

				// ====================  ACCESSORS     =======================================
				bool check_recoverable ( long failure_state );
				int get_min_cost ( long failure_state );

				//--------------------------------------------------------------------------------------
				//       Class:  LocalReconstructionCode
				//      Method:  get_encoding_matrix
				//--------------------------------------------------------------------------------------
				inline vector< GaloisFieldValue<LRC_gf_width> >
				get_encoding_matrix (  ) const
				{
						return encoding_matrix;
				}		// -----  end of method LocalReconstructionCode::get_encoding_matrix  -----

				//--------------------------------------------------------------------------------------
				//       Class:  LocalReconstructionCode
				//      Method:  set_encoding_matrix
				//--------------------------------------------------------------------------------------
				inline void
				set_encoding_matrix ( vector< GaloisFieldValue<LRC_gf_width> > value )
				{
//						encoding_matrix	= value;
						std::copy(value.begin(), value.end(), encoding_matrix.begin() );
						return ;
				}		// -----  end of method LocalReconstructionCode::set_encoding_matrix  -----
				
				// ====================  MUTATORS      =======================================

				// ====================  OPERATORS     =======================================

		protected:
				// ====================  DATA MEMBERS  =======================================

		private:
				LocalReconstructionCode ( const LocalReconstructionCode &other );   // copy constructor
				LocalReconstructionCode ( LocalReconstructionCode &&other );   // move constructor
				LocalReconstructionCode& operator = ( const LocalReconstructionCode &other ); // copy assignment operator
				LocalReconstructionCode& operator = ( LocalReconstructionCode &&other ); // move assignment operator
				void update_failure_cnt( long failure_state );
				// ====================  DATA MEMBERS  =======================================
				int group_num;
				int global_parities_num;
				struct counter {
						int total_cnt = 0;
						int global_parities_cnt = 0;
						int local_parities_cnt[group_num] = {0};
						int native_chunks_cnt[group_num] = {0};
				} failure_cnt;				// ----------  end of struct counter ----------

}; // -----  end of class LocalReconstructionCode  -----

#endif   // ----- #ifndef LOCALRECONSTRUCTIONCODE_H  -----
