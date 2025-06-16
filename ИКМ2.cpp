#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>
#include "gamelist.h"
using namespace std;

// Числа вынесены в отдельные переменные, чтобы была возможность изменить диапазон случайных чисел
const int MinRandom = -10;
const int MaxRandom = 10;

void SortStudents(Student** Array, int Size) // Функция сортировки участников
{
    for (int i = 0; i < Size - 1; i++)
    {
        for (int j = 0; j < Size - i - 1; j++)
        {
            bool ShouldSwap = Array[j]->Rating < Array[j + 1]->Rating; // Сортировка по убыванию рейтинга

            // Если рейтинги равны, сортировка по исходному порядку
            bool RatingsEqual = Array[j]->Rating == Array[j + 1]->Rating;
            bool OrderIsGreater = Array[j]->Order > Array[j + 1]->Order;
            if (RatingsEqual == true && OrderIsGreater == true)
            {
                ShouldSwap = true;
            }

            if (ShouldSwap == true)
            {
                Student* Temp = Array[j];
                Array[j] = Array[j + 1];
                Array[j + 1] = Temp;
            }
        }
    }
}

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    cout << "     Игра 'Доброе дело'     " << endl;
    cout << "Ученики становятся в круг. Случайное число определяет, кто сделает 'доброе дело'." << endl;
    cout << "Положительное число - отсчет по часовой, отрицательное - против часовой." << endl;
    cout << "Рейтинг ученика увеличивается. Играем заданное число раундов." << endl;
    cout << "В конце выводится список по невозрастанию рейтинга." << endl;
    cout << "------------------------------------------" << endl;

    GameList StudentsList;
    ifstream File("students.txt");

    if (File.is_open() == false)
    {
        cout << "Ошибка: Не удалось открыть файл students.txt" << endl;
        return 1;
    }

    char Buffer[MaxNameLength];
    while (File.getline(Buffer, MaxNameLength))
    {
        bool IsEmpty = Buffer[0] == '\0';
        if (IsEmpty == false)
        {
            StudentsList.AddStudent(Buffer);
        }
    }
    File.close();

    int ListSize = StudentsList.GetSize();
    if (ListSize == 0)
    {
        cout << "Ошибка: Файл students.txt пуст или не содержит имен." << endl;
        return 1;
    }

    cout << "Список учеников успешно загружен. Всего учеников: " << ListSize << endl;


    int Rounds;
    cout << "Введите количество раундов игры: ";

    while (true)
    {
        if (cin >> Rounds)
        {
            int nextChar = cin.get(); // Читаем следующий символ, если он является концом строки и
            // Если введенное число неотрицательное, то считается, что были введены корректные данные
            if ((nextChar == '\n') && Rounds > 0)
            {
                break; // Выходим из цикла, если ввод корректен
            }
        }

        // Если ввод был некорректен, то выводим сообщение о ошибке и предлагаем ввести новое число
        cout << "Некорректный ввод. Пожалуйста, введите целое положительное число: ";
        cin.clear(); // Сбрасываем флаги ошибок, чтобы спокойно ввести еще раз
        char c;
        while (cin.get(c) && c != '\n');
    }

    cout << "\n    Начинаем игру!    " << endl;

    srand(time(0));
    Student* Current = StudentsList.GetHead(); // Игра начинается с человека, находящегося на первой позиции в списке

    for (int i = 0; i < Rounds; i++)
    {
        int Step = 0;
        while (Step == 0) // Чтобы избежать ситуации, при которой игра не будет продвигаться, 0 как результат не учитывается 
        {
            Step = MinRandom + rand() % (MaxRandom - MinRandom + 1);
        }

        cout << "\nРаунд " << i + 1 << ". Выпало число: " << Step << endl;

        if (Step > 0) // Продвижение по часовой стрелке
        {
            for (int j = 0; j < Step; j++)
            {
                Current = Current->Next;
            }
        }
        else // Продвижение против часовой стрелки
        {
            int PositiveStep = -Step;
            for (int j = 0; j < PositiveStep; j++)
            {
                Current = Current->Prev;
            }
        }

        Current->Rating = Current->Rating + 1; // Повышение рейтинга

        cout << "Доброе дело делает: " << Current->Name << ". ";
        cout << "Новый рейтинг: " << Current->Rating << "." << endl;

        // Переход на следующего по кругу участника
        if (Step > 0) // По часовой стрелке
        {
            Current = Current->Next;
        }
        else // Против часовой
        {
            Current = Current->Prev;
        }
    }

    cout << "\n--- Игра окончена! ---" << endl;
    cout << "Итоговый рейтинг учеников (по убыванию рейтинга, если рейтинг совпадает, то по порядку добавления):" << endl;

    Student** StudentsArray = new Student * [ListSize];
    Student* StartNode = StudentsList.GetHead();
    Current = StartNode;
    for (int i = 0; i < ListSize; i++)
    {
        StudentsArray[i] = Current;
        Current = Current->Next;
    }

    SortStudents(StudentsArray, ListSize);

    for (int i = 0; i < ListSize; i++)
    {
        cout << i + 1 << ". " << StudentsArray[i]->Name << ": " << StudentsArray[i]->Rating << endl;
    }

    delete[] StudentsArray;

    return 0;
}
