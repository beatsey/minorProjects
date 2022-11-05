#include <iostream>

const char numbers[10][6][6] = {
    {
        "..##.",
        ".#..#",
        ".#..#",
        ".#..#",
        ".#..#",
        "..##.",
    },
    {
        "....#",
        "...##",
        "..#.#",
        "....#",
        "....#",
        "....#",
    },
    {
        "..##.",
        ".#..#",
        "....#",
        "...#.",
        "..#..",
        ".####",
    },
    {
        ".####",
        "....#",
        "...#.",
        "....#",
        "....#",
        ".###.",
    },
    {
        ".#..#",
        ".#..#",
        ".#..#",
        ".####",
        "....#",
        "....#",
    },
    {
        ".####",
        ".#...",
        ".###.",
        "....#",
        ".#..#",
        "..##.",
    },
    {
        "..###",
        ".#...",
        ".###.",
        ".#..#",
        ".#..#",
        "..##.",
    },
    {
        ".####",
        "....#",
        "...#.",
        "..#..",
        "..#..",
        "..#..",
    },
    {
        "..##.",
        ".#..#",
        "..##.",
        ".#..#",
        ".#..#",
        "..##.",
    },
    {
        "..##.",
        ".#..#",
        ".#..#",
        "..###",
        "....#",
        ".###.",
    }
};

// ¬озвращаем -2 - лишние пиксели; -1, если есть несколько совпадений; индекс номера, если единственное совпадение
int findNum(char input[6][6], int upperlimit = 10) {
    int result = -2;
    for (int i = 0; i < upperlimit; i++) {
        bool goodnum = true;
        for (int r = 0; r < 6; r++) {
            for (int c = 0; c < 5; c++) {
                if (numbers[i][r][c] == '.' && input[r][c] == '#') {
                    goodnum = false;
                    break;
                }
            }
            if (!goodnum)
                break;
        }
        if (goodnum) {
            if (result >= 0)
                return -1;
            result = i;
        }
    }
    return result;
}

// -2 - ERROR (пиксель или нет совпадений)
// -1 - AMBIGUITY (двойственное чтение с учЄтом формата
// 1 - ”спех
int getTime(char input[4][6][6], int res[4]) {
    res[0] = findNum(input[0], 3); // –ассматриваем только 0,1,2
    if (res[0] < 0)
        return res[0];

    if (res[0] == 2)
        res[1] = findNum(input[1], 4); // –ассматриваем только 0,1,2,3
    else
        res[1] = findNum(input[1]);

    if (res[1] < 0)
        return res[1];

    if ((res[2] = findNum(input[2], 6)) < 0)
        return res[2];

    if ((res[3] = findNum(input[3])) < 0)
        return res[3];

    return 1;
}

int main() {
    char input[4][6][6];

    for (int r = 0; r < 6; r++) {
        char str[22];
        std::cin.getline(str, 22);
        for (int c = 0; c < 20; c++) {
            input[c / 5][r][c % 5] = str[c];
        }
    }

    int res[4];
    int code = getTime(input, res);
    if (code == -1)
        std::cout << "AMBIGUITY" << std::endl;
    else if (code == -2)
        std::cout << "ERROR" << std::endl;
    else
        std::cout << res[0] << res[1] << ':' << res[2] << res[3] << std::endl;
}