#include "algorithms.h"
#include <unordered_map>

// Хеш-функция для Point
struct PointHash {
    std::size_t operator()(const Point& p) const {
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
};

std::vector<Point> aStar(const Point& start, const Point& goal, const Map& map, int& nodesExplored) {
    nodesExplored = 0;

    std::priority_queue<Node*, std::vector<Node*>, NodeCompare> openSet;
    std::unordered_map<Point, Node*, PointHash> allNodes;

    Node* startNode = new Node(start, 0, heuristic(start, goal));
    openSet.push(startNode);
    allNodes[start] = startNode;

    while (!openSet.empty()) {
        Node* current = openSet.top();
        openSet.pop();
        nodesExplored++;

        if (current->pos == goal) {
            std::vector<Point> path = reconstructPath(current);

            // Очистка памяти
            for (auto& pair : allNodes) {
                delete pair.second;
            }

            return path;
        }

        for (const Point& neighborPos : getNeighbors(current->pos, map)) {
            double newG = current->g + current->pos.distance(neighborPos);

            if (allNodes.find(neighborPos) == allNodes.end() || newG < allNodes[neighborPos]->g) {
                Node* neighborNode = new Node(neighborPos, newG, heuristic(neighborPos, goal), current);
                openSet.push(neighborNode);
                allNodes[neighborPos] = neighborNode;
            }
        }
    }

    // Очистка памяти в случае неудачи
    for (auto& pair : allNodes) {
        delete pair.second;
    }

    return std::vector<Point>(); // Путь не найден
}

std::vector<Point> aStarPS(const Point& start, const Point& goal, const Map& map, int& nodesExplored) {
    // Сначала выполняем обычный A*
    std::vector<Point> path = aStar(start, goal, map, nodesExplored);

    if (path.empty()) return path;

    // Пост-сглаживание: удаляем промежуточные точки, если есть прямая видимость
    std::vector<Point> smoothedPath;
    smoothedPath.push_back(path[0]);

    for (size_t i = 2; i < path.size(); i++) {
        if (!map.isLineOfSight(smoothedPath.back(), path[i])) {
            smoothedPath.push_back(path[i-1]);
        }
    }
    smoothedPath.push_back(path.back());

    return smoothedPath;
}

std::vector<Point> thetaStar(const Point& start, const Point& goal, const Map& map, int& nodesExplored) {
    nodesExplored = 0;

    std::priority_queue<Node*, std::vector<Node*>, NodeCompare> openSet;
    std::unordered_map<Point, Node*, PointHash> allNodes;

    Node* startNode = new Node(start, 0, heuristic(start, goal));
    openSet.push(startNode);
    allNodes[start] = startNode;

    while (!openSet.empty()) {
        Node* current = openSet.top();
        openSet.pop();
        nodesExplored++;

        if (current->pos == goal) {
            std::vector<Point> path = reconstructPath(current);

            for (auto& pair : allNodes) {
                delete pair.second;
            }

            return path;
        }

        for (const Point& neighborPos : getNeighbors(current->pos, map)) {
            // Theta*: проверяем, можно ли улучшить путь через родителя текущего узла
            double newG;
            if (current->parent && map.isLineOfSight(current->parent->pos, neighborPos)) {
                // Прямая видимость от родителя к соседу
                newG = current->parent->g + current->parent->pos.distance(neighborPos);
            } else {
                // Стандартный способ через текущий узел
                newG = current->g + current->pos.distance(neighborPos);
            }

            if (allNodes.find(neighborPos) == allNodes.end() || newG < allNodes[neighborPos]->g) {
                Node* neighborNode;

                if (current->parent && map.isLineOfSight(current->parent->pos, neighborPos)) {
                    // Прямая видимость - соединяем с родителем
                    neighborNode = new Node(neighborPos, newG, heuristic(neighborPos, goal), current->parent);
                } else {
                    // Стандартное соединение
                    neighborNode = new Node(neighborPos, newG, heuristic(neighborPos, goal), current);
                }

                openSet.push(neighborNode);
                allNodes[neighborPos] = neighborNode;
            }
        }
    }

    for (auto& pair : allNodes) {
        delete pair.second;
    }

    return std::vector<Point>();
}
