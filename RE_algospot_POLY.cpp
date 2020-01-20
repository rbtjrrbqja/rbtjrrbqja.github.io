// 2020-01-20
// algospot POLY
// https://algospot.com/judge/problem/read/POLY
// ** 다시풀기 //

#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

int cache[101][101];
const int MOD = 10000000;

// 폴리노미오의 경우의수를 찾기
int polyomino(int n, int first)
{
	if (n == first)
		return 1;

	int& ret = cache[n][first];

	if (ret != -1)
		return ret;

	ret = 0;

	// 첫번째 줄 과 그이후 이어지는 모양의 연관성을 파악할것
	// 첫번째줄과 다음 첫번째줄에 따라 경우의수가 달라진다
	// 책 p267 참고
	for (int i = 1; i <= n - first; i++) {
		ret += ((first + i - 1) * polyomino(n - first, i)) % MOD;
		ret %= MOD;
	}

	return ret % MOD;
}

int main()
{
	int C, n;
	cin >> C;

	while (C--)
	{
		memset(cache, -1, sizeof(cache));
		cin >> n;

		int ret = 0;

		for (int i = 1; i <= n; i++) {
			ret += polyomino(n, i);
			ret %= MOD;
		}

		cout << ret << endl;
	}

	return 0;
}