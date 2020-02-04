// 2020-02-04
// algospot RUNNINGMEDIAN
// https://algospot.com/judge/problem/read/RUNNINGMEDIAN

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;

// 난수 생성을 위한 변수, 및 상수
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

	// 첫번째와 마지막 원소 바꾸기
	heap[0] = heap.back();

	// 마지막 원소 제거
	heap.pop_back();

	int size = heap.size();
	int idx = 0;

	while (1)
	{
		int left = idx * 2 + 1, right = idx * 2 + 2;

		// 왼쪽 자식 범위가 힙의 크기를 벗어나면 멈춤
		if (left >= size) break;

		// 바꿀 자식의 인덱스
		int next = idx;

		// 왼쪽자식이 자신보다 크면 인덱스 업데이트
		if (heap[next] < heap[left])
			next = left;

		// 오른쪽 자식이 범위 내 이면서 더 크다면 업데이트 
		if (right < size && heap[next] < heap[right])
			next = right;

		if (next == idx) break;

		swap(heap[idx], heap[next]);

		idx = next;
	}
}

int runningMedian(int n)
{
	// maxHeap의 최대(root)는 minHeap의 최소(root)보다 작다
	// 즉 maxHeap의 최대는 문제에서 요구하는 중간값이다
	priority_queue<int, vector<int>, less<int>> maxHeap;
	priority_queue<int, vector<int>, greater<int>> minHeap;

	int ret = 0;

	for (int i = 0; i < n; i++)
	{
		if (maxHeap.size() == minHeap.size())
			maxHeap.push(getA());
		else
			minHeap.push(getA());

		// maxHeap의 root가 minHeap의 root보다 클 경우
		// pop하고 바꾸어서 push
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
	// 테스트 케이스, 입력의 크기
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