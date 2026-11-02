
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// 1. Рекурсивне створення матриці
void Create(int** a, int rowCount, int colCount,
    int Low, int High, int i = 0, int j = 0)
{
    if (i >= rowCount)
        return;

    a[i][j] = Low + rand() % (High - Low + 1);

    if (j + 1 < colCount)
        Create(a, rowCount, colCount, Low, High, i, j + 1);
    else
        Create(a, rowCount, colCount, Low, High, i + 1, 0);
}

// 2. Рекурсивне виведення матриці
void Print(int** a, int rowCount, int colCount,
    int i = 0, int j = 0)
{
    if (i >= rowCount)
    {
        cout << endl;
        return;
    }

    cout << setw(4) << a[i][j];

    if (j + 1 < colCount)
        Print(a, rowCount, colCount, i, j + 1);
    else
    {
        cout << endl;
        Print(a, rowCount, colCount, i + 1, 0);
    }
}

// 3. Рекурсивна заміна двох стовпців місцями
void Change(int** a, int col1, int col2,
    int rowCount, int i = 0)
{
    if (i >= rowCount)
        return;

    int temp = a[i][col1];
    a[i][col1] = a[i][col2];
    a[i][col2] = temp;

    Change(a, col1, col2, rowCount, i + 1);
}

// 4. Рекурсивне сортування стовпців
void Sort(int** a, int rowCount, int colCount,
    int j = 0, int pass = 0)
{
    if (pass >= colCount - 1)
        return;

    if (j >= colCount - pass - 1)
    {
        Sort(a, rowCount, colCount, 0, pass + 1);
        return;
    }

    bool needChange =
        (a[0][j] < a[0][j + 1]) ||
        (a[0][j] == a[0][j + 1] &&
            a[1][j] < a[1][j + 1]) ||
        (a[0][j] == a[0][j + 1] &&
            a[1][j] == a[1][j + 1] &&
            a[2][j] > a[2][j + 1]);

    if (needChange)
        Change(a, j, j + 1, rowCount);

    Sort(a, rowCount, colCount, j + 1, pass);
}

// 5. Рекурсивне обчислення суми та кількості
// і заміна потрібних елементів нулями
void Calc(int** a, int rowCount, int colCount,
    int& S, int& k, int i = 0, int j = 0)
{
    if (i >= rowCount)
        return;

    if (a[i][j] >= 0 && a[i][j] % 3 == 0)
    {
        S += a[i][j];
        k++;
        a[i][j] = 0;
    }

    if (j + 1 < colCount)
        Calc(a, rowCount, colCount, S, k, i, j + 1);
    else
        Calc(a, rowCount, colCount, S, k, i + 1, 0);
}

// 6. Головна функція
int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    const int Low = -21;
    const int High = 24;

    const int rowCount = 9;
    const int colCount = 6;

    // Створення динамічної матриці
    int** P = new int* [rowCount];

    for (int i = 0; i < rowCount; i++)
        P[i] = new int[colCount];

    // Створення початкової матриці
    Create(P, rowCount, colCount, Low, High);

    cout << "Original matrix P:" << endl;
    Print(P, rowCount, colCount);

    // Сортування стовпців
    Sort(P, rowCount, colCount);

    cout << "Sorted matrix P:" << endl;
    Print(P, rowCount, colCount);

    // Обчислення суми та кількості
    int S = 0;
    int k = 0;

    Calc(P, rowCount, colCount, S, k);

    cout << "Sum S = " << S << endl;
    cout << "Count k = " << k << endl;

    // Виведення зміненої матриці
    cout << "Modified matrix P:" << endl;
    Print(P, rowCount, colCount);

    // Звільнення пам'яті
    for (int i = 0; i < rowCount; i++)
        delete[] P[i];

    delete[] P;

    return 0;
}
