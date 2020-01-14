// 2020-01-14
// algospot TRIANGLEPATH
// https://algospot.com/judge/problem/read/TRIANGLEPATH

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>

using namespace std;

// 캐쉬
int cache[101][101];

// 재귀적 함수
int findMax1(const vector<vector<int>>& board, int x, int y)
{
	int n = board.size() - 1;

	if (x > n || y > n || x < y)
		return 0;

	int ret = 0;

	ret = max(board[x][y] + findMax1(board, x + 1, y), 
		      board[x][y] + findMax1(board, x + 1, y + 1));

	return ret;
}

// 재귀적 구현 + 메모이제이션
int findMax2(const vector<vector<int>>& board, int x, int y)
{
	int n = board.size() - 1;

	if (x == n)
		return board[x][y];

	if (cache[x][y] != -1)
		return cache[x][y];

	int ret = 0;

	ret = max(board[x][y] + findMax2(board, x + 1, y),
		board[x][y] + findMax2(board, x + 1, y + 1));

	return cache[x][y] = ret;
}

int main()
{
	// 테스트 케이스, 라인수, 입력 숫자
	int C, n, num;
	cin >> C;

	while (C--)
	{
		cin >> n;
		
		// 삼각형 보드, index 1 ~ n
		vector<vector<int>>board(n + 1);
		memset(cache, -1, sizeof(cache));

		for (int i = 1; i <= n; i++)
		{
			board[i].push_back(-1);
			for (int j = 1; j <= i; j++)
			{
				cin >> num;
				board[i].push_back(num);
			}
		}
		cout << findMax2(board, 1, 1) << "\n";
	}
	return 0;
}