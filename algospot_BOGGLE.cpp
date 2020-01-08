// 2020-01-08
// algospot BOGGLE
// https://algospot.com/judge/problem/read/BOGGLE

#include <iostream>
#include <vector>

using namespace std;

// for output format
const string yes = "YES";
const string no = "NO";

// 8 direction
const int nextArrX[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
const int nextArrY[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

// check word in board
bool isInBoard(const vector<string>& board, int x, int y, const string& word)
{
	// check vector range (0 ~ 4)
	if (x < 0 || x > 4 || y < 0 || y > 4)
		return false;

	int len = word.length();

	// first alphabet check
	if (board[x][y] != word[0])
		return false;

	if (len == 1)
		return true;

	for (int i = 0; i < 8; i++)
		if (isInBoard(board, x + nextArrX[i], y + nextArrY[i], word.substr(1)))
			return true;
	
	return false;
}

int main()
{
	int C, N;	
	vector<string> board(5);
	string findWord;

	// input number of test cases
	cin >> C;

	while (C--)
	{
		// input alphabets in borad
		for (int i = 0; i < 5; i++)
			cin >> board[i];

		// input number of findWords
		cin >> N;

		while (N--)
		{
			bool check = false;
			cin >> findWord;

			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 5; j++)
					check |= isInBoard(board, i, j, findWord);

			if (check)
				cout << findWord << " " << yes << endl;
			else
				cout << findWord << " " << no << endl;
		}
	}

	return 0;
}