// 알고리즘 003분반 
// 컴퓨터공학과 
// 12151466 4학년 장규석

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

struct Vertax;                 // 정점 (도시)
struct Edge;                   // 간선 (도로)
struct VertaxSet;              // Union Set 자료구조

struct VertaxSet               // Union Set 자료구조
{
	list<Vertax*> setList;     // 같은 집합에 있는 Vertax List
	int weight;	               // 총 연결된 간선(도로) 비용 

	VertaxSet(Vertax* _vertax)
	{
		setList.push_back(_vertax);
		weight = 0;
	}
};

struct Vertax					// 정점 (도시)
{
	int id;						// 도시 ID
	string name;				// 도시 이름
	int population;				// 도시 인구
	VertaxSet* set;				// 현재 이 도시가 포함된 집합

	Vertax(int _id, string _name, int _population)
	{
		id = _id;
		name = _name;
		population = _population;

		set = new VertaxSet(this);
	}
};

struct Edge {     // 간선 (도로)

	int from;     // 시작
	int to;       // 끝
	int weight;   // 비용

	Edge(int _from, int _to, int _weight)
	{
		from = _from;
		to = _to;
		weight = _weight;
	}
};

// 정점, 간선, 질의 수
int N, M, q;

// 상수시간에 Vertax에 접근하기위한 array
// vertaxArr[Vertax ID] = vertaxVector Index
int vertaxArr[1000000];

// Vertax*, Edge* 저장 vector
vector<Vertax*> vertaxVector;
vector<Edge*> edgeVector;

// edgeVector를 sort하기 위한 compare 함수
bool cmp(Edge*, Edge*);

// Union 기능 구현 함수
void Union(Vertax*, Vertax*, int);
// 어느쪽으로 Union을 수행할지 결정하는 함수
void UnionVertaxSet(Vertax*, Vertax*, int);

// 기본적인 Kruskal 알고리즘 구현
// *실제로는 쓰이지 않음*
void Kruskal();

// 각각의 쿼리 수행을 위한 함수
void QueryN(int, int);
void QueryL(int);
void QueryI();
void QueryF(int, int);
void QueryW(int);
void QueryQ();

int main()
{
	// 도시, 도로, 질의 수 입력
	cin >> N >> M >> q;

	// 도시 정보 입력
	for (int i = 0; i < N; i++)
	{
		int id, pop; string name;
		cin >> id >> name >> pop;

		vertaxArr[id] = (int)vertaxVector.size();
		vertaxVector.push_back(new Vertax(id, name, pop));
	}

	// 도로 정보 입력
	for (int i = 0; i < M; i++)
	{
		int from, to, weight;
		cin >> from >> to >> weight;

		edgeVector.push_back(new Edge{ from, to, weight });
	}

	sort(edgeVector.begin(), edgeVector.end(), cmp);

	// 질의 입력
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

// a가 포함된 VertaxSet에 b가 포함된 VertaxSet을 추가하는 함수
void Union(Vertax* a, Vertax* b, int _weight)
{
	// Weight 갱신
	a->set->weight = a->set->weight + b->set->weight + _weight;

	// b가 포함된 집합의 도시들이 a VertaxSet을 가리킴
	// set 갱신
	list<Vertax*> tmp = b->set->setList;

	for (auto& v : tmp)
		v->set = a->set;

	// a list 의 뒤쪽에 b list 를 잘라 붙인다.
	a->set->setList.splice(a->set->setList.end(), tmp);
}

// union 함수
void UnionVertaxSet(Vertax* a, Vertax* b, int _weight)
{
	int sizeA = a->set->setList.size();
	int sizeB = b->set->setList.size();

	// 집합의 크기가 더 큰쪽에 Union 한다
	if (sizeA > sizeB)
		Union(a, b, _weight);
	else if (sizeA < sizeB)
		Union(b, a, _weight);
	// 크기가 같다면 leader의 ID가 작은쪽으로 Union한다
	else {
		if (a->set->setList.front()->id < b->set->setList.front()->id)
			Union(a, b, _weight);
		else
			Union(b, a, _weight);
	}
}

// 기본적인 Kruskal 알고리즘 구현
void Kruskal()
{
	while (!edgeVector.empty())
	{
		Edge* currentEdge = edgeVector.back();
		edgeVector.pop_back();

		Vertax* fromV = vertaxVector[vertaxArr[currentEdge->from]];
		Vertax* toV = vertaxVector[vertaxArr[currentEdge->to]];

		// 포함된 집합이 다르다 == leader가 다르다
		if (fromV->set != toV->set) {
			UnionVertaxSet(fromV, toV, currentEdge->weight);
		}
	}
}

// Query N : 특정 도시가 포함된 연결리스트의 내부 정보 파악
void QueryN(int v, int k)
{
	Vertax* vertax = vertaxVector[vertaxArr[v]];

	// v가 포함된 집합엣서 헤드로부터 k번째 노드를 출력
	if (k < (int)vertax->set->setList.size())
	{
		list<Vertax*>::iterator it;
		it = vertax->set->setList.begin();

		for (int i = 0; i < k; ++i)
			++it;

		// 도시의 번호 도시의 이름
		cout << (*it)->id << " " << (*it)->name << "\n";
	}
	// k 번째 도시정보가 존재하지 않음
	else
	{
		cout << "no exist\n";
	}
}

// Query L : 특정 도시가 포함된 연결리스트의 크기
void QueryL(int v)
{
	Vertax* vertax = vertaxVector[vertaxArr[v]];

	// v 가 포함된 집합의 List의 element 개수
	cout << vertax->set->setList.size() << "\n";
}

// Query I : Kruskal 알고리즘에서 하나의 반복(iteration) 진행
void QueryI()
{
	Edge* currentEdge = edgeVector.back();
	edgeVector.pop_back();

	Vertax* fromV = vertaxVector[vertaxArr[currentEdge->from]];
	Vertax* toV = vertaxVector[vertaxArr[currentEdge->to]];

	// 해당 반복에서 Union 가능
	if (fromV->set != toV->set) {
		UnionVertaxSet(fromV, toV, currentEdge->weight);

		// 해당 반복에서 MST를 찾음
		if ((int)fromV->set->setList.size() == N - 1)
		{
			// 새로운 집합의leader id, 새로운 집합의 크기, 최종 완성된 MST 집합의 leader id, MST의 모든 비용 합
			cout << fromV->set->setList.front()->id << " " << fromV->set->setList.size() << " ";
			cout << fromV->set->setList.front()->id << " " << fromV->set->weight << "\n";
		}
		// 해당 반복에서 union 성공
		else
		{
			// 새로운 집합의leader id, 새로운 집합의 크기
			cout << fromV->set->setList.front()->id << " " << fromV->set->setList.size() << "\n";
		}
	}
	// cycle 발생으로 해당 반복에서 Union 불가능
	else
	{
		cout << "not union\n";
	}
}

// Query F : 두 도시가 같은 집합에 속하는지 확인
void QueryF(int v1, int v2)
{
	Vertax* vertax1 = vertaxVector[vertaxArr[v1]];
	Vertax* vertax2 = vertaxVector[vertaxArr[v2]];

	// 같은 집합
	if (vertax1->set == vertax2->set)
	{
		// True, 집합의 leader id
		cout << "True " << vertax1->set->setList.front()->id << "\n";
	}
	// 다른 집합
	else
	{
		// False, 각 도시의 집합의 leader id
		cout << "False " << vertax1->set->setList.front()->id << " " << vertax2->set->setList.front()->id << "\n";
	}
}

// Query W : 임의의 도시를 포함하는 집합의 모든 포장도로의 길이
void QueryW(int v)
{
	Vertax* vertax = vertaxVector[vertaxArr[v]];
	cout << vertax->set->weight << "\n";
}

// Query Q : 알고리즘의 나머지 단계 연속수행 및 프로그램 종료
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

	// MST의 leader id, 모든 비용의 합
	cout << vertaxVector[0]->set->setList.front()->id << " " << vertaxVector[0]->set->weight << "\n";
}

// edgeVector 정렬 함수
bool cmp(Edge* a, Edge* b)
{
	// edgeVector는 vector 자료형이기 때문에 pop_back 만 가능
	// 따라서 내림차순 정렬후 뒤에서부터 pop_back을 수행한다
	
	if (a->weight == b->weight)
	{
		int aPop = vertaxVector[vertaxArr[a->from]]->population + vertaxVector[vertaxArr[a->to]]->population;
		int bPop = vertaxVector[vertaxArr[b->from]]->population + vertaxVector[vertaxArr[b->to]]->population;

		
		if (aPop == bPop)
		{
			int minA = a->from > a->to ? a->to : a->from;
			int minB = b->from > b->to ? b->to : b->from;

			// 인구수도 같다면 최소 도시 ID 내림차순 정렬
			return minA > minB;
		}

		// 비용이 같다면 도시의 인구수의 합의 오름차순 정렬
		return aPop < bPop;
	}

	// 비용은 내림차순 정렬
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