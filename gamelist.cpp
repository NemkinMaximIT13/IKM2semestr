#include "gamelist.h"
#include "gamelist.h"

// Конструктор
GameList::GameList()
{
    Head = nullptr;
    Size = 0;
}

// Деструктор для освобождения памяти
GameList::~GameList()
{
    if (Head == nullptr)
    {
        return;
    }

    Student* Current = Head;
    Student* StartNode = Head;
    do
    {
        Student* ToDelete = Current;
        Current = Current->Next;
        delete[] ToDelete->Name;
        delete ToDelete;
    } while (Current != StartNode);
}

void GameList::AddStudent(const char* NewName) // Добавление участника в конец списка
{
    Student* NewStudent = new Student;
    NewStudent->Name = new char[MaxNameLength];

    // Копируем имя
    int i = 0;
    while (NewName[i] != '\0' && i < MaxNameLength - 1)
    {
        NewStudent->Name[i] = NewName[i];
        i = i + 1;
    }
    NewStudent->Name[i] = '\0';

    NewStudent->Rating = 0;
    NewStudent->Order = Size;

    if (Head == nullptr)
    {
        Head = NewStudent;
        Head->Next = Head;
        Head->Prev = Head;
    }
    else
    {
        Student* Tail = Head->Prev;
        Tail->Next = NewStudent;
        NewStudent->Prev = Tail;
        NewStudent->Next = Head;
        Head->Prev = NewStudent;
    }
    Size = Size + 1;
}

Student* GameList::GetHead() // Получить первый элемент(голову) списка
{
    return Head;
}

int GameList::GetSize() // Получить размер списка(количество участников)
{
    return Size;
}