// 2020-01-15
// algospot JLIS
// https://algospot.com/judge/problem/read/JLIS
// *** 다시 풀어봐야할것 **** //

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <memory.h>

using namespace std;

typedef long long ll;
const ll MIN = numeric_limits<ll>::min();
int cache[101][101];

int findJLIS(const vector<int>& a, const vector<int>& b, int Aidx, int Bidx)
{
	int& ret = cache[Aidx + 1][Bidx + 1];
	
	if (ret != -1)
		return ret;
	
	int Asize = a.size(), Bsize = b.size();
	
	ll aLast = (Aidx == -1) ? MIN : a[Aidx];
	ll bLast = (Bidx == -1) ? MIN : b[Bidx];

	ll last = max(aLast, bLast);

	ret = 0;

	for (int i = Aidx + 1; i < Asize; i++)
		if (last < a[i])
			ret = max(ret, findJLIS(a, b, i, Bidx) + 1);

	for (int i = Bidx + 1; i < Bsize; i++)
		if (last < b[i])
			ret = max(ret, findJLIS(a, b, Aidx, i) + 1);

	return ret;
}

int main()
{
	int c, n, m;
	cin >> c;

	while (c--)
	{
		cin >> n >> m;
		memset(cache, -1, sizeof(cache));
		vector<int> a(n, 0);
		vector<int> b(m, 0);
		int answer = 0;

		for (int i = 0; i < n; i++)
			cin >> a[i];

		for (int i = 0; i < m; i++)
			cin >> b[i];

		cout << findJLIS(a, b, -1, -1) << endl;
	}

	return 0;
}