// 2020-01-14
// algospot JUMPGAME
// https://algospot.com/judge/problem/read/JUMPGAME

#include <iostream>
#include <vector>

using namespace std;

const string yes = "YES";
const string no  = "NO";

// 재귀적 구현
bool findPath1(const vector<vector<int>>& board, int x, int y)
{
	int n = board.size();

	// 보드의 범위를 벗어남
	if (x >= n || y >= n)
		return false;

	// 목적지에 도달
	if (x == n - 1 && y == n - 1)
		return true;

	return findPath1(board, x + board[x][y], y) | findPath1(board, x, y + board[x][y]);
}

// 재귀적 구현 + 메모이제이션
int findPath2(const vector<vector<int>>& board, vector<vector<int>>& cache, int x, int y)
{
	int n = board.size();

	// 보드의 범위를 벗어남
	if (x >= n || y >= n)
		return 0;

	// 목적지에 도달
	if (x == n - 1 && y == n - 1)
		return 1;

	if (cache[x][y] != -1)
		return cache[x][y];


	return (cache[x][y] = findPath2(board, cache, x + board[x][y], y) | 
						 findPath2(board, cache, x, y + board[x][y]));
}

int main()
{
	// 테스트 케이스, 게임판 한변의 길이, 입력할 수
	int C, n, num;
	cin >> C;

	while (C--) {
		cin >> n;
		
		// 게임판
		vector<vector<int>> board(n);
		// 캐시
		vector<vector<int>> cache(n);

		// 게임판에 자연수 입력, 캐시 -1 초기화
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> num;
				board[i].push_back(num);
				cache[i].push_back(-1);
			}
		}

		/*
		if (findPath1(board, 0, 0))
			cout << yes;
		else
			cout << no;
		*/

		if (findPath2(board, cache, 0, 0) > 0)
			cout << yes << endl;
		else
			cout << no << endl;
	}

	return 0;
}