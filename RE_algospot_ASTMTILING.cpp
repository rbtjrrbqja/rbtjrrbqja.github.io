// 2020-01-17
// algospot ASYMTILING
// https://algospot.com/judge/problem/read/ASYMTILING

#include <iostream>
#include <memory.h>

using namespace std;

const int MOD = 1000000007;
int n, cache[101];

// 타일 채우는 경우의 수 세기
int countTiling(int idx)
{
	if (idx <= 1)
		return 1;

	int& ret = cache[idx];

	if (ret != -1)
		return ret;

	return ret = (countTiling(idx - 1) + countTiling(idx - 2)) % MOD;
}

// 대칭 제외
int asymmetric(int idx)
{
	// 너비가 홀수
	if (idx % 2 == 1)
		return (countTiling(idx) - countTiling(idx / 2) + MOD) % MOD;

	// 너비가 짝수
	int ret = countTiling(idx);


	ret = (ret - countTiling(idx / 2) + MOD) % MOD;
	ret = (ret - countTiling(idx / 2 - 1) + MOD) % MOD;

	return ret;
}

int main()
{
	int C;
	cin >> C;

	while (C--)
	{
		memset(cache, -1, sizeof(cache));
		cin >> n;
		cout << asymmetric(n) << endl;
	}

	return 0;
}