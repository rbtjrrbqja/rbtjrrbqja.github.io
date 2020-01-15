// 2020-01-14
// algospot WILDCARD
// https://algospot.com/judge/problem/read/WILDCARD
// *** 나중에 다시 풀기 필요 *** //

#include <iostream>
#include <vector>
#include <memory.h>
#include <algorithm>

using namespace std;

int cache[101][101];
string W, S;

bool wildCardCompare1(const string& wildCard, const string& word)
{
	int idx = 0;
	int wildSize = wildCard.length(), wordSize = word.length();

	while (idx < wildSize && idx < wordSize &&
		(wildCard[idx] == '?' || wildCard[idx] == word[idx]))
		idx++;

	if (idx == wildSize) // wildCard의 끝에 도달
		return idx == wordSize;

	if (wildCard[idx] == '*')
		for (int i = 0; i <= wordSize - idx; i++)
			if (wildCardCompare1(wildCard.substr(idx + 1), word.substr(idx + i)))
				return true;

	return false;
}

int wildCardCompare2(int w, int s)
{
	if (cache[w][s] != -1)
		return cache[w][s];

	int Wsize = W.length(), Ssize = S.length();

	while (w < Wsize && s < Ssize &&
		(W[w] == '?' || W[w] == S[s])) {
		w++; s++;
	}

	if (w == Wsize)
		return cache[w][s] = (s == Ssize);

	if (W[w] == '*')
		for (int i = 0; i <= Ssize - w; i++)
			if (wildCardCompare2(w + 1, s + i))
				return cache[w][s] = 1;

	return cache[w][s] = 0;
}

int wildCardCompare3(int w, int s)
{
	if (cache[w][s] != -1)
		return cache[w][s];

	int Wsize = W.length(), Ssize = S.length();

	while (w < Wsize && s < Ssize &&
		(W[w] == '?' || W[w] == S[s])) {
		return cache[w][s] = wildCardCompare3(w + 1, s + 1);
	}

	if (w == Wsize)
		return cache[w][s] = (s == Ssize);

	if (W[w] == '*')
			if (wildCardCompare3(w + 1, s) || (s < Ssize && wildCardCompare3(w, s + 1)))
				return cache[w][s] = 1;

	return cache[w][s] = 0;
}

int main()
{
	int C, N;

	cin >> C;

	while (C--)
	{
		vector<string> answer;
		cin >> W >> N;

		while(N--)
		{
			memset(cache, -1, sizeof(cache));
			cin >> S;
			
			/*
			if (wildCardCompare1(W, S))
				answer.push_back(S);
			*/
			
			/*
			if (wildCardCompare2(0, 0) > 0)
				answer.push_back(S);
			*/
			
			if(wildCardCompare3(0,0) > 0)
				answer.push_back(S);
			
		}

		sort(answer.begin(), answer.end());
		for (int i = 0; i < answer.size(); i++)
			cout << answer[i] << endl;
	}

	return 0;
}