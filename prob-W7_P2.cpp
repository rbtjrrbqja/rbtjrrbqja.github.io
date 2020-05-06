#include <iostream>
#include <memory.h>
#include <algorithm>
#include <ctime>

using namespace std;

int T, N, catalog[2][1001]; // [0] -> price, [1] -> pack fee
int cache[1001][1001];      // cache for DP

int func(int x, int y)
{
	int& ret = cache[x][y];

	if (ret != -1)
		return ret;

	ret = 0;
	int minValue = catalog[0][x];

	// purchase day x to day y in one time
	for (int i = x; i <= y; i++)
	{
		ret += catalog[0][i];

		if (i > x) {
			ret += catalog[1][i];
			minValue = min(minValue, catalog[0][i]);
		}
	}

	ret += minValue;

	// compare to other
	for (int i = x; i < y; i++)
		ret = min(ret, func(x, i) + func(i + 1, y));

	return ret;
}

int main()
{
	std::ios::sync_with_stdio(false);
	cin >> T;

	while (T--)
	{
		memset(cache, -1, sizeof(cache));

		cin >> N;

		for (int i = 1; i <= N; i++)
			cin >> catalog[0][i] >> catalog[1][i];

		cout << func(1, N) << endl;
	}

	return 0;
}