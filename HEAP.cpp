#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

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

void showHeap(vector<int>& heap, int idx)
{
	int size = heap.size();

	if (size == 0 || idx >= size)
		return;

	cout << "current: " << heap[idx] << " ";

	if (idx * 2 + 1 < size)
		cout << "left: " << heap[idx * 2 + 1] << " ";
	if (idx * 2 + 2 < size)
		cout << "right " << heap[idx * 2 + 2] << " ";
	cout << endl;

	showHeap(heap, idx * 2 + 1);
	showHeap(heap, idx * 2 + 2);
}

int main()
{
	vector<int> heap;

	for (int i = 0; i < 10; i++)
	{
		int num; num = rand() % 100; cout << num << " ";
		pushHeap(heap, num);
	}
	cout << endl << endl;

	showHeap(heap, 0);

	for (int i = 0; i < 10; i++)
	{
		cout << heap[0] << " ";
		popHeap(heap);
	}

	return 0;
}