#include "Backtrack.h"

void Backtrack::print_board()
{
  cout << "-----------------------------------------" << endl;
  int divider = sqrt(size);
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
    {
      string temp = to_string(board[i][j]);
      if(temp.length() == 1)
      {
        cout << " " << board[i][j] << " ";
      } else 
      {
        // Empty spaces are *
        if(board[i][j] == -1)
        {
          cout << " * ";
        } else 
        {
          cout << board[i][j] << " ";
        }
      }
      // Column divider
      if(j % divider == divider - 1)
      {
        cout << "  ";
      }
    }
    cout << endl;
    // Row divider
    if(i % divider == divider - 1)
    {
      cout << endl;
    }
  }
}

void Backtrack::print_domain_size()
{
  cout << "-----------------------------------------" << endl;
  int divider = sqrt(size);
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
    {
      int val = get_domain_size(i,j);
      string temp = to_string(val);
      if(temp.length() == 1)
      {
        cout << " " << val << " ";
      } else 
      {
        cout << val << " ";
      }
      // Column divider
      if(j % divider == divider - 1)
      {
        cout << "  ";
      }
    }
    cout << endl;
    // Row divider
    if(i % divider == divider - 1)
    {
      cout << endl;
    }
  }
  cout << "-----------------------------------------" << endl;
}

Backtrack::Backtrack(int board_size, int** input_board)
{
  sqrtSize = (int) sqrt(board_size);
  size = board_size;
  squares_remaining = size * size;
  assignment_and_domain_changes = stack<int*>();
  board = new int*[size];
  for(int i = 0; i < size; i++)
  {
    board[i] = new int[size];
    for(int j = 0; j < size; j++)
    {
      int val = input_board[i][j];
      board[i][j] = val;
      if(val != -1)
      {
        squares_remaining -= 1;
      }

      pair<int, int> coord(i,j);
      bool* empty_domain = new bool[size];
      for(int k = 0; k < size; k++)
      {
        empty_domain[k] = (k == val) || (val == -1);
      }
      domain[coord] =  empty_domain;
      
    }
  }
  // Init AC3
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
    {
      AC3(i, j);
    }
  }
}
bool* Backtrack::get_domain(int i, int j)
{
  bool* old_domain = domain[pair<int, int>(i,j)];
  bool* new_domain = new bool[size];
  for(int k = 0; k < size; k++)
  {
    new_domain[k] = old_domain[k];
  }
  return new_domain;
}
vector<int> Backtrack::get_domain_in_indices(int i, int j)
{
  vector<int> indices;
  bool* temp_domain = get_domain(i, j);
  for(int k = 0; k < size; k++)
  {
    if(temp_domain[k])
    {
      indices.push_back(k);
    }
  }
  return indices;
}
bool Backtrack::check_domain(int i, int j, int value)
{
  return domain[pair<int, int>(i,j)][value];
}
void Backtrack::set_domain(int i, int j, int value, bool possible)
{
  domain[pair<int, int>(i,j)][value] = possible;
  assignment_and_domain_changes.push(new int[3]{i, j, value});
}
void Backtrack::revert_changes(int stack_index)
{
  while(stack_index < assignment_and_domain_changes.size())
  {
    int* d_change = assignment_and_domain_changes.top();
    int i = d_change[0];
    int j = d_change[1];
    int k = d_change[2];
    if(k == -1)
    {
      // revert value assignment 
      board[i][j] = -1;
      squares_remaining += 1;
    }
    else
    {
      // revert domain change
      bool curr_val = domain[pair<int, int>(i, j)][k];
      domain[pair<int, int>(i, j)][k] = !curr_val;

    }  
    assignment_and_domain_changes.pop();
  }
}
int Backtrack::assign(int i, int j, int value)
{
  cout << "ASSIGN "<< i << " , "<< j<< endl;
  int stack_index = assignment_and_domain_changes.size();
  board[i][j] = value;
  squares_remaining -= 1;
  // we actually don't need to know the value it changed to
  assignment_and_domain_changes.push(new int[3]{i, j, -1});
  for(int k = 0; k < size; k++)
  {
    if(k != value)
    {
      set_domain(i, j, k, false);
    } 
    else {
      set_domain(i, j, k, true);
    }
  }
  return stack_index;
}
int Backtrack::get_domain_size(int i, int j)
{
  int total = 0;
  bool* temp_domain = get_domain(i,j);
  for(int k = 0; k < size; k++)
  {
    total += temp_domain[k];
  }
  return total;
}

bool Backtrack::within_box(int i, int j, int x, int y)
{
  int rowIndex = (int) i/sqrtSize;
  int colIndex = (int) j/sqrtSize;
  bool rowTest = rowIndex * sqrtSize <= x && x < (rowIndex + 1) * sqrtSize;
  bool colTest = colIndex * sqrtSize <= y && y < (colIndex + 1) * sqrtSize;
  return rowTest && colTest;
}
bool Backtrack::relevant(int i, int j, int x, int y)
{
  return x == i || y == j || within_box(i, j, x, y);
}
bool Backtrack::is_consistent(int i, int j, int val)
{
  for(int x = 0; x < size; x++)
  {
    for(int y = 0; y < size; y++)
    {
      if(val == board[x][y] && relevant(i, j, x, y))
      {
        return false;
      }
    }
  }
  return true;
}
vector<pair<int, int>> Backtrack::get_neighbors(int i, int j)
{
  vector<pair<int, int>> neighbors;
  for(int x = 0; x < size; x++)
  {
    for(int y = 0; y < size; y++)
    {
      if(board[x][y] == -1 && relevant(i, j, x, y) && (x != i || y != j))
      {
        neighbors.push_back(pair<int, int>(x,y));
      }
    }
  }
  return neighbors;
}
pair<int, int> Backtrack::select_unassigned_var()
{
  pair<int, int> best(-1, -1);
  int smallest_domain_size = size + 1; // arbitrarily size + 1
  for( auto const& [key, val] : domain )
  { 
    int current_domain_size = get_domain_size(key.first, key.second);
    if(current_domain_size < smallest_domain_size && current_domain_size > 1)
    {
      smallest_domain_size = current_domain_size;
      best = key;
    }
  }
  return best;
} 
bool Backtrack::AC3(int i, int j)
{
  // if the value is unassigned at (i,j), skip
  bool current_i_j_value_arc_consistent = true;
  if(board[i][j] == -1)
  {
    return current_i_j_value_arc_consistent;
  }
  int this_val = board[i][j];
  vector<pair<int, int>> neighbors = get_neighbors(i, j);
  // iterate through all the neighbors
  for(auto  n : neighbors)
  {
    int x = n.first;
    int y = n.second;
    // find domain values that work for the neighbor
    bool domain_changed = check_domain(x, y, this_val);
    set_domain(x, y, this_val, false);

    if(get_domain_size(x, y) == 0)
    {
      return false; // need to backtrack
    }
    else if(get_domain_size(x, y) == 1)
    {
      int only_possible_value = get_domain_in_indices(x,y)[0];
      cout << "AC3 ";
      assign(x, y, only_possible_value);
      AC3(x, y);
    }

    // forward checking
    if(domain_changed)
    {
      //current_i_j_value_arc_consistent = AC3_recurrent(x, y); 
    }
  }
  return current_i_j_value_arc_consistent; // green light to next assignment
}
bool Backtrack::AC3_recurrent(int i, int j)
{
  // not implemented
}
int Backtrack::number_of_eliminations(int i, int j, int value)
{
  int total_elimination = 0;
  vector<pair<int, int>> neighbors = get_neighbors(i, j);
  for(auto p : neighbors)
  {
    if(check_domain(p.first, p.second, value))
    {
      total_elimination += 1;
    }
  }
  return total_elimination;
}
vector<int> Backtrack::order_domain_vals(int i, int j)
{
  vector<int> domain_values = get_domain_in_indices(i, j);

  // stack the domain values and elimination values
  vector<pair<int, int>> domain_and_elimination_values;
  for(auto d_value : domain_values)
  {
    domain_and_elimination_values.push_back(pair<int, int>(d_value, number_of_eliminations(i,j,d_value)));
  }
  // sort by bigger elimination value
  sort(domain_and_elimination_values.begin(), domain_and_elimination_values.end(), [](pair<int, int> p1, pair<int, int> p2){
    return p1.second > p2. second;
  });
  // reconstruct domain values from the sorted stacked values
  vector<int> orderd_domain_values;
  for(auto p : domain_and_elimination_values)
  {
    orderd_domain_values.push_back(p.first);
  }
  return orderd_domain_values;
}
bool Backtrack::backtrack()
{
  pair<int, int> temp = select_unassigned_var();
  int i = temp.first;
  int j = temp.second;
  // full board
  if(i == -1 && j == -1)
  {
    return true;
  }
  vector<int> orderd_domain = order_domain_vals(i, j);
  for(auto potential_assignment: orderd_domain)
  {
    if(is_consistent(i, j, potential_assignment))
    { 
      bool* old_domain = get_domain(i, j);
      cout << "BACKTRACK ";
      int stack_revert_index = assign(i, j, potential_assignment);
      if(AC3(i, j))
      {
        print_board();
        //print_domain_size();
        //string nothingimportant;
        //cin >> nothingimportant;
        bool result = backtrack();
        if(result)
        {
          return result;
        }
      }
      revert_changes(stack_revert_index);
    }
    else
    {
      set_domain(i, j, potential_assignment, false);
    }
  }
  return false;
}