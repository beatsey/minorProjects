/*
����������� ���������, ��������� ����� � ���������� ����������� ��������� �� ������� ������. �� ���� �������� ���������� ����� n, ����� �������� ���� n �����. ����� � �� ���������� �� ��������� 1000000. ���� ��������� ����� ����� ���������� ����� ���������, ������� �����������. ����� ����� � ���������� ����������� ���������� ������� ��������� ����� (� ������ ������� ���������� �����, ������� �����������).
4
8 8 8 8

8
9 7 8 3 1 9 7 7

7
4 8 5 7 8 4 9

6
3 3 3 2 2 2

3
6 9 1
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int findMedian(vector<int>& a) {
    // ��� ������� ������� ������� ���� ����� ����������� �������
    if (a.size() % 2 == 0) {
        nth_element(a.begin(), a.begin() + (a.size() - 1) / 2, a.end());
        return a[(a.size() - 1) / 2];
    }
    else {
        // ��� ��������� ������� ������� ���� ����������� �������
        nth_element(a.begin(), a.begin() + a.size() / 2, a.end());
        return a[a.size() / 2];
    }
}

int main() {

    // ������ ������
    int n = 0;
    cin >> n;
    vector<int>v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    
    // ������� ���������� ���������
    unordered_map<int, int> counter;
    for (int i = 0; i < n; i++) {
        // ���� �� ����� ����� � map, �� ����������� �������
        if (counter.find(v[i]) != counter.end())
            counter[v[i]]++;
        else
            counter[v[i]] = 1;
    }

    int maxcounter = 0;
    int minmaxvalue = 0;

    // ��� �� map � ���� ����� ������������������ ����������� �������
    for (unordered_map<int, int>::iterator it = counter.begin(); it != counter.end(); it++) {
        if (it->second > maxcounter || it->second == maxcounter && it->first < minmaxvalue) {
            maxcounter = it->second;
            minmaxvalue = it->first;
        }
    }

    int mediana = findMedian(v);
    cout << minmaxvalue << " " << mediana;

    return 0;
}
