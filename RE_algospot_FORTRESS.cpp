// 2020-01-27
// algospot FORTRESS
// https://algospot.com/judge/problem/read/FORTRESS

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// �� Ŭ����
class Wall
{
public:
	int x, y, r;
	Wall(int x, int y, int r) : x(x), y(y), r(r) { }
};

// ��� Ŭ����
class Node
{
private:
	Wall w;
	Node* parent;
	vector<Node*> children;
	int childrenSize;
public:
	Node(int x, int y, int r) : w(Wall(x, y, r)), parent(NULL), childrenSize(0) { }
	~Node()
	{
		delete parent;

		for (int i = 0; i < childrenSize; i++)
			delete children[i];
	}

	Wall getWall() const
	{
		return w;
	}

	Node* getParent() const
	{
		return parent;
	}

	void setParent(Node* n)
	{
		parent = n;
	}

	Node* getChild(int idx) const
	{
		return children[idx];
	}

	void pushChildren(Node* n)
	{
		children.push_back(n);
		childrenSize++;
	}

	int getChildrenSize() const
	{
		return childrenSize;
	}
};

// ������ ������ �ȿ� ���ԵǴ��� Ȯ��
bool isRInL(const Node* l, const Node* r)
{
	double dir = sqrt(pow(r->getWall().x - l->getWall().x, 2) + 
		              pow(r->getWall().y - l->getWall().y, 2));

	return l->getWall().r >= dir + r->getWall().r ? true : false;
}

void makeTree(vector<Node*>& tree)
{
	int N = tree.size();

	// �θ� ��� ����
	for (int i = 0; i < N; i++) {
		Node* parent = tree[i];

		// �ڽ� ��� ����
		for (int j = 1; j < N; j++) {

			if (i == j)
				continue;

			Node* child = tree[j];

			// �ڽ��� �θ� ���ԵǸ�
			if (isRInL(parent, child))
			{
				bool check = true;

				// �ڽİ� �θ���̿� �ٸ� ���� �ִ��� Ȯ��
				for (int k = 1; k < N; k++) {
					if (j == k || i == k)
						continue;

					// �ٸ����� ����
					if (isRInL(tree[k], child) && isRInL(parent, tree[k])) {
						check = false;
						break;
					}
				}

				// �ٸ����� �������� ������ �θ� �ڽ� ���� Ȯ��
				if (check) {
					child->setParent(parent);
					parent->pushChildren(child);
				}
			}
		}
	}
}

int ans = 0;

int getHeight(const Node* root)
{
	int n = root->getChildrenSize();
	vector<int> tmp;

	for (int i = 0; i < n; i++)
		tmp.push_back(getHeight(root->getChild(i)));

	if (n == 0)
		return 0;

	// ��������
	sort(tmp.begin(), tmp.end());

	// �ٿ��� �ٸ� ������ ���� �ִ� ���� ���
	if (n >= 2)
		ans = max(ans, tmp[n - 2] + tmp[n - 1] + 2);
	
	// ���� ��ȯ
	return tmp.back() + 1;
}

int solve(Node* root)
{
	ans = 0;

	// �ٿ��� ��Ʈ�� ���� �ִ� ���� ���
	int ret = getHeight(root);

	// �� - ��, �� - ��Ʈ �� ū ��
	return max(ans, ret);
}

int main()
{
	// �׽�Ʈ ���̽�, ���� ����, x y ��ġ, ������
	int C, N, x, y, r;
	cin >> C;

	while (C--)
	{
		cin >> N;
		vector<Node*> tree;

		// �� �Է�
		for (int i = 0; i < N; i++)
		{
			cin >> x >> y >> r;
			tree.push_back(new Node(x, y, r));
		}

		// Ʈ�� ����
		makeTree(tree);

		// ��� ���
		cout << solve(tree[0]) << endl;
	}

	return 0;
}