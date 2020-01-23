// 2020-01-23
// algospot ITES
// https://algospot.com/judge/problem/read/ITES

#include <iostream>
#include <queue>

using namespace std;

// �Է�
unsigned int A;

// �Է��� �����ϴ� �ڵ�
unsigned int initA()
{
	unsigned int ret = A % 10000 + 1;
	A = A * 214013 + 2531011;
	return ret;
}

// �������� K���� ũ�ٸ� pop
// �������� K���� ������ push
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
	// �׽�Ʈ���̽�
	int C, N, K;
	cin >> C;

	while (C--)
	{
		A = 1983;

		// �κ���, �Է½�ȣ�� ����
		cin >> K >> N;

		cout << check(N, K) << endl;
	}

	return 0;
}