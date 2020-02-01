#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

typedef int KeyType;

struct Node {
	KeyType key;
	int priority, size;
	Node* left, * right;

	Node(const KeyType& _key) : key(_key), priority(rand() % 10000),
		size(1), left(NULL), right(NULL) { }

	void setLeft(Node* newLeft) { left = newLeft;  calcSize(); }
	void setRight(Node* newRight) { right = newRight; calcSize(); }

	void calcSize()
	{
		size = 1;
		if (left) size += left->size;
		if (right)size += right->size;
	}
};

typedef pair<Node*, Node*> NodePair;

NodePair split(Node* root, KeyType key)
{
	if (root == NULL)
		return NodePair(NULL, NULL);

	// ��Ʈ�� key �̸��̸� ������ Ʈ�� �ɰ���
	if (root->key < key)
	{
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}

	// ��Ʈ�� key �̻��̸� ���� Ʈ�� �ɰ���
	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}


// ��Ʈ�� ��Ʈ�� �ϴ� Ʈ���� ��带 ������ �� ��� Ʈ���� ��Ʈ�� ��ȯ
Node* insert(Node* root, Node* node)
{
	if (root == NULL)
		return node;

	// �߰� ��尡 ��Ʈ���� �켱������ �������
	if (root->priority < node->priority)
	{
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	else if (node->key < root->key)
		root->setLeft(insert(root->left, node));
	else
		root->setRight(insert(root->right, node));

	return root;
}

// max(a) < min(b) �� ��� �� ���� ��ģ��
Node* merge(Node* a, Node* b)
{
	if (a == NULL) return b;
	if (b == NULL) return a;

	if (a->priority < b->priority)
	{
		b->setLeft(merge(a, b->left));
		return b;
	}

	a->setRight(merge(a->right, b));
	return a;
}

Node* erase(Node* root, KeyType key)
{
	if (root == NULL)
		return root;

	// root�� ����� �� ����Ʈ���� ��ģ�� ��ȯ
	if (root->key == key)
	{
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}

	if (key < root->key)
		root->setLeft(erase(root->left, key));
	else
		root->setRight(erase(root->right, key));

	return root;
}

// k��° ���� ã��
Node* kth(Node* root, int k)
{
	if (root->size < k)
		return NULL;

	int leftSize = 0;

	if (root->left != NULL)
		leftSize = root->left->size;

	if (k <= leftSize)
		return kth(root->left, k);

	if (k == leftSize + 1)
		return root;

	return kth(root->right, k - leftSize - 1);
}

// key���� ���� Ű���� ���� ��ȯ
int countLessThan(Node* root, KeyType key)
{
	if (root == NULL)
		return 0;

	if (root->key >= key)
		return countLessThan(root->left, key);

	int ls = (root->left ? root->left->size : 0);

	return ls + 1 + countLessThan(root->right, key);
}

void deleteTreap(Node* root)
{
	if (root == NULL)
		return;

	deleteTreap(root->left);
	deleteTreap(root->right);

	delete root;
}

int main()
{
	srand((unsigned int)time(NULL));

	int C, N;

	scanf_s("%d", &C);

	while (C--)
	{
		Node* root = NULL;

		scanf_s("%d", &N);

		vector<int> arr(N, 0);
		vector<int>   A(N, 0);

		for (int i = 0; i < N; i++)
			root = insert(root, new Node(i + 1));

		for (int i = 0; i < N; i++)
			scanf_s("%d", &arr[i]);

		for (int i = N - 1; i >= 0; i--)
		{
			int num = arr[i];
			Node* tmp = kth(root, i + 1 - num);
			A[i] = tmp->key;
			root = erase(root, tmp->key);
		}

		for (int i = 0; i < N; i++)
			printf("%d ", A[i]);
		printf("\n");

		deleteTreap(root);
	}

	return 0;
}