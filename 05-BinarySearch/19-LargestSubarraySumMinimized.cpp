int util(vector<int> &arr, int max_sum){
   int tmp = 0, no_subarray = 1;
   for(auto i: arr){
      if(i + tmp <= max_sum) tmp += i;
      else {
         no_subarray++;
         tmp = i;
      }
   }
   return no_subarray;
}

int largestSubarraySumMinimized(vector<int> &arr, int k){
    int n = arr.size();
    int max_ = *max_element(arr.begin(), arr.end());
    int sum = accumulate(arr.begin(), arr.end(), 0);

    int low = max_, high = sum;
    while(low <= high ){
      int mid = low + (high - low) /2;
      if(util(arr, mid) > k ) low = mid + 1;
      else high  = mid - 1;
    }
    return low;
}
