// 2020-01-15
// algospot LIS
// https://algospot.com/judge/problem/read/LIS

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// LIS를 찾는 재귀 함수, 메모이제이션
// idx에서 시작하는 최대의 길이 반환
int findLIS(vector<int>& cache, const vector<int>& arr, int idx)
{
	int n = arr.size();

	if (cache[idx + 1] != -1)
		return cache[idx + 1];

	cache[idx + 1] = 1;

	for (int i = idx + 1; i < n; i++)
		if (idx == -1 || arr[i] > arr[idx])
			cache[idx + 1] = max(cache[idx + 1], 1 + findLIS(cache, arr, i));

	return cache[idx + 1];
}

int main()
{
	// 테스트 케이스, 원소의 수
	int C, N;
	cin >> C;

	while (C--)
	{
		cin >> N;
		// 원소 배열
		vector<int> arr(N);

		// 캐시, -1 초기화
		vector<int> cache(N + 1, -1);
		int answer = 0;

		for (int i = 0; i < N; i++)
			cin >> arr[i];

		cout << findLIS(cache, arr, -1) - 1 << endl;
	}


	return 0;
}