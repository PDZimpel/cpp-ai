#include "matrix.h"
#include<cmath>
#include<map>
#include<algorithm>
#include<iostream>

struct node{

  Matrix m;
  int rank;

  node(Matrix mat, int r = 0) : m(mat), rank(r) {}
};

int better_rank(const node& a, const node& b)
{
  return a.rank > b.rank;
}

/*static Matrix solve = {{1,2,3},
                      {4,5,6},
                      {7,8,0}};

static Matrix init = {{0,1,2},
                     {3,4,5},
                     {6,7,8}}
*/

inline int distance(int x, int y, int x1, int y1)
{
  return abs(x - x1) + (y - y1);
}

void total_manhattan_distance(node& n)
{ //this is so cringe
 int total = 0;
 for(int i= 0 ; i < 3; i++){
   for(int j = 0; j < 3; j++){
     int value = n.m.data[i][j];
     if( value != 0 ){
        int target_x = (value - 1) / 3;
        int target_y = (value - 1) % 3;
        total += distance(i, j, target_x, target_y);
     }
   }
 }
 n.rank += total;
}

std::vector<node> generate_nodes(node& n)
{
  std::vector<node> result;
  std::array<int, 2> zeroC = n.m.find_zero_coordinates();
  int x = zeroC[0], y = zeroC[1];
  std::vector<std::pair<int,int>> moves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; 

  for( auto [dx, dy] : moves ){
    int nx = x + dx, ny = y + dy;
    if(nx >= 0 && nx < 3 && ny >=0 && ny < 3){
      Matrix m1 = n.m;
      m1.swap(nx, ny, x, y);
      node new_node(m1);
      total_manhattan_distance(new_node);
      result.push_back(new_node);
    }
  }

  return result;
}

int main(int argc, char ** argv)
{
  using namespace std;

  Matrix m = Matrix(3,3);
  int counter = 0;

  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++, counter++)
      m.data[i][j] = (counter%9);

  std::cout << "the first node is: " << m.stringfy() << std::endl;
  map<std::string, bool> node_map;
  node n(m);
  vector<node> heap;  

  for(int i = 0; i < atoi(argv[1]); i++){
    node_map[n.m.stringfy()] = true;

    auto new_nodes = generate_nodes(n);
    heap.insert(heap.end(), new_nodes.begin(), new_nodes.end());

    std::make_heap(heap.begin(), heap.end(), better_rank);

    while(!heap.empty()){
      std::pop_heap(heap.begin(), heap.end(), better_rank);
      n = heap.back();
      heap.pop_back();
      if(node_map[n.m.stringfy()]) {
        continue;
      }
      break;
    }
  }
  
  std::cout << "the final result is: " << n.m.stringfy() << std::endl;

  return 0;
}
