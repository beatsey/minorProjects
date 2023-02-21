#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

class Minesweeper {
public:
    std::vector<std::vector<int8_t>> field;
    size_t cells_to_open;
    struct Cell {
        size_t x = 0;
        size_t y = 0;
    };

    enum class GameStatus {
        NOT_STARTED,
        IN_PROGRESS,
        VICTORY,
        DEFEAT
    } current_status;

    using RenderedField = std::vector<std::string>;

    Minesweeper(size_t width, size_t height, size_t mines_count);
    Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void NewGame(size_t width, size_t height, size_t mines_count);
    void NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void OpenCell(const Cell& cell);
    void MarkCell(const Cell& cell);

    GameStatus GetGameStatus() const;
    time_t GetGameTime() const;

    RenderedField RenderField() const;
};

/*
4 - закрытая с флажком с миной
3 - закрытая с флажком без мины
2 - закрытая мина
1 - закрытая клетка без мины
0 - открытая без мин вокруг
-1 - открытая с одной миной вокруг
...
-8 - открытая с 8ю минами вокруг
*/

// 1 соответствует закрытой клетке без мины
Minesweeper::Minesweeper(size_t width, size_t height, size_t mines_count) :
    field(height, std::vector<int8_t>(width, 1)),
    current_status(Minesweeper::GameStatus::IN_PROGRESS),
    cells_to_open(width * height - mines_count) {
    const size_t product = width * height;
    std::vector<size_t> in(product);
    for (size_t c = product, i = 0; i < c; i++) {
        in[i] = i;
    }
    
    std::vector<int> out;
    std::sample(
        in.begin(),
        in.end(),
        std::back_inserter(out),
        mines_count,
        std::mt19937{std::random_device{}()});
    
    for (auto i : out) {
        field[i / width][i % width] = 2; // 2 соответствует мине
    }
}
	
Minesweeper::Minesweeper(size_t width, size_t height,
    const std::vector<Minesweeper::Cell>& cells_with_mines) :
    field(height, std::vector<int8_t>(width, 1)),
    current_status(Minesweeper::GameStatus::IN_PROGRESS),
    cells_to_open(width * height - cells_with_mines.size()) {
        for(size_t i = 0; i < cells_with_mines.size(); ++i) {
            field[cells_with_mines[i].y][cells_with_mines[i].x] = 2; // 2 соответствует мине
        }
}

void Minesweeper::NewGame(size_t width, size_t height, size_t mines_count) {
    current_status = Minesweeper::GameStatus::IN_PROGRESS;
    field = std::vector(height, std::vector<int8_t>(width, 1));
    size_t product = width * height;
    cells_to_open = product - mines_count;
    std::vector<size_t> in(product);
    for (size_t c = product, i = 0; i < c; i++) {
        in[i] = i;
    }
    
    std::vector<int> out;
    std::sample(
        in.begin(),
        in.end(),
        std::back_inserter(out),
        mines_count,
        std::mt19937{std::random_device{}()});
    
    for (auto i : out) {
        field[i / width][i % width] = 2; // 2 соответствует мине
    }
}

void Minesweeper::NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    current_status = Minesweeper::GameStatus::IN_PROGRESS;
    field = std::vector(height, std::vector<int8_t>(width, 1));
    cells_to_open = width * height - cells_with_mines.size();
    for(size_t i = 0; i < cells_with_mines.size(); ++i) {
        field[cells_with_mines[i].y][cells_with_mines[i].x] = 2; // 2 соответствует мине
    }
}

void Minesweeper::OpenCell(const Cell& cell) {
    if (current_status != Minesweeper::GameStatus::IN_PROGRESS ||
        cell.y >= field.size() || cell.x >= field[0].size() ||
        field[cell.y][cell.x] == 3 || field[cell.y][cell.x] == 4) {
        return;
    }
    
    if (field[cell.y][cell.x] == 2) { // закрытая мина
        current_status = Minesweeper::GameStatus::DEFEAT;
    }
    else if (field[cell.y][cell.x] == 1) { // закрытая без мины
        cells_to_open -= 1;
        if (cells_to_open == 0){
            current_status = Minesweeper::GameStatus::VICTORY;
        }
        
        // Считаем количество мин вокруг
        size_t miny, maxy, minx, maxx;
        if (cell.y == 0) {
            miny = 0;
        }else{
            miny = cell.y - 1;
        }
        
        if (cell.x == 0) {
            minx = 0;
        }else{
            minx = cell.x - 1;
        }
        
        // Упадёт в случае field.size == 0
        maxy = std::min(field.size() - 1, cell.y + 1);
        maxx = std::min(field[0].size() - 1, cell.x + 1);
        
        // Считаем количество мин рядом
        field[cell.y][cell.x] = 0;
        for(size_t i = miny; i <= maxy; ++i) {
            for(size_t j = minx; j <= maxx; ++j) {
                if (field[i][j] == 2 || field[i][j] == 4){
                    field[cell.y][cell.x] -= 1;
                }
            }
        }
        
        // Если мин в текущей ячейке нет
        if(field[cell.y][cell.x] == 0){
            for(size_t i = miny; i <= maxy; ++i) {
                for(size_t j = minx; j <= maxx; ++j) {
                    if (field[i][j] == 1) { // Закрытая клетка без флажка
                        // TODO: заменить рекурсию на что-то
                        OpenCell({.x = j, .y = i});
                    }
                }
            }
        }
    }
}

void Minesweeper::MarkCell(const Cell& cell) {
    if (current_status != Minesweeper::GameStatus::IN_PROGRESS ||
        cell.y >= field.size() || cell.x >= field[0].size() ||
        field[cell.y][cell.x] <= 0) {
        return;
    }
    
    if(field[cell.y][cell.x] == 4) {
        field[cell.y][cell.x] = 2;
    }else if(field[cell.y][cell.x] == 3) {
        field[cell.y][cell.x] = 1;
    }else if(field[cell.y][cell.x] == 1) {
        field[cell.y][cell.x] = 3;
    }else if(field[cell.y][cell.x] == 2) {
        field[cell.y][cell.x] = 4;
    }
}

Minesweeper::GameStatus Minesweeper::GetGameStatus() const {
    return current_status;
}

time_t Minesweeper::GetGameTime() const {
    return 0;
}

Minesweeper::RenderedField Minesweeper::RenderField() const {
    std::vector<std::string> result(field.size());
    for(size_t i = 0;i<field.size();++i){
        for(size_t j = 0;j<field[i].size();++j){
            if (field[i][j] == 3 || field[i][j] == 4){
                result[i]+='?';
            } else if (field[i][j] == 1){
                result[i]+='-';
            } else if (field[i][j] == 2) { // закрытая мина
                if (current_status == Minesweeper::GameStatus::DEFEAT){
                    result[i]+='*';
                }else{
                    result[i]+='-';
                }
            } else if (field[i][j] == 0){
                result[i]+='.';
            } else {
                result[i]+= '0' - field[i][j];
            }
        }
    }
    return result;
}

int main() {
    Minesweeper minesweeper(8, 3, {{.x = 0, .y = 0}, {.x = 2, .y = 1}});
    // *211....
    // 12*1....
    // .111....

    {
        const Minesweeper::RenderedField expected = {
            "--------",
            "--------",
            "--------",
        };

        std::cout << (expected == minesweeper.RenderField()) << std::endl;
    }
    {
        minesweeper.OpenCell({.x = 2, .y = 0});

        const Minesweeper::RenderedField expected = {
            "--1-----",
            "--------",
            "--------"
        };

        std::cout << (expected == minesweeper.RenderField()) << std::endl;
    }
    {
        minesweeper.MarkCell({.x = 5, .y = 1});
        minesweeper.OpenCell({.x = 7, .y = 2});
        const Minesweeper::RenderedField expected = {
            "--11....",
            "---1.?..",
            "---1....",
        };

        std::cout << (expected == minesweeper.RenderField()) << std::endl;
    }
    {
        minesweeper.OpenCell({.x = 0, .y = 2});

        const Minesweeper::RenderedField expected = {
            "--11....",
            "12-1.?..",
            ".1-1....",
        };

        std::cout << (expected == minesweeper.RenderField()) << std::endl;
    }
    {
        minesweeper.MarkCell({.x = 0, .y = 0});
        minesweeper.OpenCell({.x = 1, .y = 0});
        minesweeper.OpenCell({.x = 2, .y = 2});
        minesweeper.MarkCell({.x = 5, .y = 1});
        minesweeper.OpenCell({.x = 5, .y = 1});

        const Minesweeper::RenderedField expected = {
            "?211....",
            "12-1....",
            ".111....",
        };

        std::cout << (expected == minesweeper.RenderField()) << std::endl;
        std::cout << (Minesweeper::GameStatus::VICTORY == minesweeper.GetGameStatus()) << std::endl;
    }
    {
        minesweeper.NewGame(1000, 1000, 1'000'000);
        minesweeper.OpenCell({.x = 0, .y = 0});
        std::cout << (Minesweeper::GameStatus::DEFEAT == minesweeper.GetGameStatus()) << std::endl;


        for (const auto& line : minesweeper.RenderField()) {
            std::cout << (std::all_of(line.begin(), line.end(), [](auto ch) { return ch == '*'; })) << std::endl;
        }
    }
}
