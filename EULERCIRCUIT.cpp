#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>>adj;
vector<int> deg;

void getEulerCircuit(int here, vector<int>& circuit)
{
	for (int i = 0; i < adj[here].size(); i++)
	{
		while (adj[here][i])
		{
			adj[here][i]--;
			adj[i][here]--;
			getEulerCircuit(i, circuit);
		}
	}
	circuit.push_back(here);
}

int main()
{
	int N;
	cout << "정점의 개수 N 입력(0 ~ N - 1): "; cin >> N;
	adj = vector<vector<int>>(N, vector<int>(N, 0));
	deg = vector<int>(N, 0);

	int E;
	cout << "간선의 개수 E 입력: "; cin >> E;

	for (int i = 0; i < E; i++)
	{
		int a, b;
		cout << "간선의 시작과 끝 정점 입력(양방향): "; cin >> a >> b;
		adj[a][b] = 1;
		adj[b][a] = 1;

		deg[a]++; deg[b]++;
	}

	for (int i = 0; i < N; i++) {
		if (deg[i] % 2 != 0) {
			cout << "No Euler Circuit\n";
			return 0;
		}
	}

	vector<int> circuit;
	getEulerCircuit(0, circuit);

	for (int i = circuit.size() - 1; i >= 0; i--)
		cout << circuit[i] << " ";
	cout << endl;

	return 0;
}

/*
오일러 서킷 O
8
9
0 1
0 4
1 2
2 3
3 4
4 5
4 7
5 6
6 7

오일러 서킷 X
5
5
0 1
0 2
1 3
2 3
3 4

*/