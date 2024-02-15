#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Solution
{
public:
    int removeDuplicate(vector<int> &v)
    {
        int n = v.size();
        int i = 1;
        for (int j = 1; j < n; j++)
        {
            if (v[j] != v[j - 1])
            {
                v[i] = v[j];
                i++;
            }
        }
        return i;
    }
};

int main()
{
    vector<int> v = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    // cout << v.size() << endl;
    cout << Solution().removeDuplicate(v);

    return 0;
}