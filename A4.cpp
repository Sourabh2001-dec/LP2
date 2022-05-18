// N Queens
#include <bits/stdc++.h>
using namespace std;

void printBoard(vector<string> &board)
{
    for (auto row : board)
    {
        cout << row << endl;
    }
    cout << "\n";
}

void solve(int col, vector<string> &board, vector<int> &leftRow, vector<int> &upperDiagonal, vector<int> &lowerDiagonal, int n)
{
    if (col == n)
    {
        printBoard(board);
        return;
    }

    for (int row = 0; row < n; row++)
    {
        if (leftRow[row] == 0 && lowerDiagonal[row + col] == 0 && upperDiagonal[(n - 1) + (col - row)] == 0)
        {
            board[row][col] = 'Q';

            leftRow[row] = 1;

            lowerDiagonal[row + col] = 1;

            upperDiagonal[(n - 1) + (col - row)] = 1;

            solve(col + 1, board, leftRow, upperDiagonal, lowerDiagonal, n);

            board[row][col] = '.';

            leftRow[row] = 0;

            lowerDiagonal[row + col] = 0;

            upperDiagonal[(n - 1) + (col - row)] = 0;
        }
    }
}

void solveNQueens(int n)
{
    vector<string> board(n);
    string s(n, '.');
    for (int i = 0; i < n; i++)
    {
        board[i] = s;
    }
    vector<int> leftRow(n, 0), upperDiagonal(2 * n - 1, 0), lowerDiagonal(2 * n - 1, 0);
    solve(0, board, leftRow, upperDiagonal, lowerDiagonal, n);
}

int main(int argc, char const *argv[])
{
    cout.tie(0);

    solveNQueens(10);

    return 0;
}
