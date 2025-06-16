#pragma once

#ifndef GAMELIST_H
#define GAMELIST_H

// Правило 12: Запрещается использовать «магические» числа
const int MaxNameLength = 256;

// Структура, представляющая ученика
struct Student
{
    // Правило 7: Наименования переменных в нотации PascalCase
    // Правило 23: Название переменных должно быть примитивным и в пределах 10 символов
    char* Name;
    int Rating;
    int Order; // Исходный порядок для сортировки

    // Правило 10: Знак указателя * и ссылки & ставить у типа
    Student* Next;
    Student* Prev;
};

// Класс для управления двусвязным циклическим списком
class GameList
{
public:
    // Конструктор
    GameList();

    // Деструктор для освобождения памяти
    ~GameList();

    // Метод добавления ученика в конец списка
    void AddStudent(const char* NewName);

    // Получить голову списка
    Student* GetHead();

    // Получить размер списка
    int GetSize();

private:
    Student* Head;
    int Size;
};

#endif // GAMELIST_H 
