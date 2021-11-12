/*
������

�������� � ����� ������ ����� ����� ��� ���� - ������ ������ � �������� �� ����. ������� �� ����� ���������� �������� � �������� � ������� �� ������������� ������� ������ �������. �� ��� ��������: � �������� ���� ������ ���� ��������, ���� � ������� ������ ���� ������� �����������. ��������� �������� - ������, �� ������������ ������������ � ���, ������� ���� �� ����� ������ �����-�� ���� �������� ����� K ��� - �������� ����� ����������� � ���� ������ ����� ��������. ��� ����, ����������, �������� ����� ��������� �� ���� ��� ����� ������. ���� ������ ������� � ���, ����� �� ���������� ������� ���� �������� �� N ���� ������� ��� ����� ����� ������� ������� ������ ������ ����, � ������� �������� ������ � ������� ���, ����� ������� ����� ���� �� ���������� ����� K ��� �� �� ����� �������.
������ ������� ������
� ������ ������ ��� ���� ����� ����� 1 <= N <= 100000 � 1 <= K <= N - ���������� ����, ����� ������� ������ ��� ������ � K - ������������ ���������� ���, ������� ����� ����������� ���� �� ����� �������. � ��������� ������ �������� ����� ��� ���� ������, ��������� �� N �������� ��������� ����. ������ ����� �������� ���� ������� ����, ������ ���� ������������� ������ �����.
������ �������� ������
�� ����� ���� ��������� ������ ������� ��� ����� �����: 1 <= L <= N - ������������ ���������� ���� ������� ��������� � 1 <= d0 <= N - ����� ��� ������. ��������, ��� � ���� ������ �������� �������� ������ ������������ �������� ����.

�������
1 1
a

1 1


6 2
abbbaa

4 3

*/

#include <iostream>

int main() {
	int N, K;
	std::cin >> N >> K;
	getchar();
	char lastChar = ' ';
	int repeatedTimes = 1,	// ���������� �������� � ������� ������������������
		times = 0,			// ����� ������� ������������������
		maxTimes=0,			// ����� ������������ ������������������
		dayOfStart = 0,		// ������ ��� ������ ������������������
		maxDayOfStart=0;	// ������ ��� ������ ������������ ������������������
	for (int i = 0; i < N; i++) {
		char c = getchar();
		if (c!=lastChar) {
			repeatedTimes = 1;
		}
		else if (++repeatedTimes > K) { // ��������� ���������� ��������
			if (maxTimes < times) {
				maxTimes = times;
				maxDayOfStart = dayOfStart;
			}
			times = K - 1;
			repeatedTimes = K;
			dayOfStart = i - K + 1;
		}

		times++;

		lastChar = c;
	}
	if (maxTimes < times) {
		maxTimes = times;
		maxDayOfStart = dayOfStart;
	}

	std::cout << maxTimes << ' ' << (maxDayOfStart+1);

}