/*
# Нормализация UNIX пути

В этой задаче нужно написать функцию, которая приводит к нормализованному виду строку, представляющую собой [путь к файлу или директории](https://www.geeksforgeeks.org/absolute-relative-pathnames-unix/) в UNIX-подобной операционной системе.
На вход подается текущая директория `current_working_dir` (абсолютный путь, т.е. начинающийся с `/`) и путь `path`, который может быть как абсолютным, так и относительным. Надо вернуть нормализованный абсолютный путь, которому соответсвует `path`.
Нормализация пути заключается в приведении к абсолютному пути и избавлении от следующих элементов:
- `/` в конце пути
- `.` - текущая директория
- `..` - родительская директория
- `//` - равносильно `/`

Примеры:
"/" == NormalizePath("/", ".")
"/home/user2" == NormalizePath("/home/user1", "../user2")
"/" == NormalizePath("/", "..")
"/tmp" == NormalizePath("/home", "../../tmp")
"/a" == NormalizePath("/", "../../a/")
"/b" == NormalizePath("/", ".././/././/./../b/././././././")
*/

#include <string>
#include <string_view>
#include <iostream>

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string mypath;
    if (path[0] == '/') {
        mypath = path;
    } else {
        mypath = std::string(current_working_dir) + '/' + std::string(path) + '/';
    }

    // i - указатель на текущий элемент
    // len - указатель на вставку
    int len = 1;
    for (size_t i = 1; i < mypath.size(); i++) {
        if (mypath[i] == '/' && mypath[i - 1] == '/') {
            continue;
        }

        // Обработка ../
        if (mypath[i] == '.' && mypath[i - 1] == '.') {
            len--;
            while (len > 1 && mypath[--len - 1] != '/');
            i++;
            continue;
        }
        if (mypath[i] == '/' && mypath[i - 1] == '.') {
            len--;
            continue;
        }

        mypath[len] = mypath[i];
        len++;
    }
    if ((len > 1) && (mypath[len - 1] == '/')) {
        len--;
    }
    mypath.resize(len);
    return mypath;
}

int main() {
    std::cout << NormalizePath("/../a/../abcd/././kjhaskjdhakjsd/////jahsdjk/./","////../abc") << std::endl;
    std::cout << NormalizePath("/", "////") << std::endl;
    std::cout << NormalizePath("/home/user1", "../user2////") << std::endl;
    std::cout << NormalizePath("/", "..") << std::endl;
    std::cout << NormalizePath("/home", "../../tmp") << std::endl;
    std::cout << NormalizePath("/", "../../a/") << std::endl;
    std::cout << NormalizePath("/", ".././/././/./../b/././././././") << std::endl;
}