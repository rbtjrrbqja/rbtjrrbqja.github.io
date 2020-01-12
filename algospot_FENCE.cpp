// 2020-01-12
// algospot FENCE
// https://algospot.com/judge/problem/read/FENCE

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 울타리에서 최대 직사각형의 넓이를 구함
int findMax(const vector<int>& fence, int start, int end)
{
	// 하나면 높이 반환
	if (start == end)
		return fence[start];

	// 리턴값
	int ret = 0;

	// 중앙
	int mid = (start + end) / 2;

	// left | right
	// mid  | mid + 1
	int left = mid, right = mid + 1;

	// 양쪽으로 분할
	ret = max(findMax(fence, start, left), findMax(fence, right, end));

	// 가운데 두개의 최대 직사각형 넓이
	int height = min(fence[left], fence[right]);
	ret = max(ret, height * 2);

	// 가운데 두개에서 양옆으로 확장해가며 직사각형 넓이 최대값 갱신
	// 양옆중 더 높은쪽으로 확장
	while (start < left && right < end)
	{
		if (fence[left - 1] < fence[right + 1] || start == left && right < end)
			height = min(height, fence[(right++) + 1]);

		else if(fence[left - 1] >= fence[right + 1] || start < left && right == end)
			height = min(height, fence[(left--) - 1]);

		ret = max(ret, height * (right - left + 1));
	}

	return ret;
}

int main()
{
	// 테스트 케이스, 울타리 수
	int C, N;

	cin >> C;

	while (C--)
	{
		cin >> N;
		vector<int> fence(N, 0);

		for (int i = 0; i < N; i++)
			cin >> fence[i];

		cout << findMax(fence, 0, N - 1) << endl;
	}

	return 0;
}