#include <climits>
#include<vector>
using namespace std;

class Solution
{
	public:
		int matrixMultiplication(int N, int arr[])
		{
		//const int N = nums.size();
		int** val = new int* [N];
		const int M = N-1;// No of matrix.
		for(int i=0; i<N; i++)
		{
			val[i] = new int [N];
			for(int j=0; j<N; j++)
			{
				if(i == j)
					val[i][j] = 1;
				else
					val[i][j] = INT_MAX;
			}
		}
		for(int i=1; i<M; i++)
		{
			val[i][i+1] = arr[i-1] * arr[i] * arr[i+1];
		}

		for(int gap = 2; gap <M; gap++)
		{
			for(int i=1; i+gap<=M; i++)
			{
				int j = i+gap;
				for(int k=i; k<j; k++)
				{
					int tmp = val[i][k] * arr[k] * val[k+1][j];
					if(tmp < val[i][j])
						val[i][j] = tmp;
				}
			}
		}
		int ret_val = val[1][M];
		for(int i = 0; i<N; i++)
		{
			delete [] val[i];
		}
		delete [] val;
		return ret_val;
	}
};
