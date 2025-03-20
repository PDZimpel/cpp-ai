#pragma once

#include <vector>
#include <array>
#include <string>
#include <iostream>
#include <sstream>

class Matrix
/*
 *  Class used for 8-piece puzzle ai algorithm solver. Will do swap operations,
 *  conversion for string and quick copying
 */
{
  
  private:

    int h, w; // height and width

  public:
    std::vector<std::vector<int>> data; // the matrix itself

    Matrix(int dimension): h(dimension), w(dimension), data(dimension, std::vector<int>(dimension)){
    }

    Matrix(int h, int w):
      h(h),
      w(w),
      data(h, std::vector<int>(w)){
    }

    Matrix(int h, int w, std::vector<std::vector<int>> m1):
      h(h),
      w(w),
      data(m1){
      }
 
    void inline swap(int x, int y, int x1, int y1)
    {
      if(x >= 0 && x < w && y >= 0 && y < h &&
        x1 >= 0 && x1 < w && y1 >= 0 && y1 < h)
        std::swap(data[x][y], data[x1][y1]);
    }

    std::array<int, 2> find_zero_coordinates() const
    {
      std::array<int, 2> result = {-1,-1};
      for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
          if(data[i][j] == 0){
            result[0] = i;
            result[1] = j;
            return result;
          }
        }
      }
      return result;
    }

    std::string stringfy()
    {
      std::ostringstream oss;
      for(const auto& row : data){
        for(int num : row){
          oss << num;
        }
        oss << " ";
      }
      return oss.str();
    }


};
