// =====================================================================================
// 
//       Filename:  ErasureCode.cpp
// 
//    Description:  
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


ErasureCode::ErasureCode ( int gf_width, int in_chuck_num, int out_chuck_num, vector< vector<gf<gf_width> > > encoding_matrix ):gf_width(gf_width), in_chuck_num(in_chuck_num), out_chuck_num(out_chuck_num) {
		int row_num = encoding_matrix[0].size();
		int col_num = encoding_matrix.size();
//		static_assert(row_num == in_chuck_num, "Wrong encoding matrix row number!");
//		static_assert(col_num == out_chuck_num, "Wrong encoding matrix column number!");
		for ( auto i = 0; i < row_num ; i++ ) {
				for ( auto j = 0 ; j < col_num ; j++ ) {
						this.encoding_matrix[i][j] = encoding_matrix[i][j];
				}
		}
}
