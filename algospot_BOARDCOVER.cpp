// 2020-01-10
// algospot BOARDCOVER
// https://algospot.com/judge/problem/read/BOARDCOVER

#include <iostream>
#include <vector>

using namespace std;

// 덮을 타일 모양
const int tile[4][3][2] =
{
	{{0, 0}, {0, 1}, {1, 0}}, // ┌
	{{0, 0}, {0, 1}, {1, 1}}, //  ┐
	{{0, 0}, {1, 0}, {1, 1}}, // └
	{{0, 0}, {1, 0}, {1,-1}}  //  ┘
};

// '.' 타일 개수 확인
int checkEmptyNum(const vector<string>& board)
{
	int count = 0;
	int H = board.size();
	int W = board[0].length();

	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			if (board[i][j] == '.')
				count++;

	return count;
}

// mode로 전해진 문자를 덮을수 있는지 확인, 가능하면 그 문자로 덮고 true 반환, 아니면 false 반환
bool boardCanCover(vector<string>& board, int x, int y, int tileType, char mode)
{
	int H = board.size(), W = board[0].length();
	int nx[3], ny[3];

	// 유효한 범위인지, 덮을수 있는 곳인지 확인
	for (int i = 0; i < 3; i++)
	{
		nx[i] = x + tile[tileType][i][0];
		ny[i] = y + tile[tileType][i][1];

		if (nx[i] < 0 || nx[i] >= H || ny[i] < 0 || ny[i] >= W)
			return false;
		else
			if (board[nx[i]][ny[i]] == mode)
				return false;
	}

	for (int i = 0; i < 3; i++)
		board[nx[i]][ny[i]] = mode;

	return true;
}

// 보드를 덮는 경우의수 구하기, 재귀
int findCoverMethod(vector<string>& board)
{
	int ret = 0;
	int H = board.size(), W = board[0].length();
	int x = -1, y = -1;

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (board[i][j] == '.') {
				x = i;
				y = j;
				break;
			}
		}
		if (x != -1 && y != -1)
			break;
	}

	if (x == -1 || y == -1)
		return 1;

	for (int i = 0; i < 4; i++)
	{
		if (boardCanCover(board, x, y, i, '#')) 
			ret += findCoverMethod(board);
		boardCanCover(board, x, y, i, '.');
	}

	return ret;
}

int main()
{
	// 테스트케이스, 세로, 가로
	int C, H, W;

	cin >> C;
	while (C--)
	{
		cin >> H >> W;

		vector<string> board(H);
		for (int i = 0; i < H; i++)
			cin >> board[i];
		
		if (checkEmptyNum(board) % 3 == 0)
			cout << findCoverMethod(board) << endl;
		else
			cout << 0 << endl;
	}

	return 0;
}