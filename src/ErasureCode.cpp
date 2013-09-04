// =====================================================================================
// 
//       Filename:  ErasureCode.cpp
// 
//    Description:  base class for erasure codes   
// 
//        Version:  1.0
//        Created:  2013/8/27 下午 10:55:45
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Shuai YUAN (galoisplusplus), yszheda AT gmail DOT com
//        Company:  
// 
// =====================================================================================
#include "ErasureCode.hpp"
#include <iostream>
#include <vector>
using namespace std;
//--------------------------------------------------------------------------------------
//       Class:  ErasureCode
//      Method:  ErasureCode
// Description:  constructor
//--------------------------------------------------------------------------------------
template < unsigned int gf_width = 8 >
ErasureCode::ErasureCode ( int in_chunk_num, int out_chunk_num ):gf_width(gf_width), in_chunk_num(in_chunk_num), out_chunk_num(out_chunk_num) {

}

//--------------------------------------------------------------------------------------
//       Class:  ErasureCode
//      Method:  ErasureCode
// Description:  constructor
//--------------------------------------------------------------------------------------
template < unsigned int gf_width = 8 >
ErasureCode::ErasureCode ( int in_chunk_num, int out_chunk_num, Array2D< GaloisFieldValue<gf_width>, out_chunk_num, in_chunk_num >& encoding_matrix ):gf_width(gf_width), in_chunk_num(in_chunk_num), out_chunk_num(out_chunk_num) {
		int row_num = encoding_matrix[0].size();
		int col_num = encoding_matrix.size();
//		static_assert(row_num == in_chunk_num, "Wrong encoding matrix row number!");
//		static_assert(col_num == out_chunk_num, "Wrong encoding matrix column number!");
		for ( auto i = 0; i < row_num ; i++ ) {
				for ( auto j = 0 ; j < col_num ; j++ ) {
						this.encoding_matrix[i][j] = encoding_matrix[i][j];
				}
		}
}

