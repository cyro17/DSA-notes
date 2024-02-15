#include <iostream>
using namespace std;

class Solution
{
public:
    int reverse(int x)
    {
        bool isneg = false;

        if (x < 0)
        {
            isneg = true;
            x = -x;
        }

        this->rev(x);
        
    }

    long rev(int n)
    {
        long rev = 0;
        while (n > 0)
        {
            rev = rev * 10 + rev % 10;
            n /= 10;
        }
        return rev;
    }
};

int main()
{

    return 0;
}