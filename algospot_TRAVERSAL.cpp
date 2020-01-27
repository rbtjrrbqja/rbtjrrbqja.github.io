// 2020-01-27
// algospot TRAVERSAL
// https://algospot.com/judge/problem/read/TRAVERSAL

#include <iostream>
#include <vector>

using namespace std;

// preorder, inorder �κ��� postorder�� ����ϴ� �Լ�
// ������ �Լ����࿡�� ��Ʈ�� ã��, ������ ���͸� �и��Ͽ� ���ȣ���Ѵ�.
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

	// ����
	makePost(
		vector<int>(preoder.begin() + 1, preoder.begin() + 1 + idx),
		vector<int>(inorder.begin(), inorder.begin() + idx));

	// ������
	makePost(
		vector<int>(preoder.begin() + 1 + idx, preoder.end()),
		vector<int>(inorder.begin() + idx + 1, inorder.end()));

	cout << root << " ";
}

int main()
{
	// �׽�Ʈ���̽�, ����� ��
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