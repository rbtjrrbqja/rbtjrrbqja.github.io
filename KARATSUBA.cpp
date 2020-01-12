#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// 자리 올림 내림
void normalize(vector<int>& a)
{
	int Asize = a.size();

	a.push_back(0);

	for (int i = 0; i < Asize - 1; i++)
	{
		if (a[i] < 0)
		{
			int borrow = (abs(a[i]) + 9) / 10;
			a[i + 1] -= borrow;
			a[i] += borrow * 10;
		}
		else
		{
			a[i + 1] += a[i] / 10;
			a[i] %= 10;
		}
	}

	while (a.size() > 1 && a.back() == 0)
		a.pop_back();
}

// 일반적인 O(N^2) 곱셈 알고리즘
vector<int> multiply(const vector<int>& a, const vector<int>& b)
{
	int Asize = a.size(), Bsize = b.size();
	vector<int> c(Asize + Bsize + 1, 0);

	for (int i = 0; i < Asize; i++)
		for (int j = 0; j < Bsize; j++)
			c[i + j] += a[i] * b[j];

	normalize(c);

	return c;
}

// a += b * 10 ^ k
void addTo(vector<int>& a, const vector<int>& b, int k)
{
	int Asize = a.size(), Bsize = b.size();

	for (int i = 0; i < Bsize + k - Asize; i++)
		a.push_back(0);

	for (int i = 0; i < Bsize; i++)
		a[i + k] += b[i];

	normalize(a);
}

// a >= b
void subFrom(vector<int>& a, const vector<int>& b)
{
	int Asize = a.size(), Bsize = b.size();

	for (int i = 0; i < Bsize; i++)
		a[i] -= b[i];

	normalize(a);
}

// karatsuba
vector<int> karatsuba(const vector<int>& a, const vector<int>& b)
{
	int Asize = a.size(), Bsize = b.size();

	if (Asize < Bsize)
		return karatsuba(b, a);

	if (Asize == 0 || Bsize == 0)
		return vector<int>();

	if (Asize <= 10)
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

int main()
{
	srand((unsigned int)time(NULL));

	vector<int> a, b;
	int Asize = rand() % 30 + 20;
	int Bsize = rand() % 30 + 20;


	for (int i = 0; i < Asize; i++)
		a.push_back(rand() % 9 + 1);

	for (int i = 0; i < Bsize; i++)
		b.push_back(rand() % 9 + 1);

	cout << "a ";
	for (int i = Asize - 1; i >= 0; i--)
		cout << a[i];
	cout << endl;

	cout << "b ";
	for (int i = Bsize - 1; i >= 0; i--)
		cout << b[i];
	cout << endl;

	vector<int> c = karatsuba(a, b);

	int Csize = c.size();

	cout << "c ";
	for (int i = Csize - 1; i >= 0; i--)
		cout << c[i];
	cout << endl;

	return 0;
}