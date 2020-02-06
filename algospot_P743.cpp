// 2020-02-06
// �˰��� ���� �ذ� ���� P743
// Ư�� �������� �ּ�ġ �� �� ã��

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

// �ִ� ����
const int MAXINT = numeric_limits<int>::max();

// pairŸ��
typedef pair<int, int> Pair;

// 4���� int�߿��� 2���� int�� Pair Ÿ������ ��ȯ, ��ȯ
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

// ����Ʈ�� ����
// ��ȯ�Ǵ� Pair Ÿ���� first <= second �̴�
struct RMQ
{
	int n;

	vector<Pair> rangeMin;

	// ������
	RMQ(const vector<int>& array)
	{
		n = array.size();
		rangeMin.resize(n * 4);
		init(array, 0, n - 1, 1);
	}

	// �ʱ�ȭ
	Pair init(const vector<int>& array, int left, int right, int node)
	{
		if (left == right)
			return rangeMin[node] = Pair{ array[left], MAXINT };

		int mid = (left + right) / 2;
		Pair leftMin  = init(array, left, mid, node * 2);
		Pair rightMin = init(array, mid + 1, right, node * 2 + 1);

		return rangeMin[node] = minPair(leftMin, rightMin);
	}

	// ����
	Pair query(int left, int right, int node, int nodeLeft, int nodeRight)
	{
		if (right < nodeLeft || nodeRight < left)
			return Pair{ MAXINT, MAXINT };

		if (left <= nodeLeft && nodeRight <= right)
			return rangeMin[node];

		int mid = (nodeLeft + nodeRight) / 2;

		return min(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}

	// �� ���������� ȣ�⹮
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