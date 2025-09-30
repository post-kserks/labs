#include <iostream>
#include "../helpers.h"
#include "../structures.h"

using namespace std;

void generateColorPalettes() {
    cout << "=== Задание 6: Генератор цветовой палитры ===" << endl;

    Color palettes[5][4];

    for (int palette = 0; palette < 5; palette++) {
        // Генерируем базовый цвет
        int baseRed = randomInRange(0, 255);
        int baseGreen = randomInRange(0, 255);
        int baseBlue = randomInRange(0, 255);

        // Первый цвет - базовый
        palettes[palette][0] = {baseRed, baseGreen, baseBlue};

        // Второй и третий цвета - оттенки базового (немного измененные)
        for (int i = 1; i <= 2; i++) {
            int variation = randomInRange(-30, 30);
            palettes[palette][i] = {
                max(0, min(255, baseRed + variation)),
                max(0, min(255, baseGreen + variation)),
                max(0, min(255, baseBlue + variation))
            };
        }

        // Четвертый цвет - контрастный (инвертированный или дополняющий)
        palettes[palette][3] = {
            255 - baseRed,
            255 - baseGreen,
            255 - baseBlue
        };
    }

    // Выводим палитры
    for (int palette = 0; palette < 5; palette++) {
        cout << "Палитра " << (palette + 1) << ":" << endl;
        for (int color = 0; color < 4; color++) {
            cout << "Цвет " << (color + 1) << ": ("
                 << palettes[palette][color].red << ", "
                 << palettes[palette][color].green << ", "
                 << palettes[palette][color].blue << ")" << endl;
        }
        cout << endl;
    }
}
