class Solution {
    public int characterReplacement(String s, int k) {
        int n = s.length();
        int max_len = 0, max_freq = 0, l = 0, r  = 0;
        int[] freq = new int[26];

        while(r < n){
            int index = s.charAt(r) - 'A';
            freq[index]++;
            max_freq = Math.max(max_freq, freq[index]);

            while((r - l + 1 )- max_freq > k){
                freq[s.charAt(l) - 'A']--;
                l++;
            } 

            max_len = Math.max(max_len, r - l + 1);
            r++;
        }
        return max_len;
        
    }
}
