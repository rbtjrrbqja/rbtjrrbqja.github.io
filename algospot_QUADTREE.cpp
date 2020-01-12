// 2020-01-12
// algospot QUADTREE
// https://algospot.com/judge/problem/read/QUADTREE

#include <iostream>

using namespace std;

// 트리 상하 반전
// 압축된 문자열을 downLeft -> downRight -> upLeft -> upRight 순으로 읽어들이면
// 상하 반전된 모양으로 읽힌다
string reverse(string picture, int& idx)
{
	idx++;

	if (picture[idx] == 'w' || picture[idx] == 'b')
		return string(1, picture[idx]);

	string upLeft = reverse(picture, idx);
	string upRight = reverse(picture, idx);
	string downLeft = reverse(picture, idx);
	string downRight = reverse(picture, idx);

	return string("x") + downLeft + downRight + upLeft + upRight;
}

int main()
{
	int C;

	// 입력된 문자열, 답
	string picture, answer;

	// 테스트 케이스
	cin >> C;

	while (C--)
	{
		int idx = -1;
		cin >> picture;
		answer = reverse(picture, idx);
		cout << answer << endl;
	}

	return 0;
}