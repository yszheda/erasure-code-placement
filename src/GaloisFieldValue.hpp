// =====================================================================================
// 
//       Filename:  GaloisFieldValue.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  2013/8/30 ¤U¤È 10:11:36
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Shuai YUAN (galoisplusplus), yszheda AT gmail DOT com
//        Company:  
// 
// =====================================================================================

#ifndef  GALOISFIELDVALUE_H
#define  GALOISFIELDVALUE_H
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
				~GaloisFieldValue ();                            // destructor

				// ====================  ACCESSORS     =======================================

				// ====================  MUTATORS      =======================================

				// ====================  OPERATORS     =======================================

				GaloisFieldValue& operator = ( const GaloisFieldValue &other ); // assignment operator

		protected:
				// ====================  DATA MEMBERS  =======================================

		private:
				// ====================  DATA MEMBERS  =======================================

}; // -----  end of class GaloisFieldValue  -----



#endif   // ----- #ifndef GALOISFIELDVALUE_H  -----
