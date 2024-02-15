#include <iostream>  // std::cout
#include <algorithm> // std::lower_bound, std::upper_bound, std::sort
#include <vector>    // std::vector

int main()
{
    int myints[] = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> v(myints, myints + 8); // 10 20 30 30 20 10 10 20

    std::sort(v.begin(), v.end()); // 10 10 10 20 20 20 30 30

    std::vector<int>::iterator low, up;
    // low = std::lower_bound(v.begin(), v.end(), 1); //          ^
    up = std::upper_bound(v.begin(), v.end(), 8); //                   ^

    // std::cout << "lower_bound  " << *low << '\n';
    std::cout << "upper_bound " << *up << '\n';

    return 0;
}