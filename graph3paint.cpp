#include <iostream> 
#include <vector> 
 
bool check(size_t cur, char color, std::string& colors, std::vector<std::vector<size_t>>& graph, std::vector<bool>& checked, std::string& new_colors) { 
    checked[cur] = true; 
    if (color == colors[cur]) 
        return false; 
    char temp = new_colors[cur]; 
    new_colors[cur] = color; 
     
    bool is_check = true; 
    for (const auto& neig : graph[cur]) { 
        if (checked[neig]) { 
            if (new_colors[neig] == color) is_check = false; 
            continue; 
        } 
         
        char new_color = 'R'; 
        if (colors[neig] != 'B' && color != 'B') { 
            new_color = 'B'; 
        } 
        else if (colors[neig] == color || colors[neig] == 'R' && color == 'B' || 
            colors[neig] == 'B' && color == 'R') { 
            new_color = 'G'; 
        } 
         
        if (colors[neig] != color){ 
            bool check_result = check(neig, new_color, colors, graph, checked, new_colors); 
            if (!check_result) 
                is_check = false; 
        } 
    } 
    if (!is_check) new_colors[cur] = temp; 
    return is_check; 
} 
 
bool main_check(size_t cur, char color, std::string& colors, std::vector<std::vector<size_t>>& graph, std::string& new_colors) { 
    std::vector<bool> checked(new_colors.size(), 0); 
    return check(cur, color, colors, graph, checked, new_colors); 
} 
 
int main() { 
    size_t n, m, start, end; 
    std::cin >> n >> m; 
    std::string colors; 
    std::cin >> colors; 
    std::vector<std::vector<size_t>> graph(n, std::vector<size_t>()); 
    for (; m > 0; --m) { 
        std::cin >> start >> end; 
        graph[end - 1].push_back(start - 1); 
        graph[start - 1].push_back(end - 1); 
    } 
 
    std::string new_colors(n, ' '); 
    for (size_t i = 0; i < n; ++i) { 
        (new_colors[i] != ' ' 
        || main_check(i, 'R', colors, graph, new_colors) 
        || main_check(i, 'G', colors, graph, new_colors) 
        || main_check(i, 'B', colors, graph, new_colors)); 
    } 
     
    if (new_colors.find(' ') != std::string::npos) std::cout << "Impossible"; 
    else std::cout << new_colors; 
     
    return 0; 
}