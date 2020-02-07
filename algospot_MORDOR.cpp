// 2020-02-07
// algospot MORDOR
// https://algospot.com/judge/problem/read/MORDOR

#include <cstdio>
#include <vector>

using std::vector;

// 주어진 문제에서 입력값들의 최대, 최소 정의
const int MAXINT = 20001;
const int MININT = -1;

// 더 작은값 반환
inline int _min(int a, int b)
{
	return a < b ? a : b;
}

// 더 큰값 반환
inline int _max(int a, int b)
{
	return a < b ? b : a;
}

// 구간 트리 구현
struct RMQ
{
	// 배열의 크기
	int size;
	// 구간 트리
	vector<int> RMQarr;
	// 비교 함수
	int(*pf)(int, int);

	RMQ(vector<int>& _arr, int(*_pf)(int, int))
	{
		size = _arr.size();
		RMQarr.resize(size * 4);
		pf = _pf;

		init(_arr, 0, size - 1, 1);
	}

	// 초기화
	int init(vector<int>& _arr, int _left, int _right, int _node)
	{
		if (_left == _right)
			return RMQarr[_node] = _arr[_left];

		int mid = (_left + _right) / 2;
		int left = init(_arr, _left, mid, _node * 2);
		int right = init(_arr, mid + 1, _right, _node * 2 + 1);

		return RMQarr[_node] = pf(left, right);
	}

	// 쿼리
	int query(int _left, int _right, int _node, int _leftNode, int _rightNode)
	{
		if (_right < _leftNode || _rightNode < _left)
		{
			if (pf == &_min)
				return MAXINT;
			return MININT;
		}

		if (_left <= _leftNode && _rightNode <= _right)
			return RMQarr[_node];

		int mid = (_leftNode + _rightNode) / 2;

		return pf(query(_left, _right, _node * 2, _leftNode, mid), query(_left, _right, _node * 2 + 1, mid + 1, _rightNode));
	}

	// 심플 쿼리
	int query(int _left, int _right)
	{
		return query(_left, _right, 1, 0, size - 1);
	}
};

int main()
{
	// 테스트 케이스, 표지판수, 등산로 수, 쿼리 구간
	int C, N, Q, a, b;
	scanf_s("%d", &C);

	while (C--)
	{
		scanf_s("%d %d", &N, &Q);

		vector<int> arr(N, 0);

		for (int i = 0; i < N; i++)
			scanf_s("%d", &arr[i]);

		RMQ Max(arr, _max);
		RMQ Min(arr, _min);

		for (int i = 0; i < Q; i++)
		{
			scanf_s("%d %d", &a, &b);
			printf("%d\n", Max.query(a, b) - Min.query(a, b));
		}
	}

	return 0;
}
