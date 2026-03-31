> Quick Sort 
TC = O( N log N)
SC = O (1)
```
class Solution {
private:
    int partition(vector<int> &arr, int low, int high){
        int pivot = arr[low];
        int i = low, j = high;

        while ( i < j){
            while(arr[i] <= pivot && i <= high - 1) 
                i++;
            while(arr[j] > pivot && j >= low + 1) 
                j--;
            
            if( i < j) 
                swap(arr[i], arr[j]);
        }

        swap(arr[low], arr[j]);
        return j;
    }

    void qs(vector<int> &arr, int low, int high){
        if(low < high){
            int pIndex = partition(arr, low, high);
            qs(arr, low, pIndex -1);
            qs(arr, pIndex + 1, high);
        }
    }
public:

    vector<int> sortArray(vector<int>& arr) {
        qs(arr, 0, arr.size() - 1);
        return arr;

    }
};

```
