#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <chrono>
#include <ctime>
#include <queue>
#include <stack>
#include <deque>
#include <tuple>
#include <functional>
#include <thread>
#include <mutex>
#include <forward_list>
#include <array>
#include <iomanip>
#include <iterator>
#include <regex>
using namespace std;
#define ull unsigned long long
#define ll long long
#define ld long double
#define bigpos INT64_MAX
#define bigneg INT64_MIN
#define pb push_back
#define ppb pop_back
#define ii pair<int, int>
#define endProgram cin.clear();cout.clear();return 0;
int inf = 1000000000;

#include "zoooooo.cpp"

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout << fixed;// << setprecision(10);
	cout.precision(10);

	krolik k(22, "f", "g");
	cat c(11, "a", "b");
	dog d(00, "c", "d");
	cout << "кролик: ";
	cout << k.getAge();
	k.sing();
	cout << k.getName() << '\n';
	cout << "кошка: ";
	cout << c.getAge();
	c.sing();
	cout << c.getName() << '\n';
	cout << "собака: ";
	cout << d.getAge();
	d.sing();
	cout << d.getName() << '\n';
	string m = k.mesto;
	k.mesto = c.mesto;
	c.mesto = m;

	cin.clear();
	cout.clear();
	return 0;
}
