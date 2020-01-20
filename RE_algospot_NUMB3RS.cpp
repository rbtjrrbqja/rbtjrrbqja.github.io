// 2020-01-21
// algospot NUMB3RS
// https://algospot.com/judge/problem/read/NUMB3RS

#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

// 마을의 수, 도망칠 날짜 수, 교도소가 있는 마을번호, 확률을 구할 마을번호
int n, d, p, dest;
// 지도 정보, 마을에 인접해있는 마을수 저장 배열
int map[50][50], neighbor[50];
// 캐시, -1 초기화
double cache[51][101];

double dunibal(int village, int count)
{
	if (count == d)
		return village == dest ? 1.0 : 0.0;
	
	double& ret = cache[village][count];

	if (ret != -1.0)
		return ret;

	ret = 0.0;
	
	for (int i = 0; i < n; i++)
		if (map[village][i] == 1)
			ret += dunibal(i, count + 1) / neighbor[village];

	return ret;
}

void resetCache()
{
	for (int i = 0; i < 51; i++)
		for (int j = 0; j < 101; j++)
			cache[i][j] = -1;
}


int main()
{
	// 테스트 케이스수, 찾을 마을수, 인접 마을수
	int C, t, count = 0;
	cin >> C;

	while (C--)
	{
		cin >> n >> d >> p;

		// 마을 지도 정보 입력 및 인접 마을수 업데이트
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> map[i][j];
				if (map[i][j] == 1) count++;
			}
			neighbor[i] = count;
			count = 0;
		}
		
		cin >> t;

		for (int i = 0; i < t; i++)
		{
			resetCache();
			cin >> dest;
			cout.precision(8);
			cout << dunibal(p, 0) << " ";
		}

		cout << endl;
	}

	return 0;
}