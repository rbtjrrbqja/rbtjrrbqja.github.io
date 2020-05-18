#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

class SampleMaxHeap
{
private:
	int *arr;
	int maxSize;

	void Swap(int idxA, int idxB)
	{
		int tmp = arr[idxA];
		arr[idxA] = arr[idxB];
		arr[idxB] = tmp;
	}

	void DownHeap(int idx)
	{
		int left = idx * 2;
		int right = idx * 2 + 1;

		int cmp;

		if (left <= arr[0])
		{
			cmp = left;

			if (right <= arr[0])
			{
				if (arr[cmp] < arr[right])
					cmp = right;
			}

			if (arr[idx] < arr[cmp]) {
				Swap(idx, cmp);
				DownHeap(cmp);
			}
		}
	}

public:
	SampleMaxHeap(int n) : maxSize(n)
	{
		arr = new int[n + 1];
		arr[0] = n;

		for (int i = 1; i <= n; i++)
			arr[i] = rand() % 100;

		Print();

		for (int i = n; i > 0; i--)
			DownHeap(i);
	}

	int Size()
	{
		return arr[0];
	}

	int Top()
	{
		return arr[1];
	}

	int Pop()
	{
		int ret = arr[1];
		arr[1] = arr[arr[0]];
		arr[0]--;

		DownHeap(1);

		return ret;
	}

	void Print()
	{
		for (int i = 1; i <= arr[0]; i++)
			cout << arr[i] << " ";
		
		cout << endl;
	}
};

int main()
{
	srand((unsigned int)time(NULL));

	SampleMaxHeap h(10);

	h.Print();

	cout << h.Pop() << endl;
	cout << h.Pop() << endl;

	h.Print();

	return 0;
}