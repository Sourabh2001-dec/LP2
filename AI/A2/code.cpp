#include <bits/stdc++.h>
using namespace std;

#define ROW 9
#define COL 10

typedef pair<int, int> Pair;

typedef pair<double, pair<int, int>> pPair;

struct cell
{
  int parent_i, parent_j;
  // f = g + h
  double f, g, h;
};

// A Utility Function to check whether given cell is in range of grid
bool isValid(int row, int col)
{
  return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

// A Utility Function to check whether the given cell is
// blocked or not
bool isUnBlocked(int grid[][COL], int row, int col)
{
  if (grid[row][col] == 1)
    return (true);
  else
    return (false);
}

// A Utility Function to check whether destination cell has
// been reached or not
bool isDestination(int row, int col, Pair dest)
{
  if (row == dest.first && col == dest.second)
    return (true);
  else
    return (false);
}

// A Utility Function to calculate the 'h' heuristic value.
double calculateHValue(int row, int col, Pair dest)
{
  // Return using the eucledian distance formula
  return ((double)sqrt(
      (row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second)));
}

// A Utility Function to trace the path from the source
// to destination
void tracePath(cell cellDetails[][COL], Pair dest)
{
  printf("\nThe Path is ");
  int row = dest.first;
  int col = dest.second;

  stack<Pair> Path;

  while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col))
  {
    Path.push(make_pair(row, col));
    int temp_row = cellDetails[row][col].parent_i;
    int temp_col = cellDetails[row][col].parent_j;
    row = temp_row;
    col = temp_col;
  }

  Path.push(make_pair(row, col));
  while (!Path.empty())
  {
    pair<int, int> p = Path.top();
    Path.pop();
    printf("-> (%d,%d) ", p.first, p.second);
  }

  return;
}

void aStarSearch(int grid[][COL], Pair src, Pair dest)
{
  // If the source is out of range
  if (isValid(src.first, src.second) == false)
  {
    printf("Source is invalid\n");
    return;
  }

  // If the destination is out of range
  if (isValid(dest.first, dest.second) == false)
  {
    printf("Destination is invalid\n");
    return;
  }

  // Either the source or the destination is blocked
  if (isUnBlocked(grid, src.first, src.second) == false || isUnBlocked(grid, dest.first, dest.second) == false)
  {
    printf("Source or the destination is blocked\n");
    return;
  }

  // If the destination cell is the same as source cell
  if (isDestination(src.first, src.second, dest) == true)
  {
    printf("We are already at the destination\n");
    return;
  }

  // Create a closed list and initialise it to false which means no cell is processed
  bool closedList[ROW][COL];
  memset(closedList, false, sizeof(closedList));

  // Declare a 2D array of structure to hold the details
  // of that cell
  cell cellDetails[ROW][COL];

  int i, j;

  for (i = 0; i < ROW; i++)
  {
    for (j = 0; j < COL; j++)
    {
      cellDetails[i][j].f = FLT_MAX;
      cellDetails[i][j].g = FLT_MAX;
      cellDetails[i][j].h = FLT_MAX;
      cellDetails[i][j].parent_i = -1;
      cellDetails[i][j].parent_j = -1;
    }
  }

  // Initialising the parameters of the starting node
  i = src.first, j = src.second;
  cellDetails[i][j].f = 0.0;
  cellDetails[i][j].g = 0.0;
  cellDetails[i][j].h = 0.0;
  cellDetails[i][j].parent_i = i;
  cellDetails[i][j].parent_j = j;

  // set is used because we need f with the minimum value and format is <f, <i, j>>
  // keep track of nodes that need to be examined
  set<pPair> openList;

  openList.insert(make_pair(0.0, make_pair(i, j)));

  // flag to check if the destination is found
  bool foundDest = false;

  while (!openList.empty())
  {
    pPair p = *openList.begin();

    // Remove this vertex from the open list
    openList.erase(openList.begin());

    // Add this vertex to the closed list
    i = p.second.first;
    j = p.second.second;
    closedList[i][j] = true;

    // To store the 'g', 'h' and 'f' of the 8 successors
    double gNew, hNew, fNew;

    // co-ordinates of the surrounding cells
    vector<vector<int>> coords = {
        {i - 1, j}, {i + 1, j}, {i, j + 1}, {i, j - 1}, {i - 1, j + 1}, {i - 1, j - 1}, {i + 1, j + 1}, {i + 1, j - 1}};

    for (int k = 0; k < coords.size(); k++)
    {
      int x = coords[k][0];
      int y = coords[k][1];
      if (isValid(x, y) == true)
      {
        // If the destination cell is the same as the
        // current successor
        if (isDestination(x, y, dest) == true)
        {
          // Set the Parent of the destination cell
          cellDetails[x][y].parent_i = i;
          cellDetails[x][y].parent_j = j;
          printf("The destination cell is found\n");
          tracePath(cellDetails, dest);
          foundDest = true;
          return;
        }

        // If the successor is already on the closed
        // list or if it is blocked, then ignore it.
        // Else do the following
        else if (closedList[x][y] == false && isUnBlocked(grid, x, y) == true)
        {
          gNew = cellDetails[i][j].g + (k > 3 ? 1.414 : 1.0);
          hNew = calculateHValue(x, y, dest);
          fNew = gNew + hNew;

          if (cellDetails[x][y].f == FLT_MAX || cellDetails[x][y].f > fNew)
          {
            openList.insert(make_pair(
                fNew, make_pair(x, y)));

            // Update the details of this cell
            cellDetails[x][y].f = fNew;
            cellDetails[x][y].g = gNew;
            cellDetails[x][y].h = hNew;
            cellDetails[x][y].parent_i = i;
            cellDetails[x][y].parent_j = j;
          }
        }
      }
    }
  }

  if (foundDest == false)
    printf("Failed to find the Destination Cell\n");

  return;
}

int main()
{
  /* Description of the Grid-
	1--> The cell is not blocked
	0--> The cell is blocked */
  int grid[ROW][COL] = {{1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
                        {1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
                        {1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
                        {0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
                        {1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
                        {1, 0, 1, 1, 1, 1, 0, 1, 0, 0},
                        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
                        {1, 1, 1, 0, 0, 0, 1, 0, 0, 1}};

  Pair src = make_pair(0, 8);

  Pair dest = make_pair(8, 0);

  aStarSearch(grid, src, dest);

  return (0);
}
