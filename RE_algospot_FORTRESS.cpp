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
public:
	Node(int x, int y, int r) : w(Wall(x, y, r)), parent(NULL) { }
	~Node()
	{
		delete parent;

		for (int i = 0; i < children.size(); i++)
			delete children[i];
	}

	friend bool isRInL(const Node* r, const Node* l);
	friend void makeTree(vector<Node*>& tree);
	friend int getHeight(const Node* root);
};

// ������ ������ �ȿ� ���ԵǴ��� Ȯ��
bool isRInL(const Node* l, const Node* r)
{
	double dir = sqrt(pow(r->w.x - l->w.x, 2) + pow(r->w.y - l->w.y, 2));

	return l->w.r >= dir + r->w.r ? true : false;
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
					child->parent = parent;
					parent->children.push_back(child);
				}
			}
		}
	}
}

int ans = 0;

int getHeight(const Node* root)
{
	int n = root->children.size();
	vector<int> tmp;

	for (int i = 0; i < n; i++)
		tmp.push_back(getHeight(root->children[i]));

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