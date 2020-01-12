// 2020-01-12
// algospot FENCE
// https://algospot.com/judge/problem/read/FENCE

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ��Ÿ������ �ִ� ���簢���� ���̸� ����
int findMax(const vector<int>& fence, int start, int end)
{
	// �ϳ��� ���� ��ȯ
	if (start == end)
		return fence[start];

	// ���ϰ�
	int ret = 0;

	// �߾�
	int mid = (start + end) / 2;

	// left | right
	// mid  | mid + 1
	int left = mid, right = mid + 1;

	// �������� ����
	ret = max(findMax(fence, start, left), findMax(fence, right, end));

	// ��� �ΰ��� �ִ� ���簢�� ����
	int height = min(fence[left], fence[right]);
	ret = max(ret, height * 2);

	// ��� �ΰ����� �翷���� Ȯ���ذ��� ���簢�� ���� �ִ밪 ����
	// �翷�� �� ���������� Ȯ��
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
	// �׽�Ʈ ���̽�, ��Ÿ�� ��
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