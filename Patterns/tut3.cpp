#include <iostream>
using namespace std;

int main()
{
    int n = 2;
    if (n & 1)
        cout << "odd"
             << " ";
    else
        cout << "even"
             << " ";

    return 0;
}