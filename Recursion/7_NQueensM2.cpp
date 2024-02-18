/* 

Optimized approach => using Hashing 
                     we can optimize on space complexity 

TC => O(N! * N)
SC =-> O(N)
*/

class Solution {
private:
    void solve(int col, vector<string> &board, vector<vector<string>> &ans, int n,  vector<int> &leftRow,  
            vector<int> &upperDiag, vector<int> &lowerDiag){

        // base condn
        if(col == n){
            ans.push_back(board);
            return;
        }

        // 1. loop over the rows
        for (int row = 0; row < n; ++row)
        {
            if(leftRow[row] == 0 && 
                upperDiag[n-1 + col-row] == 0 &&
                lowerDiag[row + col] == 0)
            {
                    
                    board[row][col] = 'Q';
                    leftRow[row] = 1;
                    upperDiag[n-1 + col-row] =1;
                    lowerDiag[row + col] = 1;

                    solve(col+1, board, ans, n, leftRow, upperDiag, lowerDiag);

                    // backtrack
                    board[row][col] = '.';
                    leftRow[row] = 0;
                    upperDiag[n-1 + col-row] =0;
                    lowerDiag[row + col] = 0;
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> board(n);
        string s(n, '.');

        vector<int> leftRow(n, 0),
                    upperDiag(2*n-1, 0),
                    lowerDiag(2*n-1, 0);  

        for (int i = 0; i < n; ++i)
         {
             board[i] = s;
         }

         solve(0, board, ans, n, leftRow, upperDiag, lowerDiag);
         return ans;
    }
};