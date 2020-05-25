#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> Pair;

class Graph
{
private:
	int vertaxSize;
	int edgeSize;
	int** edge;
public:
	Graph()
	{
		int inputVertaxSize;
		cout << "노드의 개수를 입력해 주세요 :"; cin >> inputVertaxSize;
		vertaxSize = inputVertaxSize;

		edge = new int* [vertaxSize];

		for (int i = 0; i < vertaxSize; i++)
			edge[i] = new int[vertaxSize];

		for (int i = 0; i < vertaxSize; i++)
			for (int j = 0; j < vertaxSize; j++)
				edge[i][j] = 0;

		int inputEdgeSize;
		cout << "간선의 개수를 입력해 주세요 :"; cin >> inputEdgeSize;
		edgeSize = inputEdgeSize;

		for (int i = 0; i < inputEdgeSize; i++)
		{
			int s, e, w;
			cout << "간선의 정보를 입력해 주세요 :";
			cin >> s >> e >> w;

			edge[s][e] = edge[e][s] = w;
		}
	}

	void Prim(int start)
	{
		int* dist = new int[vertaxSize];
		char *status = new char[vertaxSize];

		for (int i = 0; i < vertaxSize; i++)
			status[i] = 'U';

		priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
		
		pq.push({0, start});
		dist[start] = 0;
	
		while (!pq.empty())
		{
			int current = pq.top().second;
			int weight = pq.top().first;
			pq.pop();

			if (status[current] == 'T')
				continue;

			status[current] = 'T';
			dist[current] = weight;

			cout << "visit : " << current << endl;

			for (int i = 0; i < vertaxSize; i++)
			{
				if (edge[i][current] != 0)
				{
					if (status[i] != 'T')
					{
						cout << "current with : " << i << endl;
						pq.push({edge[i][current], i});
						status[i] = 'F';
					}
				}
			}
		}

		for (int i = 0; i < vertaxSize; i++)
			cout << dist[i] << " ";
		cout << endl;
	}
};

int main()
{
	Graph g;

	g.Prim(0);

	return 0;
}

// sample input
/*
9
15
0 1 2
0 5 9
0 6 5
1 2 4
1 6 6
2 3 2
2 7 5
3 4 1
3 7 1
4 5 6
4 8 3
5 8 1
6 7 5
6 8 2
7 8 4
*/

/*
9
15
0 1 2
0 5 7
0 6 3
1 2 4
1 6 6
2 3 2
2 7 2
3 4 1
3 7 8
4 5 6
4 8 2
5 8 5
6 7 3
6 8 1
7 8 4
*/