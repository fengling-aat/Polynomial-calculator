#include<iostream>
#include<vector>
#include<string>
#include"expr.h"
#include"judge.h"
#include<cmath>
using namespace std;
//extern vector<Expr>exprs;
vector<Expr>exprs;
bool is_name_included(string& s)
{
    for(int i = 0;i < exprs.size();i++)
	    if(exprs[i].name == s)
		    return true;
    return false;
}
void input_one()
{
    cout <<"多项式长度：";
    int length;
    Expr A;
    cin >> length;
    A.len = length;
    cout <<"请输入各位系数(从高到低）："<<endl;
    double xs;
    for(int i = length -1;i >= 0;i--){
        cin >> xs;
        A.co[i] = xs;
        A.power[i] = i;
    }
    string name;
    cout << "多项式名为(格式为单个英文字母)：";
    cin >> name;
    if(!is_name_valid(name)){
        cout << "名称格式错误"<<endl;
        return;
    }
    if(is_name_included(name)){
        cout <<"名称已存在"<<endl;
	return;
    }
    A.name = name;
    int flag = 0;
    for(int i = 0;i < exprs.size();i++)
            if(name == exprs[i].name){
                flag = 1;
                break;
            }
    if(flag == 1)
            cout << "该名称已存在，输入失败"<<endl;
    else{
        exprs.push_back(A);
        cout << "输入成功"<<endl;
    }
}

void input()
{
    string yorn;
    while(true){
        input_one();
	cout <<"是否继续输入(y/....):";
	cin >> yorn;
	if(yorn == "y")
		continue;
	else
		break;
    }
    cout << endl;
}

void output()
{
    cout << "多项式名为：";
    string name;
    cin >> name;
    int flag = 0;
    for(int i = 0;i < exprs.size();++i)
	if(name == exprs[i].name){
	    exprs[i].display();
	    flag = 1;
	    break;
	}
    if(flag == 0)
	    cout << "输入多项式名错误."<<endl;
    cout << endl;
}

void reverse()
{
    string name;
    cout <<"多项式名为：";
    cin >> name;
    if(!is_name_included(name)){
        cout << "名称不存在"<<endl;
	return;
    }
    Expr A;
    for(int i = 0;i < exprs.size();i++)
	    if(name == exprs[i].name){
	        A = exprs[i];
		break;
	    }
    Expr B;
    B.len = A.len;
    for(int i = 0;i < B.len;i++)
	    B.power[i] = i;
    if(A.co[0] == 0){
        cout << "逆元不存在"<<endl;
	return;
    }
    B.co[0] = 1/A.co[0];
    for(int i = 1;i < B.len;i++){
        double sum = 0;
	for(int j = 0;j < i;j++)
		sum += -B.co[j]*A.co[i-j]/A.co[0];
	B.co[i] = sum;
    }
    cout << "逆元为:";
    B.display();
    cout << endl;
}
int deg(Expr& A)
{
    int flag = 0;
    for(int i = 49;i >= 0;i--)
	    if(A.co[i] != 0){
	        flag = i;
		break;
	    }
    return flag+1;
}
void division()
{
    string expr;
    cout <<"请输入表达式（F/G):";
    cin >> expr;
    string name1;
    string name2;
    if(expr[1] != '/'||expr.length()!=3){
        cout << "格式错误"<<endl;
	return;
    }
    char temp1[2],temp2[2];
    temp1[0] = expr[0];temp1[1] = '\0';
    temp2[0] = expr[2];temp2[1] = '\0';
    name1 = temp1;
    name2 = temp2;
    if(!is_name_included(name1) || !is_name_included(name2)){
        cout <<"名称不存在"<<endl;
	return;
    }
    Expr A,B;
    for(int i = 0;i < exprs.size();i++){
	    if(exprs[i].name == name1){
	        A = exprs[i];
	    }
	    if(exprs[i].name == name2)
		    B = exprs[i];
    }
    if(A.len < B.len){
        cout << "商为：0,余数为:";
	A.display();
    }
    else{
        vector<Expr>temps;
	while(deg(A) >= deg(B)){
	    Expr temp;
	    temp.len = A.len - B.len + 1;
	    for(int i = 0;i < temp.len;i++)
		    temp.power[i] = i;
	    temp.co[temp.len-1] = A.co[A.len-1]/B.co[B.len-1];
	    temps.push_back(temp);
	    Expr C = B*temp;
	   // temp.display();
	    A = A - C;
	    A.len = deg(A);
	   // A.display();
	}
	for(int i = 1;i < temps.size();i++)
		temps[0] = temps[0]+temps[i];
	cout << "商为:";
	temps[0].display();
	cout << "余数为:";
	A.len = deg(A);
	//cout << A.len<<endl;
	A.display();
    }
    cout << endl;
}

void Newton()
{
    string name;
    cout << "多项式名为:";
    cin >> name;
    if(!is_name_included(name)){
        cout <<"名称不存在"<<endl;
	return;
    }
    Expr A;
    for(int i = 0;i < exprs.size();i++)
	    if(name == exprs[i].name){
	        A = exprs[i];
		break;
	    }
    double x = 1;
    int times = 0;
    int flag = 0;
    while(times < 100){
        if(abs(A.eval(x))<=0.00001){
	    flag = 1;
	    break;
	}
	else{
	    x = x - A.eval(x)/A.deriv().eval(x);
	    times += 1;
	}
    }
    if(flag == 1)
	    cout << "存在的一个实数根为:"<<x << endl;
    else
	    cout << "实数根不存在"<<endl;
    cout << endl;
}
