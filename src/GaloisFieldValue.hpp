// =====================================================================================
// 
//       Filename:  GaloisFieldValue.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  2013/8/30 下午 11:29:29
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Shuai YUAN (galoisplusplus), yszheda AT gmail DOT com
//        Company:  
// 
// =====================================================================================

#ifndef  GALOISFIELDVALUE_H
#define  GALOISFIELDVALUE_H
#include <iostream>
#include <vector>
using namespace std;
// =====================================================================================
//        Class:  GaloisFieldValue
//  Description:  
// =====================================================================================

template < int gf_width = 8 >
class GaloisFieldValue
{
		public:
				// ====================  LIFECYCLE     =======================================
				GaloisFieldValue (): gf_value(0) { setup_tables(); } // default constructor
				GaloisFieldValue ( int gf_value ): gf_value(gf_value) { setup_tables(); } // constructor
				GaloisFieldValue ( const GaloisFieldValue<gf_width> &other ): gf_value(other.gf_value) { }; // copy constructor
				~GaloisFieldValue () { };                          // destructor

				// ====================  ACCESSORS     =======================================

				// ====================  MUTATORS      =======================================

				// ====================  OPERATORS     =======================================

				GaloisFieldValue<gf_width>& operator = ( const GaloisFieldValue<gf_width> &other ); // copy assignment operator
				bool operator == ( const GaloisFieldValue<gf_width> &other ); 
				GaloisFieldValue<gf_width> operator + ( const GaloisFieldValue<gf_width> &rhs );
				GaloisFieldValue<gf_width> operator - ( const GaloisFieldValue<gf_width> &rhs );
				GaloisFieldValue<gf_width> operator * ( const GaloisFieldValue<gf_width> &rhs );
				GaloisFieldValue<gf_width> operator / ( const GaloisFieldValue<gf_width> &rhs );
				GaloisFieldValue<gf_width> operator ^ ( const int &rhs );

		protected:
				// ====================  DATA MEMBERS  =======================================

		private:
				GaloisFieldValue ( GaloisFieldValue<gf_width> &&other );   // move constructor
				GaloisFieldValue<gf_width>& operator = ( GaloisFieldValue<gf_width> &&other ); 		// move assignment operator
				// ====================  DATA MEMBERS  =======================================
				int gf_value;		// the value of galois field poly
				void setup_tables();

				static vector<int> gf_log_table;
				static vector<int> gf_exp_table;
				static int prim_poly_table[33] = 
				{ 0, 
				/*  1 */     1, 
				/*  2 */    07,
				/*  3 */    013,
				/*  4 */    023,
				/*  5 */    045,
				/*  6 */    0103,
				/*  7 */    0211,
				/*  8 */    0435,
				/*  9 */    01021,
				/* 10 */    02011,
				/* 11 */    04005,
				/* 12 */    010123,
				/* 13 */    020033,
				/* 14 */    042103,
				/* 15 */    0100003,
				/* 16 */    0210013,
				/* 17 */    0400011,
				/* 18 */    01000201,
				/* 19 */    02000047,
				/* 20 */    04000011,
				/* 21 */    010000005,
				/* 22 */    020000003,
				/* 23 */    040000041,
				/* 24 */    0100000207,
				/* 25 */    0200000011,
				/* 26 */    0400000107,
				/* 27 */    01000000047,
				/* 28 */    02000000011,
				/* 29 */    04000000005,
				/* 30 */    010040000007,
				/* 31 */    020000000011, 
				/* 32 */    00020000007 };  /* Really 40020000007, but we're omitting the high order bit */
				
				}; // -----  end of template class GaloisFieldValue  -----





#endif   // ----- #ifndef GALOISFIELDVALUE_H  -----
