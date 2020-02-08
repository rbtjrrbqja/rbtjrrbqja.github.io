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
	cout << "������ ���� N �Է�(0 ~ N - 1): "; cin >> N;
	adj = vector<vector<int>>(N, vector<int>(N, 0));
	deg = vector<int>(N, 0);

	int E;
	cout << "������ ���� E �Է�: "; cin >> E;

	for (int i = 0; i < E; i++)
	{
		int a, b;
		cout << "������ ���۰� �� ���� �Է�(�����): "; cin >> a >> b;
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
���Ϸ� ��Ŷ O
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

���Ϸ� ��Ŷ X
5
5
0 1
0 2
1 3
2 3
3 4

*/