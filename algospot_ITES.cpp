// 2020-01-23
// algospot ITES
// https://algospot.com/judge/problem/read/ITES

#include <iostream>
#include <queue>

using namespace std;

// 입력
unsigned int A;

// 입력을 생성하는 코드
unsigned int initA()
{
	unsigned int ret = A % 10000 + 1;
	A = A * 214013 + 2531011;
	return ret;
}

// 구간합이 K보다 크다면 pop
// 구간합이 K보다 작으면 push
int check(int N, int K)
{
	int ret = 0, sum = 0;
	queue<unsigned int> q;

	for (int i = 0; i < N; i++)
	{
		int num = initA();
		q.push(num);
		sum += num;

		while (sum > K)
		{
			sum -= q.front();
			q.pop();
		}

		if (sum == K)
			ret++;
	}

	return ret;
}

int main()
{
	// 테스트케이스
	int C, N, K;
	cin >> C;

	while (C--)
	{
		A = 1983;

		// 부분합, 입력신호의 개수
		cin >> K >> N;

		cout << check(N, K) << endl;
	}

	return 0;
}