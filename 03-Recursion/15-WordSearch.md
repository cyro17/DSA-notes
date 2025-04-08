> TC = O(N * M * 4^L) 
> SC = O(L), recursive stack space which is equal to the length of the word (L).
 
```
class Solution {
private:
    bool dfs(int row, int col, int n, int m, int strIndex, 
        vector<vector<char>>& board, string word, vector<vector<bool>> &vis){

        vector<int> delRow = {0, -1, 0, +1};
        vector<int> delCol = {-1, 0, 1, 0};

        if(strIndex == word.size()) return 1;
        if(row< 0 || col < 0 || row >= n || col >= m || board[row][col] != word[strIndex] 
            || vis[row][col] ) 
            return 0;

        vis[row][col] = 1;

        for (int i = 0; i < 4; ++i)
        {
            int nr = row + delRow[i];
            int nc = col + delCol[i];

            if(dfs(nr , nc, n, m, strIndex + 1, board, word, vis)) return 1;
        }
       
        return 0;
    }

public:

    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size(), m = board[0].size();
        vector<vector<bool>> vis(n, vector<bool>(m, 0));

        for(int i = 0; i<n; i++){
            for(int j = 0; j < m; j++){
                if(board[i][j] == word[0])
                    if(dfs(i, j, n, m, 0, board, word, vis))
                        return 1;
            }
        }
        return 0;
    };
    
};


```
