// 2020-01-11
// merge sort


#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void merge(vector<int>& copy, vector<int>& arr, int start, int mid, int end)
{
	int i = start, j = mid + 1, k = start;

	while (i <= mid && j <= end)
	{
		if (arr[i] > arr[j])
			copy[k++] = arr[i++];
		else
			copy[k++] = arr[j++];
	}

	while (j <= end)
		copy[k++] = arr[j++];

	while (i <= mid)
		copy[k++] = arr[i++];

	for (int i = start; i <= end; i++)
		arr[i] = copy[i];
}

void mergesort(vector<int>& copy, vector<int>& arr, int start, int end)
{
	if (start < end) {

		int mid = (start + end) / 2;

		mergesort(copy, arr, start, mid);
		mergesort(copy, arr, mid + 1, end);
		merge(copy, arr, start, mid, end);
	}
}

int main()
{
	srand((unsigned int)time(NULL));
	
	int len = rand() % 10 + 20;
	vector<int> arr(len), copy(len);

	for (int i = 0; i < len; i++)
		arr[i] = rand() % 500;

	cout << "len: " << len << endl;
	for (int i = 0; i < len; i++)
		cout << arr[i] << " ";
	cout << endl;

	mergesort(copy, arr, 0, len - 1);

	cout << "len: " << len << endl;
	for (int i = 0; i < len; i++)
		cout << arr[i] << " ";
	cout << endl;

	return 0;
}