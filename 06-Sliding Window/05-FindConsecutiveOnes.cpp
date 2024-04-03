
/*
Binary Array given => given maximum no of consecutive ones if k no of flips are allowed

[1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0] ,  k = 2

*/

/*
Brute Force :
  1. generate all the subset and count number of zeros.
  2. if zeros is less than equal to K => update max length
  3.  if all flips are used up => break out of the neseted loop.

  TC = O(N^2)
  SC = O(1)

*/

class Solution
{
public:
  int brute(vector<int> &arr, int k)
  {
    int n = arr.size();
    int max_len = 0;
    for (int i = 0; i < n; i++)
    {
      int zeros = 0;
      for (int j = 0; j < n; j++)
      {
        if (arr[j] == 0)
          zeros++;
        if (zeros <= k)
        {
          max_len = max(max_len, j - i + 1);
        }
        else
          break;
      }
    }
  }

  /*
    Optimized_1 :
      1. take 2 pointers and loop over using lright pointer
      2. cont no of zeros, once it gets more than k
      3. shrink the left window until one zero is found and update l to next of it
        such that no of zeros gets equal to K.

      TC = O(N* 2)
      SC = O(1)
   */
  int optimize_1(vector<int> &arr, int k)
  {
    int n = arr.size();
    int max_len = 0, left = 0, right = 0, int zeros = 0;
    while (r < n)
    {
      if (arr[r] == 0)
        zeros++;

      while (zeros > k)
      {
        if (arr[l] == 0)
        {
          zeros--;
          l++;
        }
      }

      if (zeros <= k)
        max_len = max(max_len, r - l + 1);

      r++;
    }
    return max_len;
  }

  /*
      optimize_ 2:
      1. here we will try to optimize the nested while loop which is used to shrink the window
          and will make sure that window is reduced just by 1

      TC = O(N)
      SC = O(1)
   */

  int optimize_2(vector<int> &arr, int k)
  {
    int n = arr.size();
    int max_len = 0, left = 0, right = 0, int zeros = 0;
    while (r < n)
    {
      if (arr[r] == 0)
        zeros++;

      //   here we will try to use if instead of while loop and will increase l by 1 instead of
      if (zeros > k)
      {
        if (arr[l] == 0)
          zeros--;
        l++;
      }

      if (zeros <= k)
        max_len = max(max_len, r - l + 1);

      r++;
    }
    return max_len;
  }

  int optimized(vector<int> &arr, int k)
  {
    int n = arr.size();
    int i = 0;
    for (int j = 0; j < n; j++)
    {
      if (arr[j] == 0)
        k--;
      if (k < 0 && arr[i++] == 0)
        k++;
    }
    return j - i;
  }
};