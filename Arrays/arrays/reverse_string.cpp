    #include<iostream>
    using namespace std;
    

    bool isValid(char ch){
        if( (ch >='a' && ch<='z') || 
            (ch >='A' && ch<='Z') || 
            (ch >='0' && ch<='9')){
            return ch;
        }
        return 0;
    }
    
    // converts into lower case character
    char toLowercase(char ch){
        if((ch>='a' && ch<='z') || (ch>='0' && ch<='9')){
            return ch;
        }
        else{
            char temp = ch - 'A' + 'a';
            return temp;
        }
    }
    
    bool checkPalindrome(string a){
        int start = 0;
        int end = a.length() - 1;
        
        while(start <=end){
            if( toLowercase(a[start] != toLowercase(a[end])) ){
                return 0;
            }
            else{
                start ++;
                end--;
            }
            
        }
        return 1;
        
    }
    
    bool isPalindrome(string s) {
        string temp = "";
        for(int j =0; j < s.length(); j++){
            if(isValid(s[j])){
                temp.push_back(s[j]);
            }
        }
        
        for(int j = 0; j< temp.length(); j++){
            temp[j] = toLowercase(temp[j]);
        }
        return checkPalindrome(temp);
        
    }


    int main(){
        string in = "A man, a plan, a canal: Panama";
        cout<<isPalindrome(in);
    return 0;
    }