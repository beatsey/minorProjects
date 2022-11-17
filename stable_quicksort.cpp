/*
Стабильная сортировка
Требуется реализовать стабильную сортировку для следующей задачи.
Выведите фамилии и имена абитуриентов, подавших документы на поступление в ВУЗ в порядке убывания их среднего балла по ЕГЭ.

Про каждого ученика известны их фамилии, имена и баллы ЕГЭ по следующим предметам:
информатика, математика и русский язык.

Формат ввода
В первой строке идет число N (1<=N<=10^5) - количество абитуриентов, подавших документы.
Далее идет N строк - описания ученика в формате "surname name inf_points math_points rus_points", где "surname" - строки длины не более 40, "*_points" - баллы за экзамены (целые числа от нуля до ста включительно).

Формат вывода
Необходимо вывести пары фамилия - имя по одной на строке, разделяя фамилию и имя одним пробелом. Выводить баллы не нужно. Если несколько учащихся имеют одинаковые средние баллы, то их нужно выводить в порядке, заданном во входных данных.


Примеры
2
Markov Alexander 100 99 98
Ivanov Ivan 99 98 98

Markov Alexander
Ivanov Ivan


3
Markov Alexander 75 90 90
Sergey Petrov 100 50 100
Petrov Petr 99 94 71

Petrov Petr
Markov Alexander
Sergey Petrov


6
A A 90 90 90
B B 90 90 90
C C 90 90 90
D D 90 90 90
E E 90 90 90
F F 90 90 90

A A
B B
C C
D D
E E
F F
*/

#include <iostream>

struct person {
    char name[41];
    char surname[41];
    int score;
    int pos;
};

void quicksort(person* arr, int left, int right) {
    if (right <= left)
        return;

    int num = (left + right) / 2;
    person pivot = arr[num];
    arr[num] = arr[right];
    arr[right] = pivot;

    int r = right - 1;
    int l = left;

    while (true) {
        for (; l <= right; l++)
            if (arr[l].score < pivot.score || arr[l].score == pivot.score && arr[l].pos >= pivot.pos)
                break;

        for (; r >= l; r--)
            if (arr[r].score > pivot.score || arr[r].score == pivot.score && arr[r].pos < pivot.pos)
                break;

        if (l < r) {
            person tmp = arr[l];
            arr[l] = arr[r];
            arr[r] = tmp;
            l++;
            r--;
        }
        else {
            arr[right] = arr[l];
            arr[l] = pivot;
            quicksort(arr, left, l - 1);
            quicksort(arr, l + 1, right);
            return;
        }
    }
}

int main()
{
    int n;
    std::cin >> n;

    person* arr = new person[n];
    for (int i = 0; i < n; i++) {
        int a, b, c;
        std::cin >> arr[i].name >> arr[i].surname >> a >> b >> c;
        arr[i].score = a + b + c;
        arr[i].pos = i;
    }

    quicksort(arr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        std::cout << arr[i].name << ' ' << arr[i].surname << std::endl;
    }
    delete[] arr;
}