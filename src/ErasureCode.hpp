// =====================================================================================
// 
//       Filename:  ErasureCode.hpp
// 
//    Description:  
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
using namespace std;
// =====================================================================================
//        Class:  ErasureCode
//  Description:  general erasure code
// =====================================================================================
class ErasureCode
{
		public:
				// ====================  LIFECYCLE     =======================================
				ErasureCode ();                             // constructor
				ErasureCode ( int gf_width, int in_chuck_num, int out_chuck_num );
				ErasureCode ( int gf_width, int in_chuck_num, int out_chuck_num, vector< vector<GaloisFieldValue<gf_width> > >& encoding_matrix );
				virtual ~ErasureCode ();                    // destructor

				// ====================  ACCESSORS     =======================================
				virtual bool check_recoverable ( long failure_state ) = 0;
				virtual int get_min_cost ( long failure_state ) = 0;

				// ====================  MUTATORS      =======================================

				// ====================  OPERATORS     =======================================


		protected:
				// ====================  DATA MEMBERS  =======================================
				int gf_width;		// the width of galois field
				int in_chuck_num;	// the number of input chucks
				int out_chuck_num;	// the number of output chucks
				vector< vector< GaloisFieldValue<gf_width> > > encoding_matrix;

		private:
				ErasureCode ( const ErasureCode &other );   // copy constructor
				ErasureCode ( ErasureCode &&other );   		// move constructor
				ErasureCode& operator = ( const ErasureCode &other ); // copy assignment operator
				ErasureCode& operator = ( ErasureCode &&other );      // move assignment operator
				// ====================  DATA MEMBERS  =======================================

}; // -----  end of class ErasureCode  -----

#endif   // ----- #ifndef ERASURECODE_H -----
