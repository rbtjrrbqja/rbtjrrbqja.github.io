// 2020-01-16
// algospot QUANTIZE
// https://algospot.com/judge/problem/read/QUANTIZE
// ** 다시 풀기 ** //

// 처음 생각 : S만큼 구간을 나누어 그 수들중에서 양자화할 숫자를 골라 계산
// 이를 재귀적으로 처리하면서 최소값을 찾는다.

// 책에서 알게된 것 : 
// 각 구간의 최소오차가 되는 값은 미분을 이용하여 구하면, 평균을 반올림한 정수이다

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

	// 반올림한 평균
	int average = 0.5 + (double)sum / ((double)end - start + 1);

	int ret = 0;

	// 차이의 제곱
	for (int i = start; i <= end; i++)
		ret += (int)pow(arr[i] - average, 2);

	return ret;
}

int divideArr(const vector<int>& arr, int idx, int count)
{
	int n = arr.size();

	// 끝에 도달
	if (idx == n)
		return 0;

	// 아직 숫자가 남음
	if (count == 0)
		return MAX_INT;

	int& ret = cache[idx][count];
	if (ret != -1)
		return ret;

	ret = MAX_INT;

	for (int i = 1; i <= n - idx; i++)
		ret = min(ret, divideArr(arr, idx + i, count - 1) + 
			           findMin(arr, idx, idx + i - 1));	

	// idx ~ idx + i - 1 까지의 구간 
	// 최대 S개의 수로 양자화 이므로 구간도 최대 S개

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