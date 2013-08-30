// =====================================================================================
// 
//       Filename:  GaloisFieldValue.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  2013/8/30 下午 10:11:36
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
// =====================================================================================
//        Class:  GaloisFieldValue
//  Description:  
// =====================================================================================
class GaloisFieldValue
{
		public:
				// ====================  LIFECYCLE     =======================================
				GaloisFieldValue ();                             // constructor
				GaloisFieldValue ( const GaloisFieldValue &other );   // copy constructor
				GaloisFieldValue ( GaloisFieldValue &&other );   // move constructor
				~GaloisFieldValue ();                            // destructor

				// ====================  ACCESSORS     =======================================

				// ====================  MUTATORS      =======================================

				// ====================  OPERATORS     =======================================

				GaloisFieldValue& operator = ( const GaloisFieldValue &other ); // copy assignment operator
				GaloisFieldValue& operator = ( GaloisFieldValue &&other ); 		// move assignment operator
				bool operator == ( const GaloisFieldValue &other ); // assignment operator
				GaloisFieldValue operator + ( const GaloisFieldValue &lhs, const GaloisFieldValue &rhs );
				GaloisFieldValue operator - ( const GaloisFieldValue &lhs, const GaloisFieldValue &rhs );
				GaloisFieldValue operator * ( const GaloisFieldValue &lhs, const GaloisFieldValue &rhs );
				GaloisFieldValue operator / ( const GaloisFieldValue &lhs, const GaloisFieldValue &rhs );
				GaloisFieldValue operator ^ ( const GaloisFieldValue &lhs, const int &rhs );

		protected:
				// ====================  DATA MEMBERS  =======================================

		private:
				// ====================  DATA MEMBERS  =======================================
				int gf_width;		// the width of galois field
				int gf_value;		// the value of galois field poly
				vector<int> gf_log_table;
				vector<int> gf_exp_table;
				void setup_tables(int gf_width);

}; // -----  end of class GaloisFieldValue  -----



#endif   // ----- #ifndef GALOISFIELDVALUE_H  -----
