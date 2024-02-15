#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int maxArea(vector<int> &h)
    {
        int l = 0;
        int r = h.size() - 1;

        int max_area = 0;
        while (l < r)
        {
            int s = min(h[l], h[r]);
            max_area = max(max_area, s * (r - l));

            if (h[l] < h[r])
                l++;
            else
                r--;
        }
        return max_area;
    }
};

int main()
{
    int n;
    cin >> n;
    vector<int> v;
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        v.push_back(temp);
    }

    int s = Solution().maxArea(v);
    cout << s;

    return 0;
}