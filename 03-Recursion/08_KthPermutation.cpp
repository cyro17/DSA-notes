/*
Brute Force:
      1. using recursion we can generate all the permutations
      2. store the perm into a ds.
      3. sort the ds

   T.C => O(N! * N)
   S.C => O(N)


Optimized approach :
   T.C => O(N^2);
   S.C => O(N)

following are the solution of optimized approach !!
 */

class Solution
{
public:
    string getPermutation(int n, int k)
    {
        int fact = 1;
        vector<int> nums;
        for (int i = 1; i < n; i++)
        {
            fact = fact * i;
            nums.push_back(i);
        }
        nums.push_back(n);

        string res = "";
        k = k - 1;
        while (true)
        {
            res = res + to_string(nums[k / fact]);
            nums.erase(nums.begin() + k / fact);

            if (nums.size() == 0)
            {
                break;
            }
            k = k % fact;
            fact = fact / nums.size();
        }
        return res;
    }
};