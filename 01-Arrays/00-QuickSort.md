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
> Java code

```
class Solution {
    private Random rand = new Random();
    private void swap(int[] arr, int i, int j){
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    private int partition(int[] arr, int low, int high){
        int pivotIndex = low + rand.nextInt(high - low + 1);
        swap(arr, low, pivotIndex);

        int pivot = arr[low]; 
        int i = low, j = high;

        while(i  < j){
            while(arr[i] <= pivot && i <= high - 1) i++;
            while(arr[j] > pivot && j >= low + 1) j--;
            if(i < j) swap(arr, i, j);
        }

        swap(arr, low, j);
        return j;
    }

    private void qs(int[] arr, int low, int high){
        if(low < high){
            int pindex = partition(arr, low, high);
            qs(arr, low , pindex -1);
            qs(arr, pindex + 1, high);
        }
    }
    public int[] sortArray(int[] nums) {
        int n = nums.length;
        qs(nums, 0, n - 1);
        return nums;
    }
}
```
