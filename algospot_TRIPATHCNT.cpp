// 2020-01-17
// algospot TRIPATHCNT
// https://algospot.com/judge/problem/read/TRIPATHCNT

#include <iostream>
#include <vector>
#include <memory.h>
#include <algorithm>

using namespace std;

// findMax를 위한 캐시
int cache1[101][101];

// countMax를 위한 캐시
int cache2[101][101];

// 최대값을 구하는 함수
int findMax(const vector<vector<int>>& arr, int x, int y)
{
	int n = arr.size();

	if (x == n - 1)
		return cache1[x][y] = arr[x][y];

	int& ret = cache1[x][y];

	if (ret != -1)
		return ret;

	ret = 0;

	ret = max(findMax(arr, x + 1, y), findMax(arr, x + 1, y + 1)) + arr[x][y];

	return ret;
}

// 최대 경로의 수를 세는 함수
int countMax(const vector<vector<int>>& arr, int x, int y)
{
	int n = arr.size();

	if (x == n - 1)
		return 1;

	int& ret = cache2[x][y];

	if (ret != -1)
		return ret;

	ret = 0;


	// 같은경우는 양쪽으로 진행가능하므로 중복 호출

	if (findMax(arr, x + 1, y) >= findMax(arr, x + 1, y + 1))
		ret += countMax(arr, x + 1, y);
	if (findMax(arr, x + 1, y) <= findMax(arr, x + 1, y + 1))
		ret += countMax(arr, x + 1, y + 1);

	return ret;
}

int main()
{
	// 테스트 케이스, 삼각형의 크기, 입력할 자연수
	int C, n, num;
	cin >> C;

	while (C--)
	{
		// 각각의 캐시 -1 초기화
		memset(cache1, -1, sizeof(cache1));
		memset(cache2, -1, sizeof(cache2));

		cin >> n;
		vector<vector<int>> arr(n);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= i;j++) {
				cin >> num;
				arr[i].push_back(num);
			}
		}

		cout << countMax(arr, 0, 0) << endl;

	}

	return 0;
}