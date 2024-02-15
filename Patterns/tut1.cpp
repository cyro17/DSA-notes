#include <iostream>
using namespace std;

/* print the pattern1

_ _ _ *
_ _ * *
_ * * *
* * * *


*/

void pattern1(int n)
{
    int i = 0;
    while (i < n)
    {
        int sp = n - 1 - i;
        while (sp)
        {
            cout << " "
                 << " ";
            sp--;
        }
        int j = 0;
        while (j <= i)
        {
            cout << "*"
                 << " ";
            j++;
        }
        cout << endl;

        i++;
    }
}

void pattern2(int n)
{
    int i = 0;
    while (i < n)
    {
        int st = n - i;
        while (st > 0)
        {
            cout << "*"
                 << " ";
            st--;
        }

        int col = 1;
        while (col <= i)
        {
            cout << "*";
            col++;
        }
        cout << endl;
        i++;
    }
}

int main()
{
    // int n;
    // cin >> n;
    // // pattern1(n);

    // pattern2(n);
}