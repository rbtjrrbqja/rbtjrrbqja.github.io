// 2020-01-17
// algospot SNAIL
// https://algospot.com/judge/problem/read/SNAIL

#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

// 우물의 깊이, 장마의 기간, 캐시
int n, m;
double cache[1001 * 2 + 1][1001];

// 달팽이가 우물을 모두 올라갈 확률을 재귀 + 메모이제이션 으로 구현한 함수
double snailUp(int current, int count)
{
	// 목표에 도달 했다면
	if (current >= n)
		return cache[current][count] = 1;

	// 장마가 지났다면
	if (count == m)
		return cache[current][count] = 0;

	double& ret = cache[current][count];

	if (ret != -1)
		return ret;

	// 비가 올 확률 0.75
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