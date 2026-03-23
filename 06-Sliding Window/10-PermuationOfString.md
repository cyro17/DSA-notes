Approach: 
  1. Generate all the permutation of string 1
  2. Check if substring of s2 has a permuation of string 1.

Time complexity : O(N! * N) + O(N^2)

```


class Solution {
    private void swap(StringBuilder s, int i, int j){
        char temp = s.charAt(i);
        s.setCharAt(i, s.charAt(j));
        s.setCharAt(j, temp);
    }

    private void recur(int index, StringBuilder s, List<String> res){

        if(index == s.length()){
        res.add(s.toString());
        return;
        }

        for(int i = index; i < s.length(); i++){
        this.swap(s, index, i);
        this.recur(index + 1, s, res);
        this.swap(s, index, i);
        }
    } 
    public List<String> generatePermutation(String s){
        int n = s.length();
        List<String> res = new ArrayList<>();
        StringBuilder sb = new StringBuilder(s);

        this.recur(0, sb, res );

        Collections.sort(res);
        return res;

  }

    public boolean checkInclusion(String s1, String s2) {
        List<String> list = this.generatePermutation(s1);

        for(int i = 0; i < s2.length(); i++){
            String sub;
            for(int j = i; j < s2.length(); j++){
                sub = s2.substring(i, j+1);

                if(list.contains(sub))return  true;

            }
        }
        return false;
    }
}

```
