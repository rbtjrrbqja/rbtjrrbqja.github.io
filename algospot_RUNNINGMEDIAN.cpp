// 2020-02-04
// algospot RUNNINGMEDIAN
// https://algospot.com/judge/problem/read/RUNNINGMEDIAN

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;

// ���� ������ ���� ����, �� ���
int A = 1983, a, b;
const int DIV = 20090711;

int getA()
{
	int ret = A;
	A = ((A * (ll)a) + b) % DIV;
	return ret;
}

void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void pushHeap(vector<int>& heap, int data)
{
	heap.push_back(data);

	int idx = heap.size() - 1;

	while (idx > 0 && heap[(idx - 1) / 2] < heap[idx])
	{
		swap(heap[(idx - 1) / 2], heap[idx]);
		idx = (idx - 1) / 2;
	}
}

void popHeap(vector<int>& heap)
{
	if (heap.empty()) return;

	// ù��°�� ������ ���� �ٲٱ�
	heap[0] = heap.back();

	// ������ ���� ����
	heap.pop_back();

	int size = heap.size();
	int idx = 0;

	while (1)
	{
		int left = idx * 2 + 1, right = idx * 2 + 2;

		// ���� �ڽ� ������ ���� ũ�⸦ ����� ����
		if (left >= size) break;

		// �ٲ� �ڽ��� �ε���
		int next = idx;

		// �����ڽ��� �ڽź��� ũ�� �ε��� ������Ʈ
		if (heap[next] < heap[left])
			next = left;

		// ������ �ڽ��� ���� �� �̸鼭 �� ũ�ٸ� ������Ʈ 
		if (right < size && heap[next] < heap[right])
			next = right;

		if (next == idx) break;

		swap(heap[idx], heap[next]);

		idx = next;
	}
}

int runningMedian(int n)
{
	// maxHeap�� �ִ�(root)�� minHeap�� �ּ�(root)���� �۴�
	// �� maxHeap�� �ִ�� �������� �䱸�ϴ� �߰����̴�
	priority_queue<int, vector<int>, less<int>> maxHeap;
	priority_queue<int, vector<int>, greater<int>> minHeap;

	int ret = 0;

	for (int i = 0; i < n; i++)
	{
		if (maxHeap.size() == minHeap.size())
			maxHeap.push(getA());
		else
			minHeap.push(getA());

		// maxHeap�� root�� minHeap�� root���� Ŭ ���
		// pop�ϰ� �ٲپ push
		if (!maxHeap.empty() && !minHeap.empty() && minHeap.top() < maxHeap.top())
		{
			int a = maxHeap.top(), b = minHeap.top();
			maxHeap.pop(); minHeap.pop();
			maxHeap.push(b); minHeap.push(a);
		}

		ret = (ret + maxHeap.top()) % DIV;
	}

	return ret;
}

int main()
{
	// �׽�Ʈ ���̽�, �Է��� ũ��
	int C, N;
	cin >> C;

	while (C--)
	{
		cin >> N >> a >> b;

		vector<int> heap;

		int ret = runningMedian(N);
		cout << ret << endl;

		A = 1983;
	}
	return 0;
}