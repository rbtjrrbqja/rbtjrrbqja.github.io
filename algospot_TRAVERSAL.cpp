// 2020-01-27
// algospot TRAVERSAL
// https://algospot.com/judge/problem/read/TRAVERSAL

#include <iostream>
#include <vector>

using namespace std;

// preorder, inorder 로부터 postorder를 출력하는 함수
// 각각의 함수실행에서 루트를 찾고, 적절히 벡터를 분리하여 재귀호출한다.
void makePost(const vector<int>& preoder, const vector<int>& inorder)
{
	int n = preoder.size();

	if (n == 0)
		return;

	int root = preoder.front();
	int idx = 0;

	for (int i = 0; i < n; i++)
		if (inorder[i] == root)
			idx = i;

	// 왼쪽
	makePost(
		vector<int>(preoder.begin() + 1, preoder.begin() + 1 + idx),
		vector<int>(inorder.begin(), inorder.begin() + idx));

	// 오른쪽
	makePost(
		vector<int>(preoder.begin() + 1 + idx, preoder.end()),
		vector<int>(inorder.begin() + idx + 1, inorder.end()));

	cout << root << " ";
}

int main()
{
	// 테스트케이스, 노드의 수
	int C, N;
	cin >> C;

	while (C--)
	{
		cin >> N;

		vector<int> preorder(N, 0);
		vector<int> inorder(N, 0);

		for (int i = 0; i < N; i++)
			cin >> preorder[i];
		for (int i = 0; i < N; i++)
			cin >> inorder[i];

		makePost(preorder, inorder);

		cout << endl;
	}

	return 0;
}