/*
using sliding window: TC = O(2*K)
 */

class Solution {
    public int maxScore(int[] arr, int k) {
        int n = arr.length;
        int max = 0,  lsum = 0, rsum = 0; 
        for(int i = 0; i < k; i++){
            lsum += arr[i];
        }

        max = lsum;
        int r = n-1, l = k-1;
        while (l>=0){

            lsum -= arr[l];
            rsum += arr[r];
        
            max = Math.max(max, lsum + rsum);

            r--;
            l--;
        }
        return max;

    }
}

