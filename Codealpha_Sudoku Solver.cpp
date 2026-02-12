#include <iostream>
#include <cstdlib>
using namespace std;

const int N = 9;
int grid[N][N] = { 0 };

// clear screen
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// print grid
void printGrid()
{
    cout << endl;
    for (int i = 0; i < N; i++)
    {
        if (i % 3 == 0 && i != 0)
            cout << "---------------------\n";

        for (int j = 0; j < N; j++)
        {
            if (j % 3 == 0 && j != 0)
                cout << "| ";

            if (grid[i][j] == 0)
                cout << "- ";
            else
                cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// check safe
bool isSafe(int row, int col, int num)
{
    for (int x = 0; x < N; x++)
    {
        if (grid[row][x] == num) return false;
        if (grid[x][col] == num) return false;
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[startRow + i][startCol + j] == num)
                return false;

    return true;
}

// find empty cell
bool findEmpty(int& row, int& col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == 0)
                return true;
    return false;
}

// solver
bool solveSudoku()
{
    int row, col;
    if (!findEmpty(row, col))
        return true;

    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(row, col, num))
        {
            grid[row][col] = num;

            if (solveSudoku())
                return true;

            grid[row][col] = 0;
        }
    }
    return false;
}

int main()
{
    clearScreen();
    cout << "Empty Sudoku Grid (- = empty)\n";
    printGrid();

    cout << "\nEnter numbers cell by cell (0 for empty)\n\n";

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int num;
            while (true)
            {
                cin >> num;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input. Enter number 0 to 9: ";
                    continue;
                }

                if (num < 0 || num > 9)
                {
                    cout << "Invalid input. Enter 0 to 9: ";
                    continue;
                }

                if (num != 0 && !isSafe(i, j, num))
                {
                    cout << "Number violates Sudoku rules. Enter again: ";
                    continue;
                }

                grid[i][j] = num;

                clearScreen();
                cout << "Sudoku Grid\n";
                printGrid();
                break;
            }
        }
    }

    cout << "\nOriginal Sudoku\n";
    printGrid();

    if (solveSudoku())
    {
        cout << "\nSolved Sudoku\n";
        printGrid();
    }
    else
    {
        cout << "\nNo solution exists for this Sudoku\n";
    }

    return 0;
}
