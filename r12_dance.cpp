/*
Танец точек
На прямой располагается 1<=N<=10000 точек с целочисленными координатами −10e9<=Vi<=10e9.
Каждой из точек разрешается сделать ровно одно движение (танцевальное па) в любом направлении на расстояние не больше 0<=L<=10e8 и остановиться на другой позиции.
Какое минимальное количество точек может оказаться после окончания танца (все точки после танца, оказывающиеся на одной позиции сливаются в одну)?

Input format
L N
V1
V2
...
VN

Output format
MinimalNumberOfPoints

Examples
Input
10 5
30 3 14 19 21

Output
2
*/

#include <iostream>
#include <vector>
#include <algorithm>

long long readLL() {
	char ch;
	while (((ch = getchar()) < '0' || ch > '9') && ch != '-');

	bool minus = false;
	long long result;

	if (ch == '-') {
		minus = true;
		result = getchar() - '0';
	}
	else {
		result = ch - '0';
	}

	while ((ch = getchar()) >= '0' && ch <= '9')
		result = result * 10 + ch - '0';

	return minus ? -result : result;
}


int main()
{
	int L = readLL()*2, N = readLL();
	std::vector<long long> vector(N);

	for (int i = N-1; i >= 0; i--) {
		vector[i]=readLL();
	}

	std::sort(vector.begin(),vector.end());

	// the lowest element stays at place but all the other can hop for L (doubled L) to the left
	long long center = vector[0];
	int counter = 1;
	for (int i = 1; i < N; i++) {
		if (vector[i] - center <= L)continue;
		center = vector[i];
		counter++;
	}

    std::cout << counter << std::endl;
    return 0;
}