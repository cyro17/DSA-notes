#include <iostream.h>
#include <vector>
using namespace std;

vector<int> spirallyTraverse(vector<vector<int> > &A, int r, int c){
	vector<int> res;
	int L = 0, R = c-1, T = 0, B=r-1;

	int i =0, dir =0;

	while(T<=B && L<=R){
		if(dir ==0){
			for (i = L; i <= R; i++)
				res.push_back(A[T][i]);
		}
		if(dir ==1){
			for (i = T; i <= B; i++)
				res.push_back(A[i][R]);
		}
		if(dir ==2){
			for (i = R; i >= L; i--)
				res.push_back(A[B][i]);
		}
		if(dir ==3){
			for (i = B; i >= T; i--)
				res.push_back(A[i][L]);
		}
		dir = (dir+1)%4;
	}
	return res;
}


int main()
{
	/* code */
	return 0;
}