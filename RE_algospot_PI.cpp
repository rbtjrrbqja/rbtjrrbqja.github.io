// 2020-01-15
// algospot PI
// https://algospot.com/judge/problem/read/PI
// ** 나중에 다시 풀기 ** //

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <memory.h>

using namespace std;
// 정수 최대치 정의
const int MAX_INT = 987654321;
// 캐시
int cache[10001];
// 난이도를 계산할 문자열
string arr;

// 부분 문자열의 난이도 계산
int checkLevel(int start, int end)
{
	string tmp = arr.substr(start, end - start + 1);

	int len = tmp.length();

	// 모든 숫자가 같을 경우
	if (tmp == string(len, tmp[0]))
		return 1;


	// 번갈아서 등장하는가
	bool rotate = true;

	for (int i = 0; i < len; i++)
		if (tmp[i] != tmp[i % 2])
			rotate = false;

	if (rotate)
		return 4;

	// 등차수열인가
	bool eq = true;
	for (int i = 0; i < len - 1; i++)
		if (tmp[i + 1] - tmp[i] != tmp[1] - tmp[0])
			eq = false;

	// 공차가 1 또는 -1인가
	if (eq && abs(tmp[1] - tmp[0]) == 1)
		return 2;

	// 그외의 등차수열인가
	if (eq)
		return 5;

	return 10;
}

// 문자열을 쪼개기( 3 - 5 )
int divideArr(int idx)
{
	int len = arr.length();

	// 기저사례
	if (idx == len)
		return 0;

	int& ret = cache[idx];

	// 캐시 확인
	if (ret != -1)
		return ret;

	ret = MAX_INT;

	for (int i = 3; i <= 5; i++)
		if(idx + i <= len)
			ret = min(ret, divideArr(idx + i) + checkLevel(idx, idx + i - 1));

	return ret;
}

int main()
{
	// 테스트 케이스
	int C;
	cin >> C;

	while (C--)
	{
		memset(cache, -1, sizeof(cache));
		cin >> arr;
		cout << divideArr(0) << endl;
	}

	return 0;
}