// 2020-01-10
// algospot CLOCKSYNC
// https://algospot.com/judge/problem/read/CLOCKSYNC

#include <iostream>
#include <vector>
#include <algorithm>    // min

using namespace std;

// 매우 큰수 정의
const int MAX_INT = 987654321;

// 스위치 작동시 동작하는 시계
// swtch[스위치 번호][시계 번호]
const int swtch[10][16] =
{
	{ 1,1,1,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },
	{ 0,0,0,1, 0,0,0,1, 0,1,0,1, 0,0,0,0 },
	{ 0,0,0,0, 1,0,0,0, 0,0,1,0, 0,0,1,1 },
	{ 1,0,0,0, 1,1,1,1, 0,0,0,0, 0,0,0,0 },
	{ 0,0,0,0, 0,0,1,1, 1,0,1,0, 1,0,0,0 },
	{ 1,0,1,0, 0,0,0,0, 0,0,0,0, 0,0,1,1 },
	{ 0,0,0,1, 0,0,0,0, 0,0,0,0, 0,0,1,1 },
	{ 0,0,0,0, 1,1,0,1, 0,0,0,0, 0,0,1,1 },
	{ 0,1,1,1, 1,1,0,0, 0,0,0,0, 0,0,0,0 },
	{ 0,0,0,1, 1,1,0,0, 0,1,0,0, 0,1,0,0 },
};

// 모든 시계가 12시 인가?
bool checkAllClock(const vector<int>& clock)
{
	for (int i = 0; i < 16; i++)
		if (clock[i] != 12)
			return false;

	return true;
}

// 시계 작동
void pushSwitch(vector<int>& clock, int switchNum)
{
	for (int i = 0; i < 16; i++)
	{
		if (swtch[switchNum][i] == 1)
		{
			clock[i] += 3;
			if (clock[i] > 12)
				clock[i] = 3;
		}
	}
}

// 최소 경우의수 구하기, 재귀
int findCount(vector<int>& clock, int count, int switchNum)
{
	int ret = MAX_INT;

	if (checkAllClock(clock))
		return count;

	if (switchNum > 9)
		return MAX_INT;

	for (int i = 0; i < 4; i++)
	{
		ret = min(ret, findCount(clock, count + i, switchNum + 1));
		pushSwitch(clock, switchNum);
	}

	return ret;
}

int main()
{
	// 테스트 케이스
	int C;
	// 현재 시계 시간 저장
	vector<int> clock(16);

	cin >> C;

	while (C--)
	{
		for (int i = 0; i < 16; i++)
			cin >> clock[i];

		int ret = findCount(clock, 0, 0);

		if (ret != MAX_INT)
			cout << ret << "\n";
		else
			cout << "-1\n";
	}

	return 0;
}