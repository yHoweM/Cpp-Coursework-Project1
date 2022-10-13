#include<iostream>
#include<string>
#include<stdlib.h>
#include<cstring>
#include <climits>
using namespace std;

int a_array[100],b_array[100],c_array[105];

bool is_number(string str){
    int count_frac=0;
    int count_e=0;
    int count_nega = 0;
    for(int i = 0; i < str.length(); i++)
        {   
            int temp = (int) str[i];
            int temp_later = 0;
            int temp_previous = 0;
//---------------------adjacent values-----------------------
            if(i<str.length()-1){
                temp_later = (int)str[i+1];
            }
            if(i>0){
                temp_previous = (int) str[i-1];
            }
//----------------------different conditions----------------------
            if ((i==0)&&(temp==45)){//negative num
                count_nega=1;
                continue;}
            if ((i!=0)&&(temp==45)&&(temp_previous!=101)){
                count_nega = 2;
                return false;
            }
            if (temp==46){//only one fraction point
                    count_frac=count_frac+1;
                    if (count_frac>1){
                        return false;
                    }
                    continue;
                    }
            if (temp==101){//only one exponation
                    if ((temp_later==45)||(temp_later<58&&temp_later>47)){
                    count_e=count_e+1;
                    if (count_e>1){
                        return false;
                    }
                    continue;
                    }
                    else return false;
                }
            if (i!=0&&temp==45){
                if(temp_previous!=101){return false;}
                else continue;
            }
            if (temp>57 | temp<48){
                    return false;
                }
        }
    return true;
}
//having checked the inputs are valid
bool fraction_point_detect(string a){
    for (int i=0;i<a.length();i++){
        if (a[i]==46){return true;}
    }
    return false;
}
int e_detect(string a){
    for (int i=0;i<a.length();i++){
        if (a[i]==101){
            return i;}
    }
    return 0;
}
//multiply type
double multipy_double(double a, double b){
    return a*b;
}
long long multipy_longlong(long long a, long long b){
    return a * b;
}
//result overflow
bool longlong_result_overflow(long long a, long long b) { // the result may overflow
    if (a > 0 && b > 0) {
        return (LLONG_MAX/a<b);
    } 
    else if (a < 0 && b < 0) {
        return (LLONG_MAX/a>b);
    } 
    else if (a * b == LLONG_MIN) {
        return false;
    } 
    else if (a == 0 || b == 0) { // avoiding 0 denom
        return false;
    } 
    else {
        return a < 0 ? longlong_result_overflow(-a, b) : longlong_result_overflow(a, -b);
    }
}
//input overflow
bool longlong_input_overflow(string str){
// range:-9223372036854775808 - 9223372036854775807 //19 max 
    bool is_nega =false;
    long long pos_18 = 223372036854775807;
    long long neg_18 = 223372036854775808;
    string str_used;
    if (str[0]==45){
        is_nega = true;
        str_used = str.substr(1,str.length());
    }
    else{
        str_used = str;
    }
    if (str_used.length()>=20){
        //max indication of long long:
        return true;
    }
    else if (str_used.length()<=18){
        //smaller than 19 max
        return false;
    }
    else {//exact 19 
        if(str_used[0]<57){
            return false;
        }
        else{
            string a = (str_used.substr(1,str_used.length()));
            long long number = atoll(a.c_str());
            if (!is_nega){
                 if (number>pos_18){return true;}
             }
            else {
                 if (number>neg_18){return true;}
            }
        }
    }
    return false; 
}
int main(int argc, char **argv){
    if (argc>3){
        cout<<"There are more than 2 numbers, please check your input."<<endl;
        return 0;
    }
    if (argc<3){
        cout<<"There number of input is not enough, please check your input."<<endl;
        return 0;
    }
    else {
    //check whether it is a "number"
    string first = argv[1];
    string second = argv[2];
    
    if ((is_number(first)&&is_number(second))){
        cout<<"This is a valid group number, now the multipy is conducted."<<endl;
        // integer
        if((!fraction_point_detect(first))&&(!fraction_point_detect(second))){
            long long answer = 0;
            long long a = (atoll(argv[1]));
            long long b = (atoll(argv[2]));
            answer = multipy_longlong(a,b);
            if (longlong_input_overflow(first)||longlong_input_overflow(second)){
                cout<<"Warning, the input overflows."<<endl;
            }
            if (longlong_result_overflow(a,b)){
                cout<<"Also, the result overflows!";
                cout<<"Wait, conducting fixing operation......"<<endl;
                cout<<first<<" * "<<second<< " = "<< endl;
                // from highest to lowest  reverse
                for(int i=0; i<first.length(); i++) {
                    a_array[i]=first[first.length()-i-1]-'0'; 
                }
               
                for(int i=0; i<second.length(); i++) {
                    b_array[i]=second[second.length()-i-1]-'0';
                }
                for(int i=0; i<first.length(); i++) {
                    int carry=0;
                    for(int j=0; j<second.length(); j++) {
                        c_array[i+j]+=a_array[i]*b_array[j]+carry;
                        carry=c_array[i+j]/10;
                        c_array[i+j]%=10;
                    }
                    c_array[i+second.length()]+=carry;
                }
                	int index=first.length()+second.length();
                    while(c_array[index]==0 && index>0) index--;
                
                    for(int i=index; i>=0; i--)
                        cout<<c_array[i];
                cout << endl;
                return 0;
            }
            cout<<"Integer operation:"<< a << "*" << b <<"="<<answer<<endl;
        }
        //fractrion
        else{
            double a = 0;
            double b = 0;
            double answer = 0;
            double maximum_positive_frac = 1.79e308;//-1.79E+308 ~ +1.79E+308
            double maximum_negative_frac = -maximum_positive_frac;
            a = stold(first.c_str());
            b = stold(second.c_str());
            answer = multipy_double(a,b);
            if (a>=maximum_positive_frac||a<=maximum_negative_frac||b>=maximum_positive_frac||b<=maximum_negative_frac||answer>=maximum_positive_frac||answer<=maximum_negative_frac){
                cout<<"Warning, the result overflows. The fixing operation is conducting......"<<endl;  
                cout << first << " * " << second << " = ";   
                string first_exp, second_exp,first_frac, second_frac;
                int num_first_exp,num_second_exp,ans_exp;
                double num_first_frac, num_second_frac, ans_frac;         
                if (e_detect(first)&&e_detect(second)){
                    first_exp = first.substr(e_detect(first)+1,first.length());
                    first_frac = first.substr(0,e_detect(first));
                    second_exp = second.substr(e_detect(second)+1,second.length());
                    second_frac = second.substr(0,e_detect(second));
                    num_first_exp = atoi(first_exp.c_str());
                    num_first_frac = stold(first_frac.c_str());
                    num_second_exp = atoi(second_exp.c_str());
                    num_second_frac = stold(second_frac.c_str());
                    ans_exp = num_first_exp+num_second_exp;
                    ans_frac = num_first_frac*num_second_frac;
                    if (ans_exp == 0){
                        cout << ans_frac <<endl;
                    }
                    else {
                        cout<< ans_frac <<"e"<<ans_exp<<endl;
                    }
                    return 0;
                }
                else if (e_detect(first)){
                    first_exp = first.substr(e_detect(first)+1,first.length());
                    first_frac = first.substr(0,e_detect(first));
                    num_first_exp = atoi(first_exp.c_str());
                    num_first_frac = stold(first_frac.c_str());
                    ans_exp = num_first_exp;
                    ans_frac = num_first_frac*b;
                    if (ans_exp == 0){
                        cout << ans_frac <<endl;
                    }
                    else {
                        cout<< ans_frac <<"e"<<ans_exp<<endl;
                    }
                    return 0;
                }
                else {
                    second_exp = second.substr(e_detect(second)+1,second.length());
                    second_frac = second.substr(0,e_detect(second));
                    num_second_exp = atoi(second_exp.c_str());
                    num_second_frac = stold(second_frac.c_str());
                    ans_exp = num_second_exp;
                    ans_frac = num_second_frac*a;
                    if (ans_exp == 0){
                        cout << ans_frac <<endl;
                    }
                    else {
                        cout<< ans_frac <<"e"<<ans_exp<<endl;
                    }
                    return 0;
                }
                return 0;
            }
            cout<<"Fraction operation: "<< a << "*" << b <<"="<<answer<<endl;
        }
    }
    else{
    // cannot be regarded as numbers 
        cout<<"The input cannot be interpret as numbers, please check."<<endl;
    }
    }
    return 0;
}