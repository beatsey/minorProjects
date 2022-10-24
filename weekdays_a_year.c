/*
В некоторой стране действует Григорианский календарь. В добавление к выходным дням субботы и воскресенья выходными объявляются 1, 2, 4, 8, 16, 32, 64, 128 и 256 день в году (1 января считается днем 1). Если такой день уже приходится на выходной, он не переносится, то есть дополнительный выходной “сгорает”.

На стандартном потоке ввода задается год (от 1902 до 2037). На стандартный поток вывода напечатайте количество выходных дней в этом году.
*/

#include <stdio.h>
#include <stdlib.h>

// Проверка на високосный год
int IsLeapYear(int year) {
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}
/*
0 - пн
1 - вт
...
6 - вс
*/
int dayofweek(int d, int m, int y)
{
    int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d - 1) % 7;
}

int daysinmonth(int month, int isleap)
{
    if (month < 8) {
        if (month == 2)
            return isleap ? 29 : 28;
    
        return (month % 2 == 0) ? 30 : 31;
    }

    return (month % 2 == 0) ? 31 : 30;
}

int checkpoweroftwo(int d){
    for(int i=0;i<=8;i++){
        if (d == (1 << i)){
            return 1;
        }
    }
    return 0;
}

int main (int argc, const char *argv[])
{
    int year;
    scanf("%d", &year);
    int isleap = IsLeapYear(year);
    int dayinyear = 1;
    int counter = 0;
    
    for(int m=1;m<=12;m++){
        int days = daysinmonth(m, isleap);
        for(int d=1; d<=days; d++, dayinyear++){
            int weekday = dayofweek(d, m, year);
            if (weekday >= 5 || checkpoweroftwo(dayinyear))
                counter++;
        }
    }
    printf("%d\n", counter);
    return 0;
}
