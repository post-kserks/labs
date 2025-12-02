#include "camellia.h"
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>

// S-box для Camellia (упрощенная версия)
// В реальной реализации используются специальные S-boxes
static const uint8_t SBOX[256] = {
    112, 130, 44, 236, 179, 39, 192, 229, 228, 133, 87, 53, 234, 12, 174, 65,
    35, 239, 107, 147, 69, 25, 165, 33, 237, 14, 79, 78, 29, 101, 146, 189,
    134, 184, 175, 143, 124, 235, 31, 206, 62, 48, 220, 95, 94, 197, 11, 26,
    166, 225, 57, 202, 213, 71, 93, 61, 217, 1, 90, 214, 81, 86, 108, 77,
    139, 13, 154, 102, 251, 204, 176, 45, 116, 18, 43, 32, 240, 177, 132, 153,
    223, 76, 203, 194, 52, 126, 118, 5, 109, 183, 169, 49, 209, 23, 4, 215,
    20, 88, 58, 97, 222, 27, 17, 28, 50, 15, 156, 22, 83, 24, 242, 34,
    254, 68, 207, 178, 195, 181, 122, 145, 36, 8, 232, 168, 96, 252, 105, 80,
    170, 208, 160, 125, 161, 137, 98, 151, 84, 91, 30, 149, 224, 255, 100, 210,
    16, 196, 0, 72, 163, 247, 117, 219, 138, 3, 230, 218, 9, 63, 221, 148,
    135, 92, 131, 2, 205, 74, 144, 51, 115, 103, 246, 243, 157, 127, 191, 226,
    82, 155, 216, 38, 200, 55, 198, 59, 129, 150, 111, 75, 19, 190, 99, 46,
    233, 121, 167, 140, 159, 110, 188, 142, 41, 245, 249, 182, 47, 253, 180, 89,
    120, 152, 6, 106, 231, 70, 113, 186, 212, 37, 171, 66, 136, 162, 141, 250,
    114, 7, 185, 85, 248, 238, 172, 10, 54, 73, 42, 104, 60, 56, 241, 164,
    64, 40, 211, 123, 187, 201, 67, 193, 21, 227, 173, 244, 119, 199, 128, 158
};

// Функция перестановки (P-function) - упрощенная
static void apply_permutation(uint8_t* block) {
    uint8_t temp[BLOCK_SIZE];
    memcpy(temp, block, BLOCK_SIZE);
    
    // Простая перестановка байтов
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] = temp[(i * 7) % BLOCK_SIZE];
    }
}

// Функция подстановки через S-box
static void apply_sbox(uint8_t* block) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] = SBOX[block[i]];
    }
}

// Обратная S-box (создаем на лету)
static uint8_t inverse_sbox(uint8_t value) {
    for (int i = 0; i < 256; i++) {
        if (SBOX[i] == value) return i;
    }
    return 0;
}

// Обратная подстановка
static void apply_inverse_sbox(uint8_t* block) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] = inverse_sbox(block[i]);
    }
}

// Обратная перестановка
static void apply_inverse_permutation(uint8_t* block) {
    uint8_t temp[BLOCK_SIZE];
    memcpy(temp, block, BLOCK_SIZE);
    
    // Обратная перестановка
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[(i * 7) % BLOCK_SIZE] = temp[i];
    }
}

// Функция XOR блока с ключом
static void xor_with_key(uint8_t* block, const uint8_t* key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i];
    }
}

// Генерация раундовых ключей (упрощенно - просто циклический сдвиг)
static void generate_round_key(const CamelliaKey& master_key, uint8_t* round_key, int round) {
    for (int i = 0; i < KEY_SIZE; i++) {
        round_key[i] = master_key.key[(i + round) % KEY_SIZE];
    }
}

// Генерация случайного ключа
CamelliaKey generate_key() {
    CamelliaKey key;
    for (int i = 0; i < KEY_SIZE; i++) {
        key.key[i] = rand() % 256;
    }
    return key;
}

// Шифрование одного блока
// Упрощенная схема: несколько раундов (S-box -> P-box -> XOR с раундовым ключом)
void encrypt_block(const uint8_t* input, uint8_t* output, const CamelliaKey& key) {
    const int NUM_ROUNDS = 8; // Упрощенно используем 8 раундов
    
    // Копируем input в output
    memcpy(output, input, BLOCK_SIZE);
    
    // Начальное XOR с ключом
    xor_with_key(output, key.key);
    
    // Раунды шифрования
    for (int round = 0; round < NUM_ROUNDS; round++) {
        // Подстановка через S-box
        apply_sbox(output);
        
        // Перестановка
        apply_permutation(output);
        
        // XOR с раундовым ключом
        uint8_t round_key[KEY_SIZE];
        generate_round_key(key, round_key, round);
        xor_with_key(output, round_key);
    }
}

// Дешифрование одного блока
void decrypt_block(const uint8_t* input, uint8_t* output, const CamelliaKey& key) {
    const int NUM_ROUNDS = 8;
    
    memcpy(output, input, BLOCK_SIZE);
    
    // Раунды дешифрования (в обратном порядке)
    for (int round = NUM_ROUNDS - 1; round >= 0; round--) {
        // XOR с раундовым ключом
        uint8_t round_key[KEY_SIZE];
        generate_round_key(key, round_key, round);
        xor_with_key(output, round_key);
        
        // Обратная перестановка
        apply_inverse_permutation(output);
        
        // Обратная подстановка
        apply_inverse_sbox(output);
    }
    
    // Финальное XOR с ключом
    xor_with_key(output, key.key);
}

// Шифрование данных произвольной длины
// Используем режим ECB (Electronic Codebook) для простоты
// В реальности лучше использовать CBC, CTR или другие режимы
std::vector<uint8_t> encrypt_data(const std::vector<uint8_t>& data, const CamelliaKey& key) {
    std::vector<uint8_t> encrypted;
    
    // Добавляем 4 байта для хранения размера + дополняем до кратности BLOCK_SIZE
    int size_with_length = data.size() + 4;
    int padded_size = ((size_with_length + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE;
    std::vector<uint8_t> padded_data(padded_size, 0);
    
    // Записываем размер в начало
    uint32_t original_size = data.size();
    memcpy(padded_data.data(), &original_size, 4);
    
    // Копируем данные после размера
    memcpy(padded_data.data() + 4, data.data(), data.size());
    
    encrypted.resize(padded_size);
    
    // Шифруем блок за блоком
    for (int i = 0; i < padded_size; i += BLOCK_SIZE) {
        encrypt_block(&padded_data[i], &encrypted[i], key);
    }
    
    return encrypted;
}

// Дешифрование данных
std::vector<uint8_t> decrypt_data(const std::vector<uint8_t>& encrypted, const CamelliaKey& key) {
    if (encrypted.size() % BLOCK_SIZE != 0) {
        std::cerr << "Ошибка: размер зашифрованных данных должен быть кратен " 
                  << BLOCK_SIZE << std::endl;
        return {};
    }
    
    std::vector<uint8_t> decrypted(encrypted.size());
    
    // Дешифруем блок за блоком
    for (size_t i = 0; i < encrypted.size(); i += BLOCK_SIZE) {
        decrypt_block(&encrypted[i], &decrypted[i], key);
    }
    
    // Извлекаем реальный размер из начала
    uint32_t original_size;
    memcpy(&original_size, decrypted.data(), 4);
    
    if (original_size > decrypted.size() || original_size + 4 > decrypted.size()) {
        std::cerr << "Ошибка: некорректный размер данных" << std::endl;
        return {};
    }
    
    // Возвращаем только реальные данные (без размера)
    std::vector<uint8_t> result(original_size);
    memcpy(result.data(), decrypted.data() + 4, original_size);
    return result;
}

// Тестирование производительности
void test_camellia_performance(int data_size_mb) {
    std::cout << "\n=== Camellia: Тестирование производительности ===" << std::endl;
    std::cout << "Размер данных: " << data_size_mb << " МБ" << std::endl;
    
    // Генерация тестовых данных
    int data_size = data_size_mb * 1024 * 1024;
    std::vector<uint8_t> test_data(data_size);
    for (int i = 0; i < data_size; i++) {
        test_data[i] = rand() % 256;
    }
    
    // Генерация ключа
    CamelliaKey key = generate_key();
    std::cout << "Ключ сгенерирован" << std::endl;
    
    // Шифрование
    clock_t start = clock();
    std::vector<uint8_t> encrypted = encrypt_data(test_data, key);
    clock_t end = clock();
    
    double encrypt_time = (double)(end - start) / CLOCKS_PER_SEC;
    double encrypt_speed = data_size_mb / encrypt_time;
    
    std::cout << "Время шифрования: " << encrypt_time << " сек" << std::endl;
    std::cout << "Скорость шифрования: " << encrypt_speed << " МБ/с" << std::endl;
    
    // Дешифрование
    start = clock();
    std::vector<uint8_t> decrypted = decrypt_data(encrypted, key);
    end = clock();
    
    double decrypt_time = (double)(end - start) / CLOCKS_PER_SEC;
    double decrypt_speed = data_size_mb / decrypt_time;
    
    std::cout << "Время дешифрования: " << decrypt_time << " сек" << std::endl;
    std::cout << "Скорость дешифрования: " << decrypt_speed << " МБ/с" << std::endl;
    
    // Проверка корректности
    bool correct = (test_data == decrypted);
    if (correct) {
        std::cout << "✓ Дешифрование корректно" << std::endl;
    } else {
        std::cout << "✗ Ошибка дешифрования!" << std::endl;
    }
    
    // Проверка требования скорости
    if (encrypt_speed > 50.0) {
        std::cout << "✓ Тест пройден: скорость > 50 МБ/с" << std::endl;
    } else {
        std::cout << "✗ Тест не пройден: скорость <= 50 МБ/с" << std::endl;
    }
    
    // Вычислительная сложность
    std::cout << "\nАнализ сложности:" << std::endl;
    std::cout << "- Шифрование блока: O(R * B), где R=8 (раунды), B=16 (размер блока)" << std::endl;
    std::cout << "- Шифрование данных: O(N/B * R * B) = O(N * R)" << std::endl;
    std::cout << "  где N=" << data_size << " байт" << std::endl;
    std::cout << "- Линейная зависимость от размера данных" << std::endl;
}
