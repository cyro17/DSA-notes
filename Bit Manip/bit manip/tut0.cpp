#include <iostream>
using namespace std;

int main()
{
    int n = 2;
    cout << ((1 & n) ? "odd" : "even");

    return 0;
}