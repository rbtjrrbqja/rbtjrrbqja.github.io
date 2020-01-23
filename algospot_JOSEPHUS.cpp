// 2020-01-23
// algospot JOSEPHUS
// https://algospot.com/judge/problem/read/JOSEPHUS

#include <iostream>
#include <list>

using namespace std;

int main()
{
	// �׽�Ʈ ���̽�, ��ü ����� ��, �ǳʶ� ����
	int C, N, K;
	cin >> C;

	while (C--)
	{
		cin >> N >> K;

		list<int> arr;

		for (int i = 1; i <= N; i++)
			arr.push_back(i);

		// ���ͷ�����
		list<int>::iterator arrI = arr.begin();

		while (N > 2)
		{
			// erase �Լ��� ���� ���� ���Ҹ� ��ȯ�Ѵ�
			arrI = arr.erase(arrI);
			N--;

			if (arrI == arr.end())
				arrI = arr.begin();

			for (int i = 0; i < K - 1; i++) {
				arrI++;
				if (arrI == arr.end())
					arrI = arr.begin();
			}
		}

		// �� ���
		arrI = arr.begin();
		for (; arrI != arr.end(); arrI++)
			cout << *arrI << " ";
		cout << endl;
	}

	return 0;
}