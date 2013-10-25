// =====================================================================================
// 
//       Filename:  ErasureCode.hpp
// 
//    Description:  base class for erasure codes   
// 
//        Version:  1.0
//        Created:  2013/8/27 下午 10:28:36
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Shuai YUAN (galoisplusplus), yszheda AT gmail DOT com
//        Company:  
// 
// =====================================================================================
#ifndef  ERASURECODE_H
#define  ERASURECODE_H

#include <iostream>
#include <vector>
#include "GaloisFieldValue.hpp"
// using namespace std;

// =====================================================================================
//        Class:  ErasureCode
//  Description:  general erasure code
// =====================================================================================
template < unsigned int gf_width = 8 >
class ErasureCode
{
		public:
				// ====================  LIFECYCLE     =======================================
//				ErasureCode ();                             // constructor
				ErasureCode ( int in_chunk_num, int out_chunk_num );
				ErasureCode ( int in_chunk_num, int out_chunk_num, vector<GaloisFieldValue<gf_width> > encoding_matrix );
				virtual ~ErasureCode ();                    // destructor

				// ====================  ACCESSORS     =======================================
				virtual bool check_recoverable ( long failure_state ) = 0;
				virtual int get_min_cost ( long failure_state ) = 0;

				virtual inline vector< GaloisFieldValue<gf_width> > get_encoding_matrix (  ) const
				{
						return encoding_matrix;
				}		// -----  end of method get_encoding_matrix  -----

				virtual inline void set_encoding_matrix ( vector< GaloisFieldValue<gf_width> > value )
				{
//						encoding_matrix	= value;
						std::copy(value.begin(), value.end(), encoding_matrix.begin() );
						return ;
				}		// -----  end of method set_encoding_matrix  -----
				
				// ====================  MUTATORS      =======================================

				// ====================  OPERATORS     =======================================


		protected:
				// ====================  DATA MEMBERS  =======================================
//				int gf_width;		// the width of galois field
				int in_chunk_num;	// the number of input chunks
				int out_chunk_num;	// the number of output chunks
				// NOTE: change the 2D array into a 1D vector is more convenient for memory management
				vector< GaloisFieldValue<gf_width> > encoding_matrix;

		private:
				ErasureCode ( const ErasureCode &other );   // copy constructor
				ErasureCode ( ErasureCode &&other );   		// move constructor
				ErasureCode& operator = ( const ErasureCode &other ); // copy assignment operator
				ErasureCode& operator = ( ErasureCode &&other );      // move assignment operator
				// ====================  DATA MEMBERS  =======================================

}; // -----  end of class ErasureCode  -----

#endif   // ----- #ifndef ERASURECODE_H -----
