// =====================================================================================
// 
//       Filename:  Array2D.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  2013/9/4 ¤U¤È 11:39:05
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Shuai YUAN (galoisplusplus), yszheda AT gmail DOT com
//        Company:  
// 
// =====================================================================================

#ifndef  ARRAY2D_H
#define  ARRAY2D_H

#include <iostream>
#include <array>

// =====================================================================================
//        Class:  Array2D
//  Description:  
// =====================================================================================

template < typename T, int row_size, int col_size >
struct Array2D
{
		std::array< std::array<T, col_size>, row_size > value;
}; // -----  end of template class Array2D  -----

#endif   // ----- #ifndef ARRAY2D_H  -----
