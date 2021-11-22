#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<algorithm>
#include<functional>
#include<sstream>
#include"expr.h"
using namespace std;
extern vector<Expr>exprs;
stack<string>operators;
vector<string>new_expr;
void calculate();
bool is_eng(char x)
{
    return (x >= 'a' && x <= 'z')||(x >= 'A' && x <= 'Z');
}
int mu(char x)
{
    if(x == '+' || x == '*')
	    return 2;
    else if(x == '!' || x == '$')
	    return 1;
    else return 0;
}
bool is_expr_valid(const string& s)
{
    if(s[0]!='(' && s[0] != '$' && !is_eng(s[0]))
    {//cout << "1";
	    return false;}
    int end = s.size() - 1;
    if(s[end]!=')' && s[end]!= '!' && !is_eng(s[end]))
    {//cout << "2";
	    return false;}
    for(int i = 0;i < s.size();i++){
        if(i < end && mu(s[i])==2 && s[i+1]!='('&& s[i+1]!='$'&&!is_eng(s[i+1]))
	{//cout << "3";
		return false;}
	else if(i < end && s[i] == '$' &&s[i+1] != '[')
	{//cout << "33";
		return false;}
	else if(i < end && s[i] == ']' && s[i+1] !='(' && !is_eng(s[i+1]))
	{//cout<<"4";
		return false;}
	else if(i < end && s[i] == '!' && mu(s[i+1])==1 && s[i+1]!=')')	
	{//cout <<"5";
		return false;}
	else if(i < end && s[i] == '(' && s[i+1]!='(' && s[i+1]!='$' && !is_eng(s[i+1]))
	{//cout<<"6";
		return false;}
	else if(i < end && s[i] == ')' && s[i+1]!=')' && s[i+1]!='+'&&s[i+1]!='*' && s[i+1]!='!')
	{//cout<<"7";
		return false;}
	else if(i < end && is_eng(s[i]) && s[i+1] != '!'&& s[i+1]!=')'&&s[i+1]!='+'&&s[i+1]!='*')
	{//cout<<"8";
		return false;}
	else 
		continue;
    }
    return true;
}

bool isSpace(char x) { return x == ' '; }
bool is_operator(char x){
    return x=='+'||x=='*'||x=='!'||x=='$';
}
int operator_int(char x){
    if(x == '!') return 4;
    else if(x == '$') return 3;
    else if(x == '*') return 2;
    else if(x == '+') return 1;
    else return 0;
}
void trans(string& s)
{
    new_expr.clear();
    while(!operators.empty())
	    operators.pop();
    s.erase(remove_if(s.begin(), s.end(), isSpace), s.end());
    int flag = 1;
    if(!is_expr_valid(s)){
	    flag = 0;
	    //cout << "here"<<endl;
    }
    for(int i = 0;i < s.size();i++){
        if(is_eng(s[i])){
	    char tmp[2]={'\0'};
	    tmp[0] = s[i];
	    tmp[1] = '\0';
	    string tmp_s = tmp;
	    new_expr.push_back(tmp_s);
	}
        else if(s[i] == '('){
	    string temp = "(";
	    operators.push(temp);}
	else if(s[i] == ')'){
	    if(operators.empty()){
	        flag = 0;
		
		break;
	    }
	    else{
	        if(operators.top()=="("){flag = 0;break;}
		else{
		    while(operators.top()!="("){
		        new_expr.push_back(operators.top());
			operators.pop();
		    }
		    if(operators.empty()){flag = 0;break;}
		    else operators.pop();
		}
	    }
	}
	else if(is_operator(s[i])){
	     string temp;
	     if(s[i] == '$'){
		temp = temp + '$';
	        int is_$_valid=0;
		int j = i + 1;
	        for(;j<s.size();j++){
		    temp = temp + s[j];
		    if(s[j] == ']'){
		        is_$_valid = 1;
			i = j;
			break;
		    }
		}
		if(is_$_valid == 0){flag = 0;break;}
		else{
		    while(!operators.empty() && operators.top()!="(" && 
				    operator_int(operators.top()[0])>=operator_int('$')){
		        new_expr.push_back(operators.top());
			operators.pop();
		    }
		    operators.push(temp);
		}
	     }
	     else{
	         temp = temp + s[i];
		 while(!operators.empty() && operators.top() != "(" &&
				 operator_int(operators.top()[0])>=operator_int(s[i])){
		     new_expr.push_back(operators.top());
		     operators.pop();
		 }
		 operators.push(temp);
	     }
	}
	else{
	    flag = 0;
	    break;
	}
    }
    while(!operators.empty()){
        new_expr.push_back(operators.top());
	operators.pop();
    }
    if(flag == 0)
	    cout << "输入不合法"<<endl;
    else{
       // for(int i = 0;i < new_expr.size();i++){
	 //   cout << new_expr[i] << " ";
	//}
	//cout << endl;
	calculate();
    }
}
bool is_name_exist(const string& name)
{
    for(int i = 0;i < exprs.size();i++)
	    if(name == exprs[i].name)
		    return true;
    return false;
}
bool isNum(const string& str)
{
    stringstream sin(str);
    double d;
    char c;
    if(!(sin >> d))
        return false;
    if (sin >> c)
        return false;
    return true;
}
bool is_$_valid(const string& s)
{
    int dh = 0;
    int i = 0;
    for(;i < s.size();i++)
	    if(s[i] == ','){
	        dh = 1;
		break;
	    }
    if(dh == 0)
	    return false;
    else{
        string n1 = s.substr(2,i-2);
	string n2 = s.substr(i+1,s.size()-i-2);
//	cout << n1 <<" "<<n2<<endl;
	if(!isNum(n1)||!isNum(n2))
		return false;
    }
    return true;
}
Expr into_expr(const string& name)
{
    for(int i = 0;i < exprs.size();i++)
	    if(name == exprs[i].name)
		    return exprs[i];
}
Expr one_c(const string& name,const string& c)
{
    Expr A = into_expr(name);
    if(c[0] == '!'){
	Expr B= A.deriv();
	string s="1";
	while(is_name_exist(s))
		s =s +"1";
	B.name = s;
	return B;
    }
    else if(c[0] == '$'){
        int i = 0;
        for(;i < c.size();i++)
            if(c[i] == ',')
                break;
	string n1 = c.substr(2,i-2);
        string n2 = c.substr(i+1,c.size()-i-2);
	double x1 = atof(n1.c_str());
	double x2 = atof(n2.c_str());
	double x = A.origin_func().eval(x2)-A.origin_func().eval(x1);
	Expr B;
	B.len = 1;
	B.co[0] = x;
	B.power[0] = 0;
	string s = "3";
	while(is_name_exist(s))
		s = s+"3";
	B.name = s;
	return B;
    }
}
Expr two_c(const string& name1,const string& name2,const string& c)
{
    Expr A = into_expr(name1);
    Expr B = into_expr(name2);
    Expr C;
    if(c == "*")
	    C = A * B;
    else if(c == "+")
	    C = A + B;
    string name = "2";
    while(is_name_exist(name))
	    name = name + "2";
    C.name = name;
    return C;
}

void calculate()
{
   int flag = 1;
   for(int i = 0;i < new_expr.size();i++){ 
	 if(is_eng(new_expr[i][0])){
		if(!is_name_exist(new_expr[i])){
		    cout << "名称错误"<<endl;
		    flag = 0;
		    break;
		}
	 }
	 else if(new_expr[i][0] == '$'){
	     if(!is_$_valid(new_expr[i])){
	         cout<<"输入不合法"<<endl;
		 flag = 0;
		 break;
	     }     
	 }
    }
    if(flag == 1){
	stack<string>st;
	for(int i = 0;i < new_expr.size();i++){
	    if(is_eng(new_expr[i][0]))
		    st.push(new_expr[i]);
	    else{
	        if(mu(new_expr[i][0])==1){
		    Expr tmp = one_c(st.top(),new_expr[i]);
		    exprs.push_back(tmp);
		    st.pop();
	    	    st.push(tmp.name);	    
		}
		else if(mu(new_expr[i][0]) == 2){
		    string name1 = st.top();
		    st.pop();
		    string name2 = st.top();
		    st.pop();
		    Expr tmp = two_c(name1,name2,new_expr[i]);
		    exprs.push_back(tmp);
		    st.push(tmp.name);
		}
	    }
	}
	Expr A = into_expr(st.top());
	A.display();
    }

}
