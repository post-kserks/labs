#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <cmath>

// Структура для представления точки в 2D пространстве
struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    // Расстояние между точками
    double distance(const Point& other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// Узел для алгоритма поиска
struct Node {
    Point pos;
    double g, h, f;
    Node* parent;

    Node(Point p, double g = 0, double h = 0, Node* parent = nullptr)
        : pos(p), g(g), h(h), f(g + h), parent(parent) {}
};

// Представление карты с препятствиями
class Map {
public:
    // Конструктор по умолчанию
    Map() : width(0), height(0) {}

    Map(int width, int height) : width(width), height(height) {
        grid.resize(height, std::vector<bool>(width, false));
    }

    // Добавить препятствие
    void addObstacle(int x, int y) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            grid[y][x] = true;
        }
    }

    // Проверить, является ли ячейка препятствием
    bool isObstacle(int x, int y) const {
        if (x < 0 || x >= width || y < 0 || y >= height) return true;
        return grid[y][x];
    }

    // Проверить, свободен ли путь между двумя точками (для Theta*)
    bool isLineOfSight(const Point& from, const Point& to) const;

    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int width, height;
    std::vector<std::vector<bool>> grid; // true - препятствие
};

#endif
