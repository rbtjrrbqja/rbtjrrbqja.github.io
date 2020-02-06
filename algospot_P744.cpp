// 2020-02-06
// 알고리즘 문제해결 전략 P744
// 정렬된 수열의 특정 구간에서 최대 출현 빈도 계산

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

const int MAXINT = numeric_limits<int>::max();

struct RangeResult
{
	int size; // 크기
	int mostFrequent; // 최대 빈도수
	int leftNumber, leftFreq; // 왼쪽 끝, 왼쪽 끝의 빈도수
	int rightNumber, rightFreq; // 오른쪽 끝, 오른쪽 끝의 빈도수

	RangeResult()
	{
		size = mostFrequent = leftFreq = rightFreq = 0;
		leftNumber = rightNumber = 0;
	}

	RangeResult(int num)
	{
		size = mostFrequent = leftFreq = rightFreq = 1;
		leftNumber = rightNumber = num;
	}
};

RangeResult merge(const RangeResult& a, const RangeResult& b)
{
	RangeResult ret;
	
	ret.leftNumber = a.leftNumber;
	ret.leftFreq = a.leftFreq;

	// [a, a, a, a] [a, b ......] 형태를 합치는 경우
	if (a.size == a.leftFreq && a.leftNumber == b.leftNumber)
		ret.leftFreq += b.leftFreq;

	ret.rightNumber = b.rightNumber;
	ret.rightFreq = b.rightFreq;

	// [......, b] [b, b, b, b] 형태를 합치는 경우
	if (b.size == b.rightFreq && a.rightNumber == b.rightNumber)
		ret.rightFreq += a.rightFreq;

	ret.mostFrequent = max(a.mostFrequent, b.mostFrequent);

	// [a, a..., b] [b, ...., c, c....] 형태를 합치는 경우
	if (a.rightNumber == b.leftNumber)
		ret.mostFrequent = max(ret.mostFrequent, a.rightFreq + b.leftFreq);

	return ret;
}

struct RMQ
{
	int n;

	vector<RangeResult> rangeMin;

	RMQ(const vector<int>& array)
	{
		n = array.size();
		rangeMin.resize(n * 4);
		init(array, 0, n - 1, 1);
	}

	RangeResult init(const vector<int>& array, int left, int right, int node)
	{
		if (left == right)
			return rangeMin[node] = RangeResult(array[left]);

		int mid = (left + right) / 2;
		RangeResult leftR = init(array, left, mid, node * 2);
		RangeResult rightR = init(array, mid + 1, right, node * 2 + 1);

		return rangeMin[node] = merge(leftR, rightR);
	}

	RangeResult query(int left, int right, int node, int nodeLeft, int nodeRight)
	{
		if (right < nodeLeft || nodeRight < left)
			return RangeResult(0);

		if (left <= nodeLeft && nodeRight <= right)
			return rangeMin[node];

		int mid = (nodeLeft + nodeRight) / 2;

		RangeResult L = query(left, right, node * 2, nodeLeft, mid);
		RangeResult R = query(left, right, node * 2 + 1, mid + 1, nodeRight);

		return merge(L, R);
	}

	int query(int left, int right)
	{
		return query(left, right, 1, 0, n - 1).mostFrequent;
	}
};

int main()
{
	srand((unsigned int)time(NULL));

	vector<int> arr;

	for (int i = 0; i < 10; i++)
		arr.push_back(rand() % 5);

	sort(arr.begin(), arr.end(), less<int>());

	vector<int>::iterator iter;
	for (iter = arr.begin(); iter != arr.end(); iter++)
		cout << *iter << " ";
	cout << endl;

	RMQ rmq(arr);

	for (int i = 0; i < 26; i++)
		cout << rmq.rangeMin[i].mostFrequent << " ";
	cout << endl;

	cout << rmq.query(0, 9) << endl;
	cout << rmq.query(0, 4) << endl;
	cout << rmq.query(5, 9) << endl;
	cout << rmq.query(3, 7) << endl;

	return 0;
}