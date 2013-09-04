// =====================================================================================
// 
//       Filename:  GaloisFieldValue.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  2013/9/2 ¤U¤È 07:47:50
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Shuai YUAN (galoisplusplus), yszheda AT gmail DOT com
//        Company:  
// 
// =====================================================================================
#include "GaloisFieldValue.hpp"
#include <iostream>
#include <vector>
using namespace std;
//--------------------------------------------------------------------------------------
//       Class:  GaloisFieldValue
//      Method:  setup_tables
// Description:  setup log and exp tables
//--------------------------------------------------------------------------------------
template < unsigned int gf_width = 8 >
void 
GaloisFieldValue::setup_tables ()
{
		static_assert(gf_width <= 30, "Cannot handle width which is larger than 30!");
		unsigned int prim_poly = prim_poly_table[gf_width];
		int table_size = (1 << gf_width) - 1;
		int exp = 1;
		for (unsigned int i = 0; i < table_size; i++) {
				if (mask > table_size + 1) {
						break;
				}
				gf_log_table[exp] = i;
				gf_exp_table[i] = exp;
				exp = exp << 1;
				if (exp & table_size + 1) {
						exp = exp ^ prim_poly;
				}
		}

}

//--------------------------------------------------------------------------------------
//       Class:  GaloisFieldValue
//      Method:  operator =
// Description:  assignment operator
//--------------------------------------------------------------------------------------
template < unsigned int gf_width = 8 >
GaloisFieldValue<gf_width>&
GaloisFieldValue::operator = ( const GaloisFieldValue &other )
{
		if ( this != &other ) {
				gf_value = other.gf_value;
		}
		return *this;
}  // -----  end of method GaloisFieldValue::operator =  (assignment operator)  -----

//--------------------------------------------------------------------------------------
//       Class:  GaloisFieldValue
//      Method:  operator +=
// Description:  add assignment operator
//--------------------------------------------------------------------------------------
template < int gf_width = 8 >
GaloisFieldValue<gf_width>&
GaloisFieldValue::operator += ( const GaloisFieldValue<gf_width> &rhs )
{
		gf_value ^= rhs.gf_value; 	// XOR
		return *this;
}

//--------------------------------------------------------------------------------------
//       Class:  GaloisFieldValue
//      Method:  operator -=
// Description:  sub assignment operator
//--------------------------------------------------------------------------------------
template < unsigned int gf_width = 8 >
GaloisFieldValue<gf_width>&
GaloisFieldValue::operator -= ( const GaloisFieldValue<gf_width> &rhs )
{
//		operator+=(rhs);
		return (*this += other);
}

//--------------------------------------------------------------------------------------
//       Class:  GaloisFieldValue
//      Method:  operator *=
// Description:  mul assignment operator
//--------------------------------------------------------------------------------------
template < unsigned int gf_width = 8 >
GaloisFieldValue<gf_width>&
GaloisFieldValue::operator *= ( const GaloisFieldValue<gf_width> &rhs )
{
		if (this.gf_value == 0 || rhs.gf_value == 0) {
				gf_value = 0;
		} else {
			int gf_max_num = (1 << gf_width) - 1;
			int sum_log = gf_log_table[gf_value] + gf_log_table[rhs.gf_value];
			if (sum_log >= gf_max_num) {
					sum_log -= gf_max_num;
			}
			gf_value = gf_exp_table[sum_log];
		}
		return *this;
}

//--------------------------------------------------------------------------------------
//       Class:  GaloisFieldValue
//      Method:  operator /=
// Description:  div assignment operator
//--------------------------------------------------------------------------------------
template < unsigned int gf_width = 8 >
GaloisFieldValue<gf_width>&
GaloisFieldValue::operator /= ( const GaloisFieldValue<gf_width> &rhs )
{
		static_assert(rhs.gf_value != 0, "Cannot divide by zero!");
		if (this.gf_value == 0) {
				gf_value = 0;
		} else {
			int gf_max_num = (1 << gf_width) - 1;
			int diff_log = gf_log_table[gf_value] - gf_log_table[rhs.gf_value];
			if (diff_log < 0) {
					diff_log += gf_max_num;
			}
			gf_value = gf_exp_table[diff_log];
		}
		return *this;
}

//--------------------------------------------------------------------------------------
//       Class:  GaloisFieldValue
//      Method:  operator ^=
// Description:  pow assignment operator
//--------------------------------------------------------------------------------------
template < unsigned int gf_width = 8 >
GaloisFieldValue<gf_width>&
GaloisFieldValue::operator ^= ( const int &rhs )
{
		int gf_max_num = (1 << gf_width) - 1;
		int pow_log = (gf_log_table[gf_value] * rhs) % gf_max_num;
		gf_value = gf_exp_table[pow_log];
		return *this;
}
