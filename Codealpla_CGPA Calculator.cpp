#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
    double cumulativePoints = 0;
    int cumulativeCredits = 0;
    int semCount = 1;

    double semGPA[20];
    int semCreditsArr[20];
    int totalSems = 0;

    cout << "=== Academic Performance Tracker ===\n";

    while (true)
    {
        cout << "\n--- Semester " << semCount << " ---\n";

        int numCourses;
        while (true)
        {
            cout << "How many courses this semester? ";
            cin >> numCourses;

            if (cin.fail() || numCourses < 1 || numCourses > 10)
            {
                cout << "Invalid input. Please enter between 1 and 10.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            else
                break;
        }

        double semPoints = 0;
        int semCredits = 0;

        for (int i = 1; i <= numCourses; i++)
        {
            cout << " Course " << i << ":\n";

            double grade;
            while (true)
            {
                cout << "   Grade (0.0-4.0): ";
                cin >> grade;

                if (cin.fail() || grade < 0.0 || grade > 4.0)
                {
                    cout << "   Invalid input. Enter grade between 0.0 and 4.0.\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else
                    break;
            }

            int credits;
            while (true)
            {
                cout << "   Credits (1-5): ";
                cin >> credits;

                if (cin.fail() || credits < 1 || credits > 5)
                {
                    cout << "   Invalid input. Enter credits between 1 and 5.\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else
                    break;
            }

            semPoints += grade * credits;
            semCredits += credits;
        }

        double currentGPA = semPoints / semCredits;

        cumulativePoints += semPoints;
        cumulativeCredits += semCredits;

        semGPA[totalSems] = currentGPA;
        semCreditsArr[totalSems] = semCredits;
        totalSems++;

        cout << "\nSemester " << semCount << " GPA: "
            << fixed << setprecision(2) << currentGPA << "\n";

        cout << "Current overall CGPA: "
            << (cumulativePoints / cumulativeCredits) << "\n";

        char cont;
        while (true)
        {
            cout << "\nAdd another semester? (y/n): ";
            cin >> cont;

            if (cont == 'y' || cont == 'Y' || cont == 'n' || cont == 'N')
                break;
            else
                cout << "Invalid choice. Enter y or n.\n";
        }

        if (cont == 'n' || cont == 'N')
            break;

        semCount++;
    }

    cout << "\n\n" << string(35, '=') << "\n";
    cout << "        FINAL ACADEMIC REPORT       \n";
    cout << string(35, '=') << "\n";
    cout << "Sem | GPA    | Credits\n";
    cout << "-----------------------------------\n";

    for (int i = 0; i < totalSems; i++)
    {
        cout << i + 1 << "   | "
            << fixed << setprecision(2) << semGPA[i]
            << "   | " << semCreditsArr[i] << "\n";
    }

    cout << "-----------------------------------\n";
    cout << "OVERALL CGPA: "
        << (cumulativePoints / cumulativeCredits) << "\n";
    cout << "TOTAL CREDITS: " << cumulativeCredits << "\n";
    cout << string(35, '=') << endl;

    return 0;
}
