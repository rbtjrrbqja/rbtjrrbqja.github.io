// 2020-01-14
// algospot JUMPGAME
// https://algospot.com/judge/problem/read/JUMPGAME

#include <iostream>
#include <vector>

using namespace std;

const string yes = "YES";
const string no  = "NO";

// ����� ����
bool findPath1(const vector<vector<int>>& board, int x, int y)
{
	int n = board.size();

	// ������ ������ ���
	if (x >= n || y >= n)
		return false;

	// �������� ����
	if (x == n - 1 && y == n - 1)
		return true;

	return findPath1(board, x + board[x][y], y) | findPath1(board, x, y + board[x][y]);
}

// ����� ���� + �޸������̼�
int findPath2(const vector<vector<int>>& board, vector<vector<int>>& cache, int x, int y)
{
	int n = board.size();

	// ������ ������ ���
	if (x >= n || y >= n)
		return 0;

	// �������� ����
	if (x == n - 1 && y == n - 1)
		return 1;

	if (cache[x][y] != -1)
		return cache[x][y];


	return (cache[x][y] = findPath2(board, cache, x + board[x][y], y) | 
						 findPath2(board, cache, x, y + board[x][y]));
}

int main()
{
	// �׽�Ʈ ���̽�, ������ �Ѻ��� ����, �Է��� ��
	int C, n, num;
	cin >> C;

	while (C--) {
		cin >> n;
		
		// ������
		vector<vector<int>> board(n);
		// ĳ��
		vector<vector<int>> cache(n);

		// �����ǿ� �ڿ��� �Է�, ĳ�� -1 �ʱ�ȭ
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