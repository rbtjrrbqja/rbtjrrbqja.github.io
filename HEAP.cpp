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