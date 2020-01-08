// 2020-01-09
// algospot PICNIC
// https://algospot.com/judge/problem/read/PICNIC

#include <iostream>
#include <vector>

using namespace std;

// ��� ���Ұ� 0�� n x n ������ ���� ����
vector<vector<int>> make2DVector(int n)
{
	vector<vector<int>> temp(n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp[i].push_back(0);

	return temp;
}

// ��� ������ ģ�� ���� ���� ���� �Լ�, ���
int makePair(const vector<vector<int>>& isFreind, vector<int>& pairVector)
{
	// ��ȯ��
	int ret = 0;

	// ģ���� ��
	int n = pairVector.size();

	// pairVector index
	int idx = 0;

	// ���� ���� �������� ���� ģ�� index ã��
	while (pairVector[idx] != -1) {
		idx++;

		if (idx >= n)
			return 1;
	}

	for (int i = 0; i < n; i++)
	{
		if (isFreind[idx][i] == 1 && pairVector[i] == -1)
		{
			pairVector[idx] = i;
			pairVector[i] = idx;

			ret += makePair(isFreind, pairVector);

			pairVector[idx] = -1;
			pairVector[i] = -1;
		}
	}

	return ret;
}

int main()
{
	int C, n, m; // �׽�Ʈ ���̽� ��, �л� ��, ģ�� ���� ��
	int f1, f2;  // ģ�� ��

	cin >> C;

	while (C--)
	{
		cin >> n >> m;

		// ģ��Ȯ�� ����
		vector<vector<int>> isFreind = make2DVector(n);

		// ģ�� ���� �Է�
		for (int i = 0; i < m; i++)
		{
			cin >> f1 >> f2;
			isFreind[f1][f2] = 1;
			isFreind[f2][f1] = 1;
		}

		// ģ�� �� ���� ����
		vector<int> pairVector(n, -1);
		
		cout << makePair(isFreind, pairVector) << endl;
	}

	return 0;
}