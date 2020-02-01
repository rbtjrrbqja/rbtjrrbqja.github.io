#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

// ��� ����ü ����
struct Node {
	// ������ ������
	int data;
	// ���� ��带 ��Ʈ�� �ϴ� ������, �¿� ���� ��
	int size, diff;
	// ����, ������
	Node* left, * right;

	// ������
	Node(const int& _data) : data(_data), size(1), diff(0), left(NULL), right(NULL) { }
	// ���� �ڽ� ����
	void setLeft(Node* newLeft) { left = newLeft; calcDiff(); calcSize(); }
	// ������ �ڽ� ����
	void setRight(Node* newRight) { right = newRight; calcDiff(); calcSize(); }

	// ���� ��ȯ
	int getHeight(Node* root)
	{
		if (root == NULL)
			return -1;

		return max(getHeight(root->left), getHeight(root->right)) + 1;
	}

	// �¿� ���� �� ���
	void calcDiff()
	{
		diff = getHeight(right) - getHeight(left);
	}

	// Ʈ�� ������ ���
	void calcSize()
	{
		size = 1;
		if (left)size += left->size;
		if (right)size += right->size;
	}
};

Node* LL(Node* root)
{
	Node* child = root->left;
	root->setLeft(child->right);
	child->setRight(root);
	return child;
}

Node* RR(Node* root)
{
	Node* child = root->right;
	root->setRight(child->left);
	child->setLeft(root);
	return child;
}

Node* LR(Node* root)
{
	Node* child = root->left;
	root->setLeft(RR(child));
	return LL(root);
}

Node* RL(Node* root)
{
	Node* child = root->right;
	root->setRight(LL(child));
	return RR(root);
}

// ��� ���� ���߱�
Node* balanceNode(Node* node)
{
	if (node->diff <= -2)
	{
		if (node->left->diff <= -1) node = LL(node); // LL
		else node = LR(node);						 // LR
	}
	else if (node->diff >= 2)
	{   
		if (node->right->diff >= 1) node = RR(node); // RR
		else node = RL(node);						 // RL
	}

	return node;
}

// ��� ����
Node* insert(Node* root, Node* node)
{
	if (root == NULL)
		return node;

	if (root->data < node->data) {
		root->setRight(insert(root->right, node));
		root = balanceNode(root);
	}
	else if (root->data > node->data) {
		root->setLeft(insert(root->left, node));
		root = balanceNode(root);
	}

	return root;
}

// max(a) < min(b) �϶� �¿� Ʈ�� ��ġ��
Node* merge(Node* a, Node* b)
{
	if (a == NULL) return b;
	if (b == NULL) return a;

	if (a->size > b->size) {
		a->setRight(merge(a->right, b));
		return a;
	}

	b->setLeft(merge(a, b->left));
	return b;
}

// ��� �����
Node* erase(Node* root, int data)
{
	if (root == NULL) return root;

	if (root->data == data)
	{
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}

	if (root->data < data) 
		root->setRight(erase(root->right, data));
	else 
		root->setLeft(erase(root->left, data));

	return root;
}

// ��ü Ʈ�� ���� ���߱�
Node* balanceTree(Node* root)
{
	if (root == NULL) return NULL;

	root = balanceNode(root);

	root->setLeft(balanceTree(root->left));
	root->setRight(balanceTree(root->right));

	return root;
}

// Ʈ������ ���
void showAVL(Node* root)
{
	if (root == NULL) return;

	cout << "current: " << root->data << " ";
	if (root->left) cout << "left: " << root->left->data << " ";
	if (root->right) cout << "right: " << root->right->data << " ";
	cout << "diff: " << root->diff << " ";
	cout << "size: " << root->size << " ";
	cout << endl;

	showAVL(root->left);
	showAVL(root->right);
}

int main()
{
	srand((unsigned int)time(NULL));

	Node* root = NULL;
	for (int i = 0; i < 10; i++) {
		int num = rand() % 100; cout << num << " ";
		root = insert(root, new Node(num));
	}
	cout << endl;

	showAVL(root);

	for (int i = 0; i < 3; i++)
	{
		int num; cout << "input delete num: "; cin >> num;
		root = erase(root, num);
		root = balanceTree(root);
		showAVL(root);
	}

	return 0;
}