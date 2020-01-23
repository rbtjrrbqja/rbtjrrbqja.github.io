// 2020-01-23
// algospot JOSEPHUS
// https://algospot.com/judge/problem/read/JOSEPHUS

#include <iostream>
#include <list>

using namespace std;

int main()
{
	// 테스트 케이스, 전체 사람의 수, 건너뛸 숫자
	int C, N, K;
	cin >> C;

	while (C--)
	{
		cin >> N >> K;

		list<int> arr;

		for (int i = 1; i <= N; i++)
			arr.push_back(i);

		// 이터레이터
		list<int>::iterator arrI = arr.begin();

		while (N > 2)
		{
			// erase 함수는 지운 다음 원소를 반환한다
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

		// 답 출력
		arrI = arr.begin();
		for (; arrI != arr.end(); arrI++)
			cout << *arrI << " ";
		cout << endl;
	}

	return 0;
}