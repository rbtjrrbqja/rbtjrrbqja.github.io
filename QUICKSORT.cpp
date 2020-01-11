// 2020-01-12
// quick sort

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void quickSort(vector<int>& arr, int start, int end)
{
	if (start < end)
	{
		int pivot = start;
		int i = start + 1, j = end;

		while (i <= j)
		{
			while (i <= end && arr[i] >= arr[pivot])
				i++;

			while (j > start&& arr[j] <= arr[pivot])
				j--;

			if (i > j)
				swap(arr[j], arr[pivot]);
			else
				swap(arr[i], arr[j]);
		}

		quickSort(arr, start, j - 1);
		quickSort(arr, j + 1, end);
	}
}

int main()
{
	
	srand((unsigned int)time(NULL));
	int len = rand() % 150 + 15;
	vector<int> arr(len);

	for (int i = 0; i < len; i++)
		arr[i] = rand() % 500;

	cout << "len: " << len << endl;
	for (int i = 0; i < len; i++)
		cout << arr[i] << " ";
	cout << endl;

	quickSort(arr, 0, len - 1);

	cout << "len: " << len << endl;
	for (int i = 0; i < len; i++)
		cout << arr[i] << " ";
	cout << endl;

	return 0;
}