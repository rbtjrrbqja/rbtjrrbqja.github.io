// 2020-01-16
// algospot TILING2
// https://algospot.com/judge/problem/read/TILING2

#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

// 나누기
int const DIVIDE = 1000000007;
// 캐시
int cache[101];

int findFillMethod(int idx)
{
	if (idx == 0 || idx == 1)
		return cache[idx] = 1;

	int& ret = cache[idx];

	if (ret != -1)
		return ret;

	ret = 0;

	ret += (findFillMethod(idx - 2) + findFillMethod(idx - 1)) % DIVIDE;

	return ret;
}

int main()
{
	int C;
	cin >> C;

	while (C--)
	{
		memset(cache, -1, sizeof(cache));
		int n;
		cin >> n;
		cout << findFillMethod(n) << endl;
	}

	return 0;
}