// 2020-01-16
// algospot QUANTIZE
// https://algospot.com/judge/problem/read/QUANTIZE
// ** �ٽ� Ǯ�� ** //

// ó�� ���� : S��ŭ ������ ������ �� �����߿��� ����ȭ�� ���ڸ� ��� ���
// �̸� ��������� ó���ϸ鼭 �ּҰ��� ã�´�.

// å���� �˰Ե� �� : 
// �� ������ �ּҿ����� �Ǵ� ���� �̺��� �̿��Ͽ� ���ϸ�, ����� �ݿø��� �����̴�

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>

using namespace std;
const int MAX_INT = 987654321;
int cache[1001][101];

int findMin(const vector<int>& arr, int start, int end)
{
	int sum = 0;

	for (int i = start; i <= end; i++)
		sum += arr[i];

	// �ݿø��� ���
	int average = 0.5 + (double)sum / ((double)end - start + 1);

	int ret = 0;

	// ������ ����
	for (int i = start; i <= end; i++)
		ret += (int)pow(arr[i] - average, 2);

	return ret;
}

int divideArr(const vector<int>& arr, int idx, int count)
{
	int n = arr.size();

	// ���� ����
	if (idx == n)
		return 0;

	// ���� ���ڰ� ����
	if (count == 0)
		return MAX_INT;

	int& ret = cache[idx][count];
	if (ret != -1)
		return ret;

	ret = MAX_INT;

	for (int i = 1; i <= n - idx; i++)
		ret = min(ret, divideArr(arr, idx + i, count - 1) + 
			           findMin(arr, idx, idx + i - 1));	

	// idx ~ idx + i - 1 ������ ���� 
	// �ִ� S���� ���� ����ȭ �̹Ƿ� ������ �ִ� S��

	return ret;
}

int main()
{
	int C, N, S;

	cin >> C;

	while (C--)
	{
		memset(cache, -1, sizeof(cache));
		cin >> N >> S;
		vector<int> arr(N, 0);

		for (int i = 0; i < N; i++)
			cin >> arr[i];

		sort(arr.begin(), arr.end());

		cout << divideArr(arr, 0, S) << endl;
	}

	return 0;
}