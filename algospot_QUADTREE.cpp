// 2020-01-12
// algospot QUADTREE
// https://algospot.com/judge/problem/read/QUADTREE

#include <iostream>

using namespace std;

// Ʈ�� ���� ����
// ����� ���ڿ��� downLeft -> downRight -> upLeft -> upRight ������ �о���̸�
// ���� ������ ������� ������
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

	// �Էµ� ���ڿ�, ��
	string picture, answer;

	// �׽�Ʈ ���̽�
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