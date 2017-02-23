#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;


vector<vector <bool>> readPizza(string file_name){
  int nrow, ncol, n_ingredients, max_ingredients;
  ifstream file( ("../test-data/" + file_name).c_str(), ifstream::in );
  char c;
  string line;

  file >> nrow;
  file >> ncol;
  file >> n_ingredients;
  file >> max_ingredients;

  vector<vector <bool>> pizza(nrow, vector<bool>(ncol));

  // Remove final endline
  file.get();
  
  for(int i=0; i < nrow; i++){
    for(int j=0; j < ncol; j++){
      file.get(c);
      pizza[i][j] = (c == 'T');
    }
    file.get();
  }


  return pizza;
}

int main(){
  cout <<  readPizza("small.in")[1][0];
}
