// 2020-01-27
// algospot FORTRESS
// https://algospot.com/judge/problem/read/FORTRESS

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 벽 클래스
class Wall
{
public:
	int x, y, r;
	Wall(int x, int y, int r) : x(x), y(y), r(r) { }
};

// 노드 클래스
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

// 오른쪽이 왼쪽 안에 포함되는지 확인
bool isRInL(const Node* l, const Node* r)
{
	double dir = sqrt(pow(r->getWall().x - l->getWall().x, 2) + 
		              pow(r->getWall().y - l->getWall().y, 2));

	return l->getWall().r >= dir + r->getWall().r ? true : false;
}

void makeTree(vector<Node*>& tree)
{
	int N = tree.size();

	// 부모 노드 선택
	for (int i = 0; i < N; i++) {
		Node* parent = tree[i];

		// 자식 노드 선택
		for (int j = 1; j < N; j++) {

			if (i == j)
				continue;

			Node* child = tree[j];

			// 자식이 부모에 포함되면
			if (isRInL(parent, child))
			{
				bool check = true;

				// 자식과 부모사이에 다른 원이 있는지 확인
				for (int k = 1; k < N; k++) {
					if (j == k || i == k)
						continue;

					// 다른원이 존재
					if (isRInL(tree[k], child) && isRInL(parent, tree[k])) {
						check = false;
						break;
					}
				}

				// 다른원이 존재하지 않으면 부모 자식 관계 확정
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

	// 오름차순
	sort(tmp.begin(), tmp.end());

	// 잎에서 다른 잎으로 가는 최대 성벽 경로
	if (n >= 2)
		ans = max(ans, tmp[n - 2] + tmp[n - 1] + 2);
	
	// 높이 반환
	return tmp.back() + 1;
}

int solve(Node* root)
{
	ans = 0;

	// 잎에서 루트로 가는 최대 성벽 경로
	int ret = getHeight(root);

	// 잎 - 잎, 잎 - 루트 중 큰 값
	return max(ans, ret);
}

int main()
{
	// 테스트 케이스, 원의 개수, x y 위치, 반지름
	int C, N, x, y, r;
	cin >> C;

	while (C--)
	{
		cin >> N;
		vector<Node*> tree;

		// 원 입력
		for (int i = 0; i < N; i++)
		{
			cin >> x >> y >> r;
			tree.push_back(new Node(x, y, r));
		}

		// 트리 생성
		makeTree(tree);

		// 답안 출력
		cout << solve(tree[0]) << endl;
	}

	return 0;
}
