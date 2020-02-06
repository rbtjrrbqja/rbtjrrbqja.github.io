// 2020-02-06
// 알고리즘 문제 해결 전략 P743
// 특정 구간에서 최소치 두 개 찾기

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

// 최대 정수
const int MAXINT = numeric_limits<int>::max();

// pair타입
typedef pair<int, int> Pair;

// 4개의 int중에서 2개의 int를 Pair 타입으로 변환, 반환
Pair minPair(Pair a, Pair b)
{
	int ret1, ret2;
	
	if (a.first < b.first)
	{
		ret1 = a.first;
		int tmp = a.second < b.first ? a.second : b.first;
		ret2 = tmp < b.second ? tmp : b.second;

		return Pair{ ret1, ret2 };
	}

	ret1 = b.first;
	int tmp = a.first < b.second ? a.first : b.second;
	ret2 = tmp < a.second ? tmp : a.second;

	return Pair{ ret1, ret2 };
}

// 구간트리 구조
// 반환되는 Pair 타입은 first <= second 이다
struct RMQ
{
	int n;

	vector<Pair> rangeMin;

	// 생성자
	RMQ(const vector<int>& array)
	{
		n = array.size();
		rangeMin.resize(n * 4);
		init(array, 0, n - 1, 1);
	}

	// 초기화
	Pair init(const vector<int>& array, int left, int right, int node)
	{
		if (left == right)
			return rangeMin[node] = Pair{ array[left], MAXINT };

		int mid = (left + right) / 2;
		Pair leftMin  = init(array, left, mid, node * 2);
		Pair rightMin = init(array, mid + 1, right, node * 2 + 1);

		return rangeMin[node] = minPair(leftMin, rightMin);
	}

	// 쿼리
	Pair query(int left, int right, int node, int nodeLeft, int nodeRight)
	{
		if (right < nodeLeft || nodeRight < left)
			return Pair{ MAXINT, MAXINT };

		if (left <= nodeLeft && nodeRight <= right)
			return rangeMin[node];

		int mid = (nodeLeft + nodeRight) / 2;

		return min(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}

	// 더 간단한쿼리 호출문
	Pair query(int left, int right)
	{
		return query(left, right, 1, 0, n - 1);
	}
};

int main()
{
	srand((unsigned int)time(NULL));

	vector<int> arr;

	for (int i = 0; i < 10; i++)
	{
		int num = rand() % 30; cout << num << " ";
		arr.push_back(num);
	}
	cout << endl;

	RMQ rmq(arr);

	Pair ret = rmq.query(0, 9);
	cout << ret.first << " " << ret.second << endl;

	return 0;
}