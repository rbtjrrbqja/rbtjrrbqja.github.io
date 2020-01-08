// 2020-01-09
// algospot PICNIC
// https://algospot.com/judge/problem/read/PICNIC

#include <iostream>
#include <vector>

using namespace std;

// 모든 원소가 0인 n x n 이차원 벡터 생성
vector<vector<int>> make2DVector(int n)
{
	vector<vector<int>> temp(n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp[i].push_back(0);

	return temp;
}

// 모든 가능한 친구 쌍의 수를 세는 함수, 재귀
int makePair(const vector<vector<int>>& isFreind, vector<int>& pairVector)
{
	// 반환값
	int ret = 0;

	// 친구의 수
	int n = pairVector.size();

	// pairVector index
	int idx = 0;

	// 아직 쌍이 정해지지 않은 친구 index 찾기
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
	int C, n, m; // 테스트 케이스 수, 학생 수, 친구 쌍의 수
	int f1, f2;  // 친구 쌍

	cin >> C;

	while (C--)
	{
		cin >> n >> m;

		// 친구확인 벡터
		vector<vector<int>> isFreind = make2DVector(n);

		// 친구 정보 입력
		for (int i = 0; i < m; i++)
		{
			cin >> f1 >> f2;
			isFreind[f1][f2] = 1;
			isFreind[f2][f1] = 1;
		}

		// 친구 쌍 저장 벡터
		vector<int> pairVector(n, -1);
		
		cout << makePair(isFreind, pairVector) << endl;
	}

	return 0;
}