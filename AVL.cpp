#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

// 노드 구조체 정의
struct Node {
	// 정수형 데이터
	int data;
	// 현재 노드를 루트로 하는 사이즈, 좌우 높이 차
	int size, diff;
	// 왼쪽, 오른쪽
	Node* left, * right;

	// 생성자
	Node(const int& _data) : data(_data), size(1), diff(0), left(NULL), right(NULL) { }
	// 왼쪽 자식 지정
	void setLeft(Node* newLeft) { left = newLeft; calcDiff(); calcSize(); }
	// 오른쪽 자식 지정
	void setRight(Node* newRight) { right = newRight; calcDiff(); calcSize(); }

	// 높이 반환
	int getHeight(Node* root)
	{
		if (root == NULL)
			return -1;

		return max(getHeight(root->left), getHeight(root->right)) + 1;
	}

	// 좌우 높이 차 계산
	void calcDiff()
	{
		diff = getHeight(right) - getHeight(left);
	}

	// 트리 사이즈 계산
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

// 노드 균형 맞추기
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

// 노드 삽입
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

// max(a) < min(b) 일때 좌우 트리 합치기
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

// 노드 지우기
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

// 전체 트리 균형 맞추기
Node* balanceTree(Node* root)
{
	if (root == NULL) return NULL;

	root = balanceNode(root);

	root->setLeft(balanceTree(root->left));
	root->setRight(balanceTree(root->right));

	return root;
}

// 트리정보 출력
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