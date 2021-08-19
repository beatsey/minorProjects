#include <iostream>
#include <algorithm>
#include <vector>

class Time {
    uint64_t year;
    uint64_t month;
    uint64_t day;
    uint64_t hour;
    uint64_t minute;
    uint64_t second;

    bool isLeap;
public:

    Time() : year(0), month(0), day(0), hour(0), minute(0), second(0), isLeap(IsLeapYear(year)) {};

    Time(uint64_t year, uint64_t month, uint64_t day, uint64_t hour, uint64_t minute, uint64_t second) :
        year(year), month(month), day(day), hour(hour), minute(minute), second(second), isLeap(IsLeapYear(year)) {};

    // Проверка на високосный год
    bool static IsLeapYear(uint64_t year) {
        return (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);
    }

    uint64_t GetYear() const {
        return year;
    }

    uint64_t GetMonth() const {
        return month;
    }

    uint64_t GetDay() const {
        return day;
    }

    uint64_t GetHour() const {
        return hour;
    }

    uint64_t GetMinute() const {
        return minute;
    }

    uint64_t GetSecond() const {
        return second;
    }

    void SetUnixtime(uint64_t);
    uint64_t GetUnixTime() const;

    void SetFiletime(uint64_t);
    uint64_t GetFileTime();

    uint64_t static GetDaysInMonth(uint64_t, bool);
    uint64_t DaysInCurrentMonth() const;

    int64_t operator-(const Time&);
    Time operator+(const Time&);

    friend std::istream& operator>>(std::istream&, Time&);
};

void Time::SetUnixtime(uint64_t unixtime) {
    second = unixtime % 60;
    unixtime /= 60; // количество минут с 1970 года

    minute = unixtime % 60;
    unixtime /= 60; // количество часов с 1970 года

    hour = unixtime % 24;
    unixtime /= 24; // количество суток с 1970 года

    // Определяем год, месяц, число по пройденным суткам

    year = 1970;
    isLeap = IsLeapYear(year);
    while (true) {
        const uint64_t days_in_current_year = isLeap ? 366 : 365;

        if (unixtime >= days_in_current_year) {
            year++;
            isLeap = IsLeapYear(year);
            unixtime -= days_in_current_year;
        }
        else {
            break;
        }
    }

    month = 1;
    while (true) {
        const uint64_t days_in_current_month = DaysInCurrentMonth();

        if (unixtime >= days_in_current_month) {
            month++;
            unixtime -= days_in_current_month;
        }
        else {
            break;
        }
    }
    day = unixtime + 1;

}

uint64_t Time::GetUnixTime() const {
    if (year < 1970)
        return 0;

    uint64_t daysCounter = 0;

    for (int j = 1970; j < year; ++j) {
        if (IsLeapYear(j)) daysCounter += 366;
        else daysCounter += 365;
    }

    for (int j = 1; j < month; ++j) {
        daysCounter += GetDaysInMonth(j, isLeap);
    }
    daysCounter += day - 1;

    return ((daysCounter * 24 + hour) * 60 + minute) * 60 + second;
}

void Time::SetFiletime(uint64_t filetime) {
    filetime /= 10000000; // Отбрасываем хвост с сотнями наносекунд до секунд

    second = filetime % 60;
    filetime /= 60; // количество минут с 1601 года

    minute = filetime % 60;
    filetime /= 60; // количество часов с 1601 года

    hour = filetime % 24;
    filetime /= 24; // количество суток с 1601 года

    // Определяем год, месяц, число по пройденным суткам

    year = 1601;
    isLeap = IsLeapYear(year);
    while (true) {
        const uint64_t days_in_current_year = isLeap ? 366 : 365;

        if (filetime >= days_in_current_year) {
            year++;
            isLeap = IsLeapYear(year);
            filetime -= days_in_current_year;
        }
        else break;
    }

    month = 1;
    while (true) {
        const uint64_t days_in_current_month = DaysInCurrentMonth();

        if (filetime >= days_in_current_month) {
            month++;
            filetime -= days_in_current_month;
        }
        else break;
    }
    day = filetime + 1;
}

uint64_t Time::GetFileTime() {
    if (year < 1601)
        return 0;

    uint64_t daysCounter = 0;

    for (int j = 1601; j < year; ++j) {
        if (IsLeapYear(j)) daysCounter += 366;
        else daysCounter += 365;
    }

    for (int j = 1; j < month; ++j) {
        daysCounter += GetDaysInMonth(j, isLeap);
    }

    daysCounter += day - 1;

    return (((daysCounter * 24 + hour) * 60 + minute) * 60 + second) * 10000000;
}

uint64_t Time::GetDaysInMonth(uint64_t month, bool isLeapYear) {
    if (month < 8) {
        if (month == 2)
            return isLeapYear ? 29 : 28;

        return (month % 2 == 0) ? 30 : 31;
    }

    return (month % 2 == 0) ? 31 : 30;
}

uint64_t Time::DaysInCurrentMonth() const {
    if (month < 8) {
        if (month == 2)
            return isLeap ? 29 : 28;

        return (month % 2 == 0) ? 30 : 31;
    }

    return (month % 2 == 0) ? 31 : 30;
}

int64_t Time::operator-(const Time& t) {
    return GetUnixTime() - t.GetUnixTime();
}

Time Time::operator+(const Time& t) {
    Time newTime;
    newTime.SetUnixtime(GetUnixTime() + t.GetUnixTime());
    return newTime;
}

std::istream& operator>>(std::istream& in, Time& t) {
    in >> t.year >> t.month >> t.day >> t.hour >> t.minute >> t.second;
    t.isLeap = t.IsLeapYear(t.year);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Time& t) {
    return out << "Date: " << t.GetDay() << "." << t.GetMonth() << "." << t.GetYear()
        << "\nTime: " << t.GetHour() << ":" << t.GetMinute() << ":" << t.GetSecond();
}

// Задание 3
struct Element {
    int row, col;
    double value;
    Element(int row, int col, double value) :row(row), col(col), value(value) {}

    Element() : row(0), col(0), value(0) {};

    bool operator<(const Element& b) const {
        return row < b.row || row == b.row && col < b.col;
    };
};

// Перегрузка оператора ввода Element
std::istream& operator>>(std::istream& in, Element& el) {
    return in >> el.row >> el.col >> el.value;
}
std::ostream& operator<<(std::ostream& out, const Element& el) {
    return out << '(' << el.row << ',' << el.col << ',' << el.value << ')';
}

class SparseMatrix {
    // Динамический массив Element'ов
    std::vector<Element> data;
    bool sorted;
    void sortAndRemoveDuplicates();
public:
    SparseMatrix():sorted(false) {}
    SparseMatrix(const SparseMatrix& mat) {
        std::copy(mat.data.begin(), mat.data.end(), data.begin());
        sorted = mat.sorted;
    }

    // Устанавливаем значение в ячейке
    void setElement(Element& el) {
        data.push_back(el);
        sorted = false;
    }

    void setElement(int row, int col, double value) {
        Element el(row, col, value);
        setElement(el);
    }

    // Получаем значение в ячейке
    double getElement(int row, int col) {
        sortAndRemoveDuplicates();

        for (long long i = data.size() - 1; i >= 0; i--) {
            if (data[i].row == row && data[i].col == col)
                return data[i].value;
        }
        return 0;
    }

    SparseMatrix& operator*=(double);
    SparseMatrix& operator+=(SparseMatrix&);
    SparseMatrix& operator-=(SparseMatrix&);
    SparseMatrix operator+(SparseMatrix&);
    SparseMatrix operator-(SparseMatrix&);
    SparseMatrix& operator=(const SparseMatrix&);

    friend std::ostream& operator<<(std::ostream&, SparseMatrix&);
};

// Метод для сортировки и удаления дублирующих элементов (с одинаковыми индексами)
void SparseMatrix::sortAndRemoveDuplicates() {
    if (sorted) return;
    sorted = true;

    if (data.size() <= 1) return;

    // Отсортировали массив по возрастанию строк.
    // При совпадающих строках сортировка по возрастанию столбцов
    sort(data.begin(), data.end());

    // Удаляем дубликаты (если при вводе данных несколько раз указывалась тройка (i,j,val1) (i,j,val2) ...

    size_t indexForWrite = 0;  // Индекс для записи
    size_t indexStart = 0;  // Индекс первого элемента с расматриваемой строкой и столбцом
    size_t currentIndex = 1; // Текущий правый индекс

    for (; currentIndex < data.size(); currentIndex++) {
        if (data[indexStart].row == data[currentIndex].row &&
            data[indexStart].col == data[currentIndex].col) {
            // Индексы соседних элементов равны. Идём дальше
            continue;
        }

        // Если значение записываемого элемента равно нулю, то он игнорируется
        if (data[currentIndex - 1].value != 0) {
            data[indexForWrite++] = data[currentIndex - 1];
        }

        indexStart = currentIndex;
    }
    data[indexForWrite++] = data[currentIndex - 1];

    // Изменяем размер динамического массива
    data.resize(indexForWrite);

}

// Оператор умножения матрицы на вещественное число
SparseMatrix& SparseMatrix::operator*=(double multiplier) {
    for (size_t i = 0; i < data.size(); i++) {
        data[i].value *= multiplier;
    }
    return *this;
}

// Оператор +=
SparseMatrix& SparseMatrix::operator+=(SparseMatrix& mat) {
    // Подготавливаем обе матрицы
    sortAndRemoveDuplicates();
    mat.sortAndRemoveDuplicates();

    const size_t mat1size = data.size();
    size_t j = 0;
    for (size_t i = 0; i < mat1size && j < mat.data.size();) {
        // Если позиция элемента в матрице одна и та же, то складываем
        if (data[i].row == mat.data[j].row && data[i].col == mat.data[j].col) {
            data[i].value += mat.data[j].value;
            i++;
            j++;
            continue;
        }

        // Индекс в первом массиве меньше текущего индекса во втором
        if (data[i] < mat.data[j]) {
            i++;
            continue;
        }
        // Индекс в первом массиве больше текущего индекса во втором
        // У нас точно в первой матрицы нет элемента с индексом (mat.data[j].row, mat.data[j].col)
        setElement(mat.data[j]);
        j++;
    }

    // Если в первом массиве закончились элементы, но во втором ещё присутствуют,
    // то мы добавляем в первую матрицу соответствующие элементы из второй
    for (; j < mat.data.size(); j++) {
        setElement(mat.data[j]);
    }

    // Отмечаем, что матрица должна быть отсортирована снова
    sorted = false;

    return *this;
}

// Оператор -=
SparseMatrix& SparseMatrix::operator-=(SparseMatrix& mat) {
    // Подготавливаем обе матрицы
    sortAndRemoveDuplicates();
    mat.sortAndRemoveDuplicates();

    const size_t mat1size = data.size();
    size_t j = 0;
    for (size_t i = 0; i < mat1size && j < mat.data.size();) {
        // Если позиция элемента в матрице одна и та же, то складываем
        if (data[i].row == mat.data[j].row && data[i].col == mat.data[j].col) {
            data[i].value -= mat.data[j].value;
            i++;
            j++;
            continue;
        }

        // Индекс в первом массиве меньше текущего индекса во втором
        if (data[i] < mat.data[j]) {
            i++;
            continue;
        }
        // Индекс в первом массиве больше текущего индекса во втором
        // У нас точно в первой матрицы нет элемента с индексом (mat.data[j].row, mat.data[j].col)
        Element el = mat.data[j];
        el.value = -el.value;
        setElement(el);
        j++;
    }

    // Если в первом массиве закончились элементы, но во втором ещё присутствуют,
    // то мы добавляем в первую матрицу соответствующие элементы из второй со знаком минус
    for (; j < mat.data.size(); j++) {
        Element el = mat.data[j];
        el.value = -el.value;
        setElement(el);
    }

    // Отмечаем, что матрица должна быть отсортирована снова
    sorted = false;

    return *this;
}

// Оператор +
SparseMatrix SparseMatrix::operator+(SparseMatrix& mat) {
    // Подготавливаем обе матрицы
    sortAndRemoveDuplicates();
    mat.sortAndRemoveDuplicates();

    SparseMatrix matResult;

    size_t j = 0;
    for (size_t i = 0; i < data.size() && j < mat.data.size();) {
        // Если позиция элемента в матрице одна и та же, то складываем
        if (data[i].row == mat.data[j].row && data[i].col == mat.data[j].col) {
            matResult.setElement(data[i].row, data[i].col, data[i].value + mat.data[j].value);
            i++;
            j++;
            continue;
        }

        // Индекс в первом массиве меньше текущего индекса во втором
        if (data[i] < mat.data[j]) {
            i++;
            continue;
        }

        matResult.setElement(mat.data[j]);
        j++;
    }

    // Если в первом массиве закончились элементы, но во втором ещё присутствуют,
    // то мы добавляем в первую матрицу соответствующие элементы из второй
    for (; j < mat.data.size(); j++) {
        matResult.setElement(mat.data[j]);
    }

    return matResult;
}

// Оператор -
SparseMatrix SparseMatrix::operator-(SparseMatrix& mat) {
    // Подготавливаем обе матрицы
    sortAndRemoveDuplicates();
    mat.sortAndRemoveDuplicates();

    SparseMatrix matResult;

    size_t j = 0;
    for (size_t i = 0; i < data.size() && j < mat.data.size();) {
        // Если позиция элемента в матрице одна и та же, то складываем
        if (data[i].row == mat.data[j].row && data[i].col == mat.data[j].col) {
            matResult.setElement(data[i].row, data[i].col, data[i].value - mat.data[j].value);
            i++;
            j++;
            continue;
        }

        // Индекс в первом массиве меньше текущего индекса во втором
        if (data[i] < mat.data[j]) {
            i++;
            continue;
        }

        Element el = mat.data[j];
        el.value = -el.value;
        matResult.setElement(el);
        j++;
    }

    // Если в первом массиве закончились элементы, но во втором ещё присутствуют,
    // то мы добавляем в первую матрицу соответствующие элементы из второй
    for (; j < mat.data.size(); j++) {
        Element el = mat.data[j];
        el.value = -el.value;
        matResult.setElement(el);
    }

    return matResult;
}

SparseMatrix& SparseMatrix::operator=(const SparseMatrix& mat) {
    sorted = mat.sorted;
    std::copy(mat.data.begin(), mat.data.end(), data.begin());
    return *this;
}

// Перегрузка оператора вывода матрицы
std::ostream& operator<<(std::ostream& out, SparseMatrix& mat) {
    mat.sortAndRemoveDuplicates();
    if (mat.data.size() == 0)
        return out;

    for (int i = 0; i < mat.data.size() - 1; i++)
        out << mat.data[i] << '\n';

    return out << mat.data[mat.data.size() - 1];
}

class EasterYear {
    int indict;     // Индикт 1-15
    int sunCircle;  // Круг солнцу 1-28
    int moonCircle; // Круг луне 1-19

    int year;

public:
    EasterYear(int, int, int);
    EasterYear(int year) :year(year) {
        indict = year % 15;
        sunCircle = year % 28;
        moonCircle = year % 19;
    }

    EasterYear() : year(1), indict(1), sunCircle(1), moonCircle(1) {};

    // Преобразование от года сотворения мира к Григорианскому календарю
    int getYearFromTheBirthOfChrist() const {
        int christYear = year - 5508;
        if (christYear <= 0)
            christYear--;

        return christYear;
    }

    // От Григрианского календаря к солнечному календарю
    void setYearFromTheBirthOfChrist(int christYear) {
        if (christYear <= 0)
            throw "Ошибка! Укажите положительный год от Рождества Христова.";

        year = christYear + 5508;
        indict = year % 15;
        sunCircle = year % 28;
        moonCircle = year % 19;
    }

    friend std::ostream& operator<<(std::ostream&, const EasterYear&);
};

// Задание 2 на солнечный календарь
EasterYear::EasterYear(int indict, int sunCircle, int moonCircle) :indict(indict), sunCircle(sunCircle), moonCircle(moonCircle) {
    if (indict <= 0 || indict > 15)
        throw "Ошибка! Индикт должен принимать значения в диапазоне 1-15.";
    if (sunCircle <= 0 || sunCircle > 28)
        throw "Ошибка! Круг солнцу должен принимать значения в диапазоне 1-28.";
    if (moonCircle <= 0 || moonCircle > 19)
        throw "Ошибка! Круг луне должен принимать значения в диапазоне 1-19.";

    year = 1; // Год в отсчёте от Сотворения мира (5508 до н.э.)

    while (indict != 1 || sunCircle != 1 || moonCircle != 1) {
        if (--indict == 0) indict = 15;
        if (--sunCircle == 0) sunCircle = 28;
        if (--moonCircle == 0) moonCircle = 19;
        year++;
    }
}

std::ostream& operator<<(std::ostream& out, const EasterYear& easterYear) {
    int christYear = easterYear.getYearFromTheBirthOfChrist();
    if (christYear < 0)
        out << -christYear << " до н.э. (";
    else
        out << christYear << " н.э. (";

    return out << easterYear.indict << '-' << easterYear.sunCircle << '-' << easterYear.moonCircle << ") год от Адама: " << easterYear.year;
}

std::istream& operator>>(std::istream& in, EasterYear& easterYear) {
    int year;
    in >> year;
    easterYear = EasterYear(year);
    return in;
}

int main() {
    setlocale(LC_ALL, "Russian"); // Для поддержки кириллицы

    std::cout << "Выберите опцию:\n"
        << "1 - перевод даты в unix time\n"
        << "2 - перевод unix time в дату\n"
        << "3 - перевод даты в file time\n"
        << "4 - перевод file time в дату\n"
        << "5 - сложение и вычитание времени\n"
        << "6 - ввод разряженной матрицы(формат ввода -> индекс коэффициент)\n"
        << "7 - сложение и вычитание двух матриц\n"
        << "8 - умножение матрицы на число\n"
        << "9 - ввод и вывод года по солнечному календарю\n";

    uint64_t option;
    std::cin >> option;
    switch (option) {
        case 1: // date to unix
        {
            Time t;
            std::cin >> t;
            std::cout << t << "\nUnix_time: " << t.GetUnixTime() << '\n';
            break;
        }
        case 2: // unix time to date
        {
            Time t;
            uint64_t input_unix_t;
            std::cin >> input_unix_t;
            t.SetUnixtime(input_unix_t);

            std::cout << t << '\n';
            break;
        }
        case 3: // date to file time
        {
            Time t;
            std::cin >> t;
            std::cout << t << "\nFile_time: " << t.GetFileTime() << '\n';

            break;
        }
        case 4: // file time to date
        {
            Time t;
            uint64_t input_file_t;
            std::cin >> input_file_t;
            t.SetFiletime(input_file_t);

            std::cout << t << '\n';

            break;
        }
        case 5:
        {
            Time t1,t2;
            std::cout << "Введите год, месяц, число, час, минуту, секунду:\n";
            std::cin >> t1;
            std::cout << t1 << "\nUnix_time: " << t1.GetUnixTime()
                << "\n\nВведите год, месяц, число, час, минуту, секунду:\n";
            std::cin >> t2;

            std::cout << t2 << "\nUnix_time: " << t2.GetUnixTime() << "\n\n";

            Time t3 = t1 + t2;
            std::cout << "Сумма введённых дат и времени:\n"
                << t3 << "\nUnix_time: " << t3.GetUnixTime() << "\n\n";

            t3.SetUnixtime(t1 - t2);
            std::cout << "Разность введённых дат и времени:\n"
                << t3 << "\nUnix_time: " << t3.GetUnixTime() << "\n\n";

            break;
        }
        case 6:
        {
            std::cout << "Введите строку, столбец и значение элемента матрицы:\n";

            SparseMatrix mat;
            int row, col, answer;
            double val;
            do
            {
                std::cin >> row >> col >> val;

                if (row < 0 || col < 0)
                    std::cout << "Индексы строки и столбца должны быть неотрицательны.\n";
                else {
                    mat.setElement(row, col, val);
                }
                std::cout << "Продолжить ввод данных (1 - да, 0 - нет): ";
                std::cin >> answer;
            } while (answer != 0);

            std::cout << "\nВведите строку и столбец для вывода значений матрицы:\n";
            do
            {
                std::cin >> row >> col;
                if (row < 0 || col < 0)
                    std::cout << "Индексы строки и столбца должны быть неотрицательны.\n";
                else {
                    std::cout << mat.getElement(row, col) << '\n';
                }

                std::cout << "Продолжить вывод данных (1 - да, 0 - нет): ";
                std::cin >> answer;
            } while (answer != 0);

            std::cout << "\nПоэлементный вывод матрицы:\n" << mat << '\n';

            break;
        }
        case 7:
        {
            std::cout << "Введите строку, столбец и значение элемента матрицы A:\n";

            SparseMatrix matA, matB;
            int row, col, answer;
            double val;
            // Ввод матрицы A
            do
            {
                std::cin >> row >> col >> val;

                if (row < 0 || col < 0)
                    std::cout << "Индексы строки и столбца должны быть неотрицательны.\n";
                else {
                    matA.setElement(row, col, val);
                }
                std::cout << "Продолжить ввод данных (1 - да, 0 - нет): ";
                std::cin >> answer;
            } while (answer != 0);

            // Ввод матрицы B
            std::cout << "\nВведите строку, столбец и значение элемента матрицы B:\n";
            do
            {
                std::cin >> row >> col >> val;

                if (row < 0 || col < 0)
                    std::cout << "Индексы строки и столбца должны быть неотрицательны.\n";
                else {
                    matB.setElement(row, col, val);
                }
                std::cout << "Продолжить ввод данных (1 - да, 0 - нет): ";
                std::cin >> answer;
            } while (answer != 0);

            // Сложение и вычитание матриц A и B
            std::cout << "\nМатрица A:\n" << matA << "\n\nМатрица B:\n" << matB << '\n';
            do
            {
                std::cout << "\nВыберите опцию:\n1 - прибавить к A матрицу B\n2 - вычесть из A матрицу B\n";

                std::cin >> answer;
                if (answer == 1) {
                    matA += matB; // Оператор SparseMatrix +=
                    //matA = matA + matB; // Оператор SparseMatrix + SparseMatrix
                    std::cout << "\nРезультат сложения. Матрица A:\n" << matA;
                }
                else if (answer == 2) {
                    matA -= matB;
                    //matA = matA - matB;
                    std::cout << "\nРезультат вычитания. Матрица A:\n" << matA;
                }
                
                std::cout << "\n\nПродолжить ввод данных (1 - да, 0 - нет): ";
                std::cin >> answer;
            } while (answer != 0);

            break;
        }
        case 8: {
            std::cout << "Введите строку, столбец и значение элемента матрицы A:\n";

            SparseMatrix matA;
            int row, col, answer;
            double val;
            // Ввод матрицы A
            do
            {
                std::cin >> row >> col >> val;

                if (row < 0 || col < 0)
                    std::cout << "Индексы строки и столбца должны быть неотрицательны.\n";
                else {
                    matA.setElement(row, col, val);
                }
                std::cout << "Продолжить ввод данных (1 - да, 0 - нет): ";
                std::cin >> answer;
            } while (answer != 0);

            std::cout << "\nВведите коэффициент для умножения матрицы на него:\n";
            std::cin >> val;
            matA *= val;
            std::cout << "Результат операции умножения матрицы на число:\n" << matA;

            break;
        }
        case 9:
        {
            EasterYear year;

            std::cout << "Введите год в отсчете от Адама:\n";
            std::cin >> year;
            std::cout << year << "\n\n";

            int christYear;
            std::cout << "Введите год в отсчете от Рождества Христова:\n";
            std::cin >> christYear;
            year.setYearFromTheBirthOfChrist(christYear);
            std::cout << year << "\n\n";

            int indict, sunCircle, moonCircle;
            std::cout << "Введите индикт, круг солнцу, круг луне:\n";
            std::cin >> indict >> sunCircle >> moonCircle;
            std::cout << EasterYear(indict, sunCircle, moonCircle) << "\n\n";

            break;
        }
}

    return 0;
}
