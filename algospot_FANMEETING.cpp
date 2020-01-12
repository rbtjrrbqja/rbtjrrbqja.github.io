// 2020-01-12
// algospot FANMEETING
// https://algospot.com/judge/problem/read/FANMEETING

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 일반적인 곱셈으로는 시간초과가 발생한다.
// 이 문제에서는 karatsuba 를 사용해야 통과 가능
vector<int> multiply(const vector<int>& idol, const vector<int>& fan)
{
	int Isize = idol.size(), Fsize = fan.size();
	vector<int> ret(Isize + Fsize - 1, 0);

	for (int i = 0; i < Isize; i++)
		for (int j = 0; j < Fsize; j++)
			ret[i + j] += idol[i] * fan[j];

	return ret;
}

// karatsuba 알고리즘 구현
void addTo(vector<int>& a, const vector<int>& b, int k)
{
	int Asize = a.size(), Bsize = b.size();

	for (int i = 0; i < Bsize + k - Asize; i++)
		a.push_back(0);

	for (int i = 0; i < Bsize; i++)
		a[i + k] += b[i];
}

// a >= b
void subFrom(vector<int>& a, const vector<int>& b)
{
	int Asize = a.size(), Bsize = b.size();

	for (int i = 0; i < Bsize; i++)
		a[i] -= b[i];
}

// karatsuba
vector<int> karatsuba(const vector<int>& a, const vector<int>& b)
{
	int Asize = a.size(), Bsize = b.size();

	if (Asize < Bsize)
		return karatsuba(b, a);

	if (Asize == 0 || Bsize == 0)
		return vector<int>();

	if (Asize <= 50)
		return multiply(a, b);

	int half = Asize / 2;

	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(Bsize, half));
	vector<int> b1(b.begin() + min<int>(Bsize, half), b.end());
	// a * b = (a1 * b1) * 10 ^ 2 half + (a1 * b0 + a0 * b1) * 10 ^ half + (a0 * b0)

	vector<int> z2 = karatsuba(a1, b1);
	// z2 = a1 * b1

	vector<int> z0 = karatsuba(a0, b0);
	// z0 = a0 * b0

	addTo(a0, a1, 0); addTo(b0, b1, 0);
	// a0 = a0 + a1 , b0 = b0 + b1

	vector<int> z1 = karatsuba(a0, b0);
	subFrom(z1, z0);
	subFrom(z1, z2);
	// z1 = (a0 + a1) * (b0 + b1) - z2 - z0

	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half + half);

	return ret;
}

int fanMeeting(const vector<int>& idol, const vector<int>& fan)
{
	int Isize = idol.size(), Fsize = fan.size();
	// vector<int> ret = multiply(idol, fan);
	vector<int> ret = karatsuba(idol, fan);
	int count = 0;

	for (int i = Isize - 1; i < Fsize; i++)
		if (ret[i] == 0)
			count++;

	return count;
}

int main()
{
	// 테스트 케이스
	int C;
	cin >> C;

	while (C--)
	{
		vector<int> idol, fan;
		string input;
		
		// 문자열 입력을 0과 1의 입력으로 전환
		// F : 0, M : 1
		cin >> input;
		for (int i = 0; i < input.length(); i++)
			idol.push_back((int)(input[i] == 'M'));

		cin >> input;
		for (int i = input.length() - 1; i >= 0; i--)
			fan.push_back((int)(input[i] == 'M'));
		
		cout << fanMeeting(idol, fan) << endl;
	}
	return 0;
}