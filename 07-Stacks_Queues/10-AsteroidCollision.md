

> TC = O( 2N )
> SC = O( N ) 
'''
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& arr) {
        int n = arr.size();
        vector<int> res;
        stack<int> st;
        for (int i = 0; i < n; ++i)
        {
            if(arr[i] > 0) st.push(arr[i]);
            else {
                while(!st.empty() && st.top() > 0 && st.top() < abs(arr[i])) st.pop();
                if(!st.empty() && st.top() == abs(arr[i])) st.pop();
                else if(st.empty() || st.top() < 0) st.push(arr[i]);  
            }
        }
        while(!st.empty()){
            res.push_back(st.top());
            st.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
'''

'''
class Solution {
    public int[] asteroidCollision(int[] arr) {
        int n = arr.length;
        ArrayDeque<Integer> st = new ArrayDeque<>();
        for(int a : arr){
            if(a > 0) st.push(a);
            else {
                while(!st.isEmpty() && st.peek() > 0 && -a > st.peek() ) st.pop();
                if(!st.isEmpty() && st.peek() == -a) st.pop();
                else if(st.isEmpty() || st.peek() < 0) st.push(a);
            }
        }
        int res[] = new int[st.size()];
        int i = st.size() -1;
        while(!st.isEmpty()){
            res[i--] = st.pop();
        }
        return res;
    }
}
'''
