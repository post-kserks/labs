#include "common.h"

// Определяем глобальную переменную
long long orient_tests = 0;

// orient: ориентированный детерминант (a->b->c)
// >0   левый поворот (ccw)
// <0   правый поворот (cw)
// ==0  коллинеарно
long long orient(const Point &a, const Point &b, const Point &c) {
    ++orient_tests; // считаем каждую проверку основной операцией
    return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
}
