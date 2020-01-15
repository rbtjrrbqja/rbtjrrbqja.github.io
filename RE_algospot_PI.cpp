// 2020-01-15
// algospot PI
// https://algospot.com/judge/problem/read/PI
// ** ���߿� �ٽ� Ǯ�� ** //

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <memory.h>

using namespace std;
// ���� �ִ�ġ ����
const int MAX_INT = 987654321;
// ĳ��
int cache[10001];
// ���̵��� ����� ���ڿ�
string arr;

// �κ� ���ڿ��� ���̵� ���
int checkLevel(int start, int end)
{
	string tmp = arr.substr(start, end - start + 1);

	int len = tmp.length();

	// ��� ���ڰ� ���� ���
	if (tmp == string(len, tmp[0]))
		return 1;


	// �����Ƽ� �����ϴ°�
	bool rotate = true;

	for (int i = 0; i < len; i++)
		if (tmp[i] != tmp[i % 2])
			rotate = false;

	if (rotate)
		return 4;

	// ���������ΰ�
	bool eq = true;
	for (int i = 0; i < len - 1; i++)
		if (tmp[i + 1] - tmp[i] != tmp[1] - tmp[0])
			eq = false;

	// ������ 1 �Ǵ� -1�ΰ�
	if (eq && abs(tmp[1] - tmp[0]) == 1)
		return 2;

	// �׿��� ���������ΰ�
	if (eq)
		return 5;

	return 10;
}

// ���ڿ��� �ɰ���( 3 - 5 )
int divideArr(int idx)
{
	int len = arr.length();

	// �������
	if (idx == len)
		return 0;

	int& ret = cache[idx];

	// ĳ�� Ȯ��
	if (ret != -1)
		return ret;

	ret = MAX_INT;

	for (int i = 3; i <= 5; i++)
		if(idx + i <= len)
			ret = min(ret, divideArr(idx + i) + checkLevel(idx, idx + i - 1));

	return ret;
}

int main()
{
	// �׽�Ʈ ���̽�
	int C;
	cin >> C;

	while (C--)
	{
		memset(cache, -1, sizeof(cache));
		cin >> arr;
		cout << divideArr(0) << endl;
	}

	return 0;
}