// 2020-01-20
// algospot POLY
// https://algospot.com/judge/problem/read/POLY
// ** �ٽ�Ǯ�� //

#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

int cache[101][101];
const int MOD = 10000000;

// ������̿��� ����Ǽ��� ã��
int polyomino(int n, int first)
{
	if (n == first)
		return 1;

	int& ret = cache[n][first];

	if (ret != -1)
		return ret;

	ret = 0;

	// ù��° �� �� ������ �̾����� ����� �������� �ľ��Ұ�
	// ù��°�ٰ� ���� ù��°�ٿ� ���� ����Ǽ��� �޶�����
	// å p267 ����
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