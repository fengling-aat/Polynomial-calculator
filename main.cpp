#include<iostream>
#include<vector>
#include<string>
#include<stdlib.h>
#include"calculate.h"
#include"io.h"
//#include"expr.h"
using namespace std;
//vector<Expr>exprs;
void compute()
{
    string s;
    string yorn;
    while(true){
        cout << "请输入表达式：";
	getline(cin,s);
        getline(cin,s);
	cout << "结果为:";
	trans(s);
	cout <<"是否继续输入(y/....):";
	cin >> yorn;
	s = " ";
        if(yorn == "y")
	{cout << endl;continue;}
        else
                break;
    }
    cout << endl;
}
void menu()
{
    cout << "==========多项式计算器=========="<<endl;
    //cout << "1. 输入 2.查看 3.混合运算 4.多项式求逆 0.退出"<<endl;
    int x;
    while(true){
	cout << "1. 输入 2.查看 3.混合运算 4.多项式求逆 5.多项式除法 6.多项式求根 0.退出"<<endl;
	cout <<"请输入你的选择：";
        cin>> x;
	switch(x){
	case 0:exit(0);break;
	case 1:input();break;
	case 2:output();break;
	case 3:compute();break;
	case 4:reverse();break;
	case 5:division();break;
	case 6:Newton();break;
	default:cout << "输入有误，请重输:";cin >> x;

	}
    }
}

int main()
{
    //cout << is_$_valid(s);
   // getline(cin,s);
   // trans(s);
    menu();
    return 0;
  /* string str;
   char s[2]={'f',0};
   str = s;
   cout << str <<" "<<str.length()<<endl ;*/
   /* int length;
    cin >> length;
    Expr A;
    A.len = length;
    int xs;
    for(int i = length-1;i >= 0;i--){
        cin >> xs;
	A.co[i] = xs;
	A.power[i] = i;
    }
    A.display();
    
    cout << "value is "<<A.eval(1)<<endl;
    Expr F;
    F = A.origin_func();
    F.display()
    Expr R = !F;
    R.display();*/
     
   // Expr B = A.deriv();
   // B.display();
   // Expr C;
   // C = A + B;
   // C.display();
   // Expr D;
   // D = A - B;
   // D.display();
   // Expr E;
   // E = C * D;
   // E.display();
}
