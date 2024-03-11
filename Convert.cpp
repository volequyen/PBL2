#include "Convert.h"
int Convert::StringtoInt(const string& s) {
    int sum = 0;
    for(int i = 0 ; i < s.size() ; ++i) {
        if(s[i] >= '0' && s[i] <= '9') sum = sum * 10 + int(s[i]) - 48;
    }
    return sum;
}

int Convert::Compare(string s1 , string s2) {
    s1 = s1 + '/';
    s2 = s2 + '/';
    int i = 0;
    string temp1 = "" , temp2 = "";
    int d1 , m1 , y1 , d2 , m2 , y2;
    int count = 0;
    while(i < s1.size() && i < s2.size()) {
        if(s1[i] != '/') {
            temp1 = temp1 + s1[i];
            temp2 = temp2 + s2[i];
        }
        else if(s1[i] == '/') {
            // cout << temp1 << " " << temp2 << endl;
            if(count == 0) {
                y1 = Convert::StringtoInt(temp1);
                y2 = Convert::StringtoInt(temp2);
                count++;
                temp1 = "";
                temp2 = "";
            }
            else if(count == 1) {
                m1 = Convert::StringtoInt(temp1);
                m2 = Convert::StringtoInt(temp2);
                count++;
                temp1 = "";
                temp2 = "";
            }
            else {
                d1 = Convert::StringtoInt(temp1);
                d2 = Convert::StringtoInt(temp2);
                count++;
                temp1 = "";
                temp2 = "";
            }
        }
        i++;
    }
    // cout << d1 << " " << d2 << endl;
    if(y1 > y2) return 1;
    else if(y1 < y2) return 2;
    else {
        if(m1 > m2) return 1;
        else if(m1 < m2) return 2;
        else {
            if(d1 > d2) return 1;
            else if(d1 < d2) return 2;
            else return 0;
        }   
    }
    return 0;
}
