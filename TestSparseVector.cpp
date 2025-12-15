#include "SparseVector.h"
#include <gtest/gtest.h>
#include <iostream>

// Тест 1: Базовый конструктор и методы доступа
TEST(SparseVectorTest, BasicConstructorAndAccess) {
    SparseVector vec(10);
    
    EXPECT_EQ(vec.getSize(), 10);
    
    // Все элементы должны быть нулевыми
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(vec.getElem(i), 0);
    }
}

// Тест 2: Установка и получение элементов
TEST(SparseVectorTest, SetAndGetElements) {
    SparseVector vec(10);
    
    vec.setElem(3, 5);
    EXPECT_EQ(vec.getElem(3), 5);
    
    vec.setElem(7, 100);
    EXPECT_EQ(vec.getElem(7), 100);
    
    // Проверка, что другие элементы остались нулевыми
    EXPECT_EQ(vec.getElem(0), 0);
    EXPECT_EQ(vec.getElem(5), 0);
}

// Тест 3: Обнуление элементов
TEST(SparseVectorTest, ZeroElements) {
    SparseVector vec(5);
    
    vec.setElem(2, 10);
    EXPECT_EQ(vec.getElem(2), 10);
    
    // Установка в ноль должно удалить элемент
    vec.setElem(2, 0);
    EXPECT_EQ(vec.getElem(2), 0);
}

// Тест 4: Конструктор копирования
TEST(SparseVectorTest, CopyConstructor) {
    SparseVector vec1(10);
    vec1.setElem(1, 3);
    vec1.setElem(4, 7);
    vec1.setElem(8, 12);
    
    SparseVector vec2(vec1); // Копирование
    
    EXPECT_EQ(vec2.getSize(), 10);
    EXPECT_EQ(vec2.getElem(1), 3);
    EXPECT_EQ(vec2.getElem(4), 7);
    EXPECT_EQ(vec2.getElem(8), 12);
    
    // Проверка независимости копий
    vec1.setElem(4, 999);
    EXPECT_EQ(vec2.getElem(4), 7); // Копия не должна измениться
}

// Тест 5: Оператор присваивания
TEST(SparseVectorTest, AssignmentOperator) {
    SparseVector vec1(10);
    vec1.setElem(2, 8);
    vec1.setElem(5, 12);
    
    SparseVector vec2(5);
    vec2 = vec1;
    
    EXPECT_EQ(vec2.getSize(), 10);
    EXPECT_EQ(vec2.getElem(2), 8);
    EXPECT_EQ(vec2.getElem(5), 12);
    
    // Проверка самоприсваивания
    vec2 = vec2;
    EXPECT_EQ(vec2.getElem(2), 8);
}

// Тест 6: Операторы равенства и неравенства
TEST(SparseVectorTest, EqualityOperators) {
    SparseVector vec1(10);
    SparseVector vec2(10);
    SparseVector vec3(5);
    
    // Пустые векторы одного размера
    EXPECT_TRUE(vec1 == vec2);
    EXPECT_FALSE(vec1 != vec2);
    
    // С одинаковыми элементами
    vec1.setElem(3, 5);
    vec2.setElem(3, 5);
    EXPECT_TRUE(vec1 == vec2);
    
    // С разными элементами
    vec1.setElem(4, 10);
    EXPECT_TRUE(vec1 != vec2);
    
    // Разные размеры
    EXPECT_TRUE(vec1 != vec3);
}

// Тест 7: Сложение векторов
TEST(SparseVectorTest, Addition) {
    SparseVector vec1(10);
    SparseVector vec2(10);
    
    vec1.setElem(1, 3);
    vec1.setElem(3, 7);
    vec1.setElem(6, 2);
    
    vec2.setElem(1, 2);
    vec2.setElem(5, 4);
    vec2.setElem(6, -2);
    
    SparseVector sum = vec1 + vec2;
    
    EXPECT_EQ(sum.getElem(1), 5);   // 3 + 2
    EXPECT_EQ(sum.getElem(3), 7);   // 7 + 0
    EXPECT_EQ(sum.getElem(5), 4);   // 0 + 4
    EXPECT_EQ(sum.getElem(6), 0);   // 2 + (-2) = 0 (должно удалиться)
    
    // Проверка оператора +=
    SparseVector vec3 = vec1;
    vec3 += vec2;
    EXPECT_TRUE(vec3 == sum);
}

// Тест 8: Вычитание векторов
TEST(SparseVectorTest, Subtraction) {
    SparseVector vec1(10);
    SparseVector vec2(10);
    
    vec1.setElem(1, 10);
    vec1.setElem(3, 5);
    vec1.setElem(7, 8);
    
    vec2.setElem(1, 3);
    vec2.setElem(5, 2);
    vec2.setElem(7, 8);
    
    SparseVector diff = vec1 - vec2;
    
    EXPECT_EQ(diff.getElem(1), 7);   // 10 - 3
    EXPECT_EQ(diff.getElem(3), 5);   // 5 - 0
    EXPECT_EQ(diff.getElem(5), -2);  // 0 - 2
    EXPECT_EQ(diff.getElem(7), 0);   // 8 - 8 = 0 (должно удалиться)
    
    // Проверка оператора -=
    SparseVector vec3 = vec1;
    vec3 -= vec2;
    EXPECT_TRUE(vec3 == diff);
}

// Тест 9: Большие векторы
TEST(SparseVectorTest, LargeVector) {
    SparseVector vec(1000);
    
    vec.setElem(0, 1);
    vec.setElem(500, 250);
    vec.setElem(999, 1000);
    
    EXPECT_EQ(vec.getElem(0), 1);
    EXPECT_EQ(vec.getElem(500), 250);
    EXPECT_EQ(vec.getElem(999), 1000);
    EXPECT_EQ(vec.getElem(250), 0);
}

// Тест 10: Комбинированные операции
TEST(SparseVectorTest, CombinedOperations) {
    SparseVector vec1(10);
    SparseVector vec2(10);
    SparseVector vec3(10);
    
    vec1.setElem(1, 5);
    vec1.setElem(2, 10);
    
    vec2.setElem(1, 3);
    vec2.setElem(3, 7);
    
    vec3.setElem(2, 5);
    vec3.setElem(3, 2);
    
    // (vec1 + vec2) - vec3
    SparseVector result = vec1 + vec2;
    result -= vec3;
    
    EXPECT_EQ(result.getElem(1), 8);  // 5 + 3 - 0 = 8
    EXPECT_EQ(result.getElem(2), 5);  // 10 + 0 - 5 = 5
    EXPECT_EQ(result.getElem(3), 5);  // 0 + 7 - 2 = 5
}

// Тест 11: Порядок индексов
TEST(SparseVectorTest, IndexOrder) {
    SparseVector vec(10);
    
    // Добавляем элементы не по порядку
    vec.setElem(7, 70);
    vec.setElem(3, 30);
    vec.setElem(5, 50);
    vec.setElem(1, 10);
    
    // Внутренний список должен поддерживать порядок
    EXPECT_EQ(vec.getElem(1), 10);
    EXPECT_EQ(vec.getElem(3), 30);
    EXPECT_EQ(vec.getElem(5), 50);
    EXPECT_EQ(vec.getElem(7), 70);
}

// Тест 12: Push back (если этот метод используется)
TEST(SparseVectorTest, PushBack) {
    SparseVector vec(10);
    
    vec.push_back(2, 20);
    vec.push_back(5, 50);
    
    EXPECT_EQ(vec.getElem(2), 20);
    EXPECT_EQ(vec.getElem(5), 50);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
