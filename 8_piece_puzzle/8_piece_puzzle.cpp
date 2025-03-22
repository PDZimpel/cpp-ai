#include "matrix.h"
#include<cmath>
#include<map>
#include<algorithm>
#include<iostream>

struct node{

  Matrix m;
  int rank;
  int h;

  node(Matrix mat, int height) : m(mat), rank(0), h(height){}
};

int better_rank(const node& a, const node& b)
{
  return a.rank > b.rank ;
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
  return abs(x - x1) + abs(y - y1);
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
 n.rank += n.h + total;
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
      node new_node(m1, n.h + 1);
      total_manhattan_distance(new_node);
      result.push_back(new_node);
    }
  }

  return result;
}

bool is_goal(const Matrix&m) {
  return m.data[0][0] == 1 && m.data[0][1] == 2 && m.data[0][2] == 3 &&
         m.data[1][0] == 4 && m.data[1][1] == 5 && m.data[1][2] == 6 &&
         m.data[2][0] == 7 && m.data[2][1] == 8 && m.data[2][2] == 0;
}

int main(int argc, char ** argv)
{
  using namespace std;

  Matrix m = Matrix(3,3);
  int counter = 0;
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++, counter++)
      m.data[i][j] = (counter);

  cout << "the first node is: " << m.stringfy() << endl;

  map<std::string, bool> node_map;
  vector<node> heap;  

   node start(m, 0);
   total_manhattan_distance(start);
   std::make_heap(heap.begin(), heap.end(), better_rank);
   heap.push_back(start);
   std::make_heap(heap.begin(), heap.end(), better_rank);

  for(int i = 0; i < atoi(argv[1]); i++){
    pop_heap(heap.begin(), heap.end(), better_rank);
    node current = heap.back();
    heap.pop_back();

    if(is_goal(current.m)){
      cout << "Solution found: " << current.m.stringfy() << " with deph " << current.h << endl;
      return 0;
    }

    string curr_str = current.m.stringfy();
    if(node_map.find(curr_str) == node_map.end()){
      node_map[curr_str] = true;
      auto new_nodes = generate_nodes(current);
      for(auto& new_node : new_nodes) {
        string new_str = new_node.m.stringfy();
        if(node_map.find(new_str) == node_map.end()){
          heap.push_back(new_node);
          push_heap(heap.begin(), heap.end(), better_rank);
        }
      }
    }
  }
  
  cout << "not found solution "<< endl;
  return 0;
}
