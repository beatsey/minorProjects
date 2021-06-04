void fast_sort(unsigned *begin, unsigned *end)
{
    unsigned *tmparr = new unsigned[end - begin],
        *pointer=begin,
        *tmpArrEnd = tmparr + (end - begin),
        *tmpArrPointer=tmparr;

    unsigned count[1 << 8] = {};
    const unsigned* const countEnd = count + sizeof(count) / sizeof(count[0]);
    unsigned* ptr = count;
    {
        for (; pointer!=end;)
            count[*pointer++ & ((1 << 8) - 1)]++;
        for (; ++ptr != countEnd;)
            *ptr += *(ptr-1);
        for (; pointer!=begin;)
            tmparr[--count[*--pointer & ((1 << 8) - 1)]] = *pointer;
    }
    {
        for (; ptr != count;)
            *--ptr=0;
        for (; tmpArrPointer!=tmpArrEnd;)
            count[(*tmpArrPointer++>>8) & ((1 << 8) - 1)]++;
        for (; ++ptr != countEnd;)
            *ptr += *(ptr - 1);
        for (; tmpArrPointer != tmparr;)
            begin[--count[(*--tmpArrPointer >> 8) & ((1 << 8) - 1)]] = *tmpArrPointer;
    }
    {
        for (; ptr != count;)
            *--ptr = 0;
        for (; pointer != end;)
            count[(*pointer++ >> 16) & ((1 << 8) - 1)]++;
        for (; ++ptr != countEnd;)
            *ptr += *(ptr - 1);
        for (; pointer != begin;)
            tmparr[--count[(*--pointer >> 16) & ((1 << 8) - 1)]] = *pointer;
    }
    {
        for (; ptr != count;)
            *--ptr = 0;
        for (; tmpArrPointer != tmpArrEnd;)
            count[(*tmpArrPointer++ >> 24) & ((1 << 8) - 1)]++;
        for (; ++ptr != countEnd;)
            *ptr += *(ptr - 1);
        for (; tmpArrPointer != tmparr;)
            begin[--count[(*--tmpArrPointer >> 24) & ((1 << 8) - 1)]] = *tmpArrPointer;
    }
    delete[] tmparr;
}

/*
Time limit:	3300 ms
Real time limit:	5 s
Memory limit:	1300M
Stack limit:	2M
Очень быстрая сортировка
Уметь сортировать быстро – полезный навык. Стандартные сортировки в языках Си и C++ достаточно быстры и универсальны. К сожалению, их универсальность имеет недостаток: сложность алоритмов этих сортировки составляет O(N log(N)).

Между тем известно, что для некоторых типов данных имеются и сортировки со сложность по времени O(N).

Вам и предстоит такую написать.

Файл, который вы должны послать в тестирующую систему, должен иметь реализацию ровно одной функции. Она должна ничего не вводить и ничего не выводить.

   
        void fast_sort(unsigned *begin, unsigned *end); 
    
Требуется, чтобы ваша функция отсортировала массив, заданный аргументами, по возрастанию.

Вы можете пользоваться временными массивами в динамической памяти, память, занятая этими массивами должна быть освобождена к моменту завершения вашей функции.

Оценка выставляется по каждому тесту отдельно в зависимости от эффективности вашего алгоритма – чем больше времени будет использовать ваша функция в данном тесте, тем меньше баллов она получит.

Ваша программа не должна содержать функции main. Пример программы, которую можно использовать при тестировании:

 
            

void fast_sort(unsigned *begin, unsigned *end) {
    // Your code for implementation
}

int main() {
    unsigned array[8] = {3,1,4,1,5,9,2,6};
    fast_sort(array, array+8);
    // Now array = {1,1,2,3,4,5,6,9}
}
            
*/