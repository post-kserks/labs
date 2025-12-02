#ifndef CAMELLIA_H
#define CAMELLIA_H

#include <cstdint>
#include <vector>

// Упрощенная реализация Camellia (128-bit ключ, 128-bit блок)
// Для учебных целей - не для production использования!

const int BLOCK_SIZE = 16;  // 128 бит = 16 байт
const int KEY_SIZE = 16;    // 128 бит = 16 байт

// Структура для хранения ключа
struct CamelliaKey {
    uint8_t key[KEY_SIZE];
};

// Генерация случайного ключа
CamelliaKey generate_key();

// Шифрование одного блока (128 бит)
void encrypt_block(const uint8_t* input, uint8_t* output, const CamelliaKey& key);

// Дешифрование одного блока (128 бит)
void decrypt_block(const uint8_t* input, uint8_t* output, const CamelliaKey& key);

// Шифрование данных произвольной длины (режим ECB для простоты)
std::vector<uint8_t> encrypt_data(const std::vector<uint8_t>& data, const CamelliaKey& key);

// Дешифрование данных
std::vector<uint8_t> decrypt_data(const std::vector<uint8_t>& encrypted, const CamelliaKey& key);

// Тестирование производительности шифрования
void test_camellia_performance(int data_size_mb);

#endif
