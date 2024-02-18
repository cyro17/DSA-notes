/* 
TC => O(N! * N)
SC =-> O(N^2)
*/


class Solution {
public:

        bool check(int row, int col, vector<string> &board, int n ){
        int dupRow = row;
        int dupCol = col;

        // 1. check for upper left diagonal
        while(row>=0 && col>=0){
            if (board[row][col] == 'Q')
                return false;
            row-- ; col--;
        } 
        row = dupRow;
        col = dupCol;

        // 2. check for left 
        while(col>=0){
            if (board[row][col] == 'Q')
                return false;
            col--;
        } 
        row = dupRow;
        col = dupCol;

        // 3. check for lower left diagonal
        while(row<n && col>=0){
            if (board[row][col] == 'Q')
                return false;
            row++; col--;
        }
        return true;
    }
    void solve(int col, vector<string> &board, vector<vector<string>> &ans, int n){
        if(col == n){
            ans.push_back(board);
            return;
        }
        
        // 1. loop over the rows 
        for (int row = 0; row < n; ++row)
        {
            if(check(row, col, board, n)){
                board[row][col] = 'Q';
                solve(col+1, board, ans, n);

                // backtrack
                board[row][col] = '.';
            }
        }
    }



    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> board(n);
        string s(n, '.');

        for (int i = 0; i < n; ++i)
         {
             board[i] = s;
         }

         solve(0, board, ans, n);
         return ans;
    }

    

};