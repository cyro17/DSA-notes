#include <iostream>
using namespace std;

int main()
{
    int n = 2;
    cout << ((n & 1) ? "odd" : "even");
    return 0;
}