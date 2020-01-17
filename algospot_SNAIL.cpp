// 2020-01-17
// algospot SNAIL
// https://algospot.com/judge/problem/read/SNAIL

#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

// �칰�� ����, �帶�� �Ⱓ, ĳ��
int n, m;
double cache[1001 * 2 + 1][1001];

// �����̰� �칰�� ��� �ö� Ȯ���� ��� + �޸������̼� ���� ������ �Լ�
double snailUp(int current, int count)
{
	// ��ǥ�� ���� �ߴٸ�
	if (current >= n)
		return cache[current][count] = 1;

	// �帶�� �����ٸ�
	if (count == m)
		return cache[current][count] = 0;

	double& ret = cache[current][count];

	if (ret != -1)
		return ret;

	// �� �� Ȯ�� 0.75
	return ret = 0.25 * snailUp(current + 1, count + 1) + 0.75 * snailUp(current + 2, count + 1);
}

void init()
{
	for (int i = 0; i < 2003; i++)
		for (int j = 0; j < 1001; j++)
			cache[i][j] = -1;
}

int main()
{
	int C;
	cin >> C;

	while (C--)
	{
		init();
		cin >> n >> m;
		cout.precision(10);
		cout << snailUp(0, 0) << endl;
	}

	return 0;
}