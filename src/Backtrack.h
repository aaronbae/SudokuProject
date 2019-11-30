#ifndef BACKTRACK_H
#define BACKTRACK_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <cmath>
#include <string>
using namespace std;

class Backtrack
{
  public: 
    int squares_remaining; 
    int sqrtSize;
    int size;
    int** board;
    stack<int*> assignment_and_domain_changes; // maintains assignment and domain changes. length 3 [i , j , domain_value]
    map<pair<int, int>, bool*> domain;
    void print_board();
    void print_domain_size();

    Backtrack(int board_size, int** input_board);
    bool* get_domain(int i, int j);
    vector<int> get_domain_in_indices(int i, int j);
    bool check_domain(int i, int j, int value);
    void set_domain(int i, int j, int value, bool possible);
    int get_domain_size(int i, int j);

    int assign(int i, int j, int value);
    void revert_changes(int stack_index);

    bool within_box(int i, int j, int x, int y);
    bool relevant(int i, int j, int x, int y);
    bool is_consistent(int i, int j, int val);
    vector<pair<int, int>> get_neighbors(int i, int j);

    pair<int, int> select_unassigned_var(); // MRV 
    bool AC3(int i, int j);
    bool AC3_recurrent(int i, int j); // forward checking
    int number_of_eliminations(int i, int j, int value);
    vector<int> order_domain_vals(int i, int j); // Least Constraining Value

    bool backtrack();
};
#endif