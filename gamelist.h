#pragma once

#ifndef GAMELIST_H
#define GAMELIST_H

// ������� 12: ����������� ������������ ����������� �����
const int MaxNameLength = 256;

// ���������, �������������� �������
struct Student
{
    // ������� 7: ������������ ���������� � ������� PascalCase
    // ������� 23: �������� ���������� ������ ���� ����������� � � �������� 10 ��������
    char* Name;
    int Rating;
    int Order; // �������� ������� ��� ����������

    // ������� 10: ���� ��������� * � ������ & ������� � ����
    Student* Next;
    Student* Prev;
};

// ����� ��� ���������� ���������� ����������� �������
class GameList
{
public:
    // �����������
    GameList();

    // ���������� ��� ������������ ������
    ~GameList();

    // ����� ���������� ������� � ����� ������
    void AddStudent(const char* NewName);

    // �������� ������ ������
    Student* GetHead();

    // �������� ������ ������
    int GetSize();

private:
    Student* Head;
    int Size;
};

#endif // GAMELIST_H 
