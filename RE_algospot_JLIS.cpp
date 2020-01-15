// 2020-01-15
// algospot JLIS
// https://algospot.com/judge/problem/read/JLIS
// *** 나중에 다시 풀기 **** //

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <memory.h>

using namespace std;

typedef long long ll;
// long long 타입 최소값 저장
const ll MIN = numeric_limits<ll>::min();
int cache[101][101];

// 재귀적 구현 + 메모이제이션
// 입력되는 원소는 32비트 정수
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
	
	// 더 큰수 있으면 하나씩 더해가며 재귀 호출
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
	// 테스트 케이스, 각각 배열의 원소의 수
	int c, n, m;
	cin >> c;

	while (c--)
	{
		cin >> n >> m;
		// 캐시 초기화
		memset(cache, -1, sizeof(cache));
		vector<int> a(n, 0);
		vector<int> b(m, 0);
		int answer = 0;
		
		// 배열 원소 입력
		for (int i = 0; i < n; i++)
			cin >> a[i];

		for (int i = 0; i < m; i++)
			cin >> b[i];

		cout << findJLIS(a, b, -1, -1) << endl;
	}

	return 0;
}
