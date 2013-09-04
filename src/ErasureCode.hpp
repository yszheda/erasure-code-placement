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
#include <array>
#include "GaloisFieldValue.hpp"
#include "Array2D.hpp"
// using namespace std;

// =====================================================================================
//        Class:  ErasureCode
//  Description:  general erasure code
// =====================================================================================
// gf_width: the width of galois field
template < unsigned int gf_width = 8 >
class ErasureCode
{
		public:
				// ====================  LIFECYCLE     =======================================
//				ErasureCode ();                             // constructor
				ErasureCode ( int in_chunk_num, int out_chunk_num );
				ErasureCode ( int in_chunk_num, int out_chunk_num, Array2D< GaloisFieldValue<gf_width>, out_chunk_num, in_chunk_num >& encoding_matrix );
				virtual ~ErasureCode ();                    // destructor

				// ====================  ACCESSORS     =======================================
				virtual bool check_recoverable ( long failure_state ) = 0;
				virtual int get_min_cost ( long failure_state ) = 0;

				// ====================  MUTATORS      =======================================

				// ====================  OPERATORS     =======================================


		protected:
				// ====================  DATA MEMBERS  =======================================
				int in_chunk_num;	// the number of input chunks
				int out_chunk_num;	// the number of output chunks
				Array2D< GaloisFieldValue<gf_width>, out_chunk_num, in_chunk_num > encoding_matrix;

		private:
				ErasureCode ( const ErasureCode &other );   // copy constructor
				ErasureCode ( ErasureCode &&other );   		// move constructor
				ErasureCode& operator = ( const ErasureCode &other ); // copy assignment operator
				ErasureCode& operator = ( ErasureCode &&other );      // move assignment operator
				// ====================  DATA MEMBERS  =======================================

}; // -----  end of class ErasureCode  -----

#endif   // ----- #ifndef ERASURECODE_H -----
