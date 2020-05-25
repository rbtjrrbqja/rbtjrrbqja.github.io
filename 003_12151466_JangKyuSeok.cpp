// �˰��� 003�й� 
// ��ǻ�Ͱ��а� 
// 12151466 4�г� ��Լ�

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

struct Vertax;                 // ���� (����)
struct Edge;                   // ���� (����)
struct VertaxSet;              // Union Set �ڷᱸ��

struct VertaxSet               // Union Set �ڷᱸ��
{
	list<Vertax*> setList;     // ���� ���տ� �ִ� Vertax List
	int weight;	               // �� ����� ����(����) ��� 

	VertaxSet(Vertax* _vertax)
	{
		setList.push_back(_vertax);
		weight = 0;
	}
};

struct Vertax					// ���� (����)
{
	int id;						// ���� ID
	string name;				// ���� �̸�
	int population;				// ���� �α�
	VertaxSet* set;				// ���� �� ���ð� ���Ե� ����

	Vertax(int _id, string _name, int _population)
	{
		id = _id;
		name = _name;
		population = _population;

		set = new VertaxSet(this);
	}
};

struct Edge {     // ���� (����)

	int from;     // ����
	int to;       // ��
	int weight;   // ���

	Edge(int _from, int _to, int _weight)
	{
		from = _from;
		to = _to;
		weight = _weight;
	}
};

// ����, ����, ���� ��
int N, M, q;

// ����ð��� Vertax�� �����ϱ����� array
// vertaxArr[Vertax ID] = vertaxVector Index
int vertaxArr[1000000];

// Vertax*, Edge* ���� vector
vector<Vertax*> vertaxVector;
vector<Edge*> edgeVector;

// edgeVector�� sort�ϱ� ���� compare �Լ�
bool cmp(Edge*, Edge*);

// Union ��� ���� �Լ�
void Union(Vertax*, Vertax*, int);
// ��������� Union�� �������� �����ϴ� �Լ�
void UnionVertaxSet(Vertax*, Vertax*, int);

// �⺻���� Kruskal �˰��� ����
// *�����δ� ������ ����*
void Kruskal();

// ������ ���� ������ ���� �Լ�
void QueryN(int, int);
void QueryL(int);
void QueryI();
void QueryF(int, int);
void QueryW(int);
void QueryQ();

int main()
{
	// ����, ����, ���� �� �Է�
	cin >> N >> M >> q;

	// ���� ���� �Է�
	for (int i = 0; i < N; i++)
	{
		int id, pop; string name;
		cin >> id >> name >> pop;

		vertaxArr[id] = (int)vertaxVector.size();
		vertaxVector.push_back(new Vertax(id, name, pop));
	}

	// ���� ���� �Է�
	for (int i = 0; i < M; i++)
	{
		int from, to, weight;
		cin >> from >> to >> weight;

		edgeVector.push_back(new Edge{ from, to, weight });
	}

	sort(edgeVector.begin(), edgeVector.end(), cmp);

	// ���� �Է�
	for (int i = 0; i < q; i++)
	{
		char q;
		int v, k, v1, v2;
		cin >> q;

		switch (q)
		{
			case 'N':
				cin >> v >> k;
				QueryN(v, k);
				break;
			case 'L':
				cin >> v;
				QueryL(v);
				break;
			case 'I':
				QueryI();
				break;
			case 'F':
				cin >> v1 >> v2;
				QueryF(v1, v2);
				break;
			case 'W':
				cin >> v;
				QueryW(v);
				break;
			case 'Q':
				QueryQ();
				break;
			default:
				break;
		}

	}

	return 0;
}

// a�� ���Ե� VertaxSet�� b�� ���Ե� VertaxSet�� �߰��ϴ� �Լ�
void Union(Vertax* a, Vertax* b, int _weight)
{
	// Weight ����
	a->set->weight = a->set->weight + b->set->weight + _weight;

	// b�� ���Ե� ������ ���õ��� a VertaxSet�� ����Ŵ
	// set ����
	list<Vertax*> tmp = b->set->setList;

	for (auto& v : tmp)
		v->set = a->set;

	// a list �� ���ʿ� b list �� �߶� ���δ�.
	a->set->setList.splice(a->set->setList.end(), tmp);
}

// union �Լ�
void UnionVertaxSet(Vertax* a, Vertax* b, int _weight)
{
	int sizeA = a->set->setList.size();
	int sizeB = b->set->setList.size();

	// ������ ũ�Ⱑ �� ū�ʿ� Union �Ѵ�
	if (sizeA > sizeB)
		Union(a, b, _weight);
	else if (sizeA < sizeB)
		Union(b, a, _weight);
	// ũ�Ⱑ ���ٸ� leader�� ID�� ���������� Union�Ѵ�
	else {
		if (a->set->setList.front()->id < b->set->setList.front()->id)
			Union(a, b, _weight);
		else
			Union(b, a, _weight);
	}
}

// �⺻���� Kruskal �˰��� ����
void Kruskal()
{
	while (!edgeVector.empty())
	{
		Edge* currentEdge = edgeVector.back();
		edgeVector.pop_back();

		Vertax* fromV = vertaxVector[vertaxArr[currentEdge->from]];
		Vertax* toV = vertaxVector[vertaxArr[currentEdge->to]];

		// ���Ե� ������ �ٸ��� == leader�� �ٸ���
		if (fromV->set != toV->set) {
			UnionVertaxSet(fromV, toV, currentEdge->weight);
		}
	}
}

// Query N : Ư�� ���ð� ���Ե� ���Ḯ��Ʈ�� ���� ���� �ľ�
void QueryN(int v, int k)
{
	Vertax* vertax = vertaxVector[vertaxArr[v]];

	// v�� ���Ե� ���տ��� ���κ��� k��° ��带 ���
	if (k < (int)vertax->set->setList.size())
	{
		list<Vertax*>::iterator it;
		it = vertax->set->setList.begin();

		for (int i = 0; i < k; ++i)
			++it;

		// ������ ��ȣ ������ �̸�
		cout << (*it)->id << " " << (*it)->name << "\n";
	}
	// k ��° ���������� �������� ����
	else
	{
		cout << "no exist\n";
	}
}

// Query L : Ư�� ���ð� ���Ե� ���Ḯ��Ʈ�� ũ��
void QueryL(int v)
{
	Vertax* vertax = vertaxVector[vertaxArr[v]];

	// v �� ���Ե� ������ List�� element ����
	cout << vertax->set->setList.size() << "\n";
}

// Query I : Kruskal �˰��򿡼� �ϳ��� �ݺ�(iteration) ����
void QueryI()
{
	Edge* currentEdge = edgeVector.back();
	edgeVector.pop_back();

	Vertax* fromV = vertaxVector[vertaxArr[currentEdge->from]];
	Vertax* toV = vertaxVector[vertaxArr[currentEdge->to]];

	// �ش� �ݺ����� Union ����
	if (fromV->set != toV->set) {
		UnionVertaxSet(fromV, toV, currentEdge->weight);

		// �ش� �ݺ����� MST�� ã��
		if ((int)fromV->set->setList.size() == N - 1)
		{
			// ���ο� ������leader id, ���ο� ������ ũ��, ���� �ϼ��� MST ������ leader id, MST�� ��� ��� ��
			cout << fromV->set->setList.front()->id << " " << fromV->set->setList.size() << " ";
			cout << fromV->set->setList.front()->id << " " << fromV->set->weight << "\n";
		}
		// �ش� �ݺ����� union ����
		else
		{
			// ���ο� ������leader id, ���ο� ������ ũ��
			cout << fromV->set->setList.front()->id << " " << fromV->set->setList.size() << "\n";
		}
	}
	// cycle �߻����� �ش� �ݺ����� Union �Ұ���
	else
	{
		cout << "not union\n";
	}
}

// Query F : �� ���ð� ���� ���տ� ���ϴ��� Ȯ��
void QueryF(int v1, int v2)
{
	Vertax* vertax1 = vertaxVector[vertaxArr[v1]];
	Vertax* vertax2 = vertaxVector[vertaxArr[v2]];

	// ���� ����
	if (vertax1->set == vertax2->set)
	{
		// True, ������ leader id
		cout << "True " << vertax1->set->setList.front()->id << "\n";
	}
	// �ٸ� ����
	else
	{
		// False, �� ������ ������ leader id
		cout << "False " << vertax1->set->setList.front()->id << " " << vertax2->set->setList.front()->id << "\n";
	}
}

// Query W : ������ ���ø� �����ϴ� ������ ��� ���嵵���� ����
void QueryW(int v)
{
	Vertax* vertax = vertaxVector[vertaxArr[v]];
	cout << vertax->set->weight << "\n";
}

// Query Q : �˰����� ������ �ܰ� ���Ӽ��� �� ���α׷� ����
void QueryQ()
{
	while (!edgeVector.empty())
	{
		Edge* currentEdge = edgeVector.back();
		edgeVector.pop_back();

		Vertax* fromV = vertaxVector[vertaxArr[currentEdge->from]];
		Vertax* toV = vertaxVector[vertaxArr[currentEdge->to]];

		if (fromV->set != toV->set) {
			UnionVertaxSet(fromV, toV, currentEdge->weight);
		}
	}

	// MST�� leader id, ��� ����� ��
	cout << vertaxVector[0]->set->setList.front()->id << " " << vertaxVector[0]->set->weight << "\n";
}

// edgeVector ���� �Լ�
bool cmp(Edge* a, Edge* b)
{
	// edgeVector�� vector �ڷ����̱� ������ pop_back �� ����
	// ���� �������� ������ �ڿ������� pop_back�� �����Ѵ�
	
	if (a->weight == b->weight)
	{
		int aPop = vertaxVector[vertaxArr[a->from]]->population + vertaxVector[vertaxArr[a->to]]->population;
		int bPop = vertaxVector[vertaxArr[b->from]]->population + vertaxVector[vertaxArr[b->to]]->population;

		
		if (aPop == bPop)
		{
			int minA = a->from > a->to ? a->to : a->from;
			int minB = b->from > b->to ? b->to : b->from;

			// �α����� ���ٸ� �ּ� ���� ID �������� ����
			return minA > minB;
		}

		// ����� ���ٸ� ������ �α����� ���� �������� ����
		return aPop < bPop;
	}

	// ����� �������� ����
	return a->weight > b->weight;
}

// sample Input
/*
9 19 16
10 seoul 123
20 dajeon 325
40 newyork 951
30 tokyo 157
50 london 358
60 paris 675
70 kairo 6990
80 cicago 1254
90 sandiego 695
10 20 337
10 30 1404
20 30 1235
20 50 2342
30 50 1121
10 40 1846
40 30 802
50 60 946
50 70 1090
50 90 1258
60 70 184
70 80 144
70 90 187
10 90 2704
40 60 621
40 70 740
40 80 849
40 90 867
30 70 1391
I
I
I
F 60 80
F 90 10
N 90 2
N 90 1
N 90 0
L 50
L 60
I
W 70
W 20
I
I
Q
*/