/* Brute force:
      using loop multiply x  n times => TC = O(N)

 */

/* Optimal approach: Using Binary Exponentiation
      TC = log(N)
*/

class Solution {
public:
    double myPow(double x, int n) {
        if(n == 0) return 1.0;
        if(n == 1) return x;
        if(n < 0) x = 1 / x;
        n = abs(n);
        
        double pow = 1;
        while(n !=0){
            if(n & 1 != 0){
                pow = pow * x;
            }
            x *= x;
            n >>= 1;
        }
        return pow;
        
    }
};
