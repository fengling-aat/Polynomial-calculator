#ifndef EXPR_H_
#define EXPR_H_
// 你的代码块
#include<iostream>
#include<cstdlib>
#include<string>
#include<string.h>
#include<fstream>
#include <math.h>
using namespace std;
//Expr Expr::deriv();
//Expr Expr::operator !(int);
//double Expr::eval(double x);
//void Expr::display();
//Expr Expr::origin_func();
//Expr operator +(Expr& s1, Expr& s2);
//Expr operator *(Expr& s1,Expr& s2);
//Expr operator -(Expr& s1, Expr& s2);
class Expr{

public:
    int len;
    double co[50];
    int power[50];
    string name;
    Expr(){
        for(int i = 0;i < 50;i++){
	    co[i] = 0;
	    power[i] = -1;
	}
	name = "";
    }
    Expr deriv();
    double eval(double x);
    void display();
    Expr origin_func();
    Expr operator!(){
        return deriv();
    }
   /* double operator $[double a,double b](){
        Expr temp = origin_func();
	temp.value = b;
	double top = temp.eval();
	temp.value = a;
	double bottom = temp.eval();
	return top-bottom;
    }*/
};
Expr operator +(Expr& s1, Expr& s2);
Expr operator *(Expr& s1,Expr& s2);
Expr operator -(Expr& s1, Expr& s2);
/*Expr Expr::deriv()
{
    Expr dhs;
    dhs.len = len - 1;
    for(int i = 1;i < len;i++){
        dhs.co[i-1]=co[i]*power[i];
	dhs.power[i-1] = power[i]-1;
    }
    return dhs;
}

Expr Expr::operator !(int)
{
    Expr temp = *this;
    for(int i = 1;i < len;i++){
	this->co[i-1] = this->co[i]*this->power[i];
        this->power[i-1] = this->power[i]-1;	
    }
    return temp;
}

double Expr::eval(double x)
{
    double sum = 0;
    for(int i = 0;i < len;i++)
	    sum += co[i]*pow(x,power[i]);
    return sum;
}

void Expr::display()
{
    for(int i = len-1;i >= 0;i--){
	if(power[i] == 0){
	    if(co[i] > 0)
		    cout << "+"<<co[i];
	    else if(co[i]<0) cout << co[i];
	}
	else{
        if(i == len-1 || co[i] < 0){
		if(co[i] == -1 )
			cout <<"-";
		else if(co[i] != 1) cout << co[i];
	}
	else if(co[i] > 0){
		if(co[i] != 1)
			cout << "+"<< co[i];
		else cout <<"+";
	}
	if(co[i] != 0){
	    if(power[i] == 1)
		    cout << "x";
	    else cout <<"x^"<<power[i];
	}
	}
    }
    cout << endl;
}

Expr Expr::origin_func()
{
    Expr yhs;
    yhs.len = len + 1;
    for(int j = 0;j < yhs.len;j++)
	    yhs.power[j] = j;
    for(int i = 0;i < len;i++)
	    yhs.co[i+1] = co[i]/(i+1);
    return yhs;
}

Expr operator +(Expr& s1, Expr& s2)
{
    Expr s;
    if(s1.len > s2.len)
	    s.len = s1.len;
    else s.len = s2.len;
    for(int i = 0;i < s.len;i++){
        s.co[i] = s1.co[i] + s2.co[i];
	s.power[i] = i;
    }
    return s;
}

Expr operator -(Expr& s1, Expr& s2)
{
    Expr s;
    if(s1.len > s2.len)
            s.len = s1.len;
    else s.len = s2.len;
    for(int i = 0;i < s.len;i++){
        s.co[i] = s1.co[i] - s2.co[i];
        s.power[i] = i;
    }
    return s;
}

Expr operator *(Expr& s1,Expr& s2)
{
    Expr s;
    s.len = s1.len + s2.len - 1;
    for(int i = 0;i < s.len;i++)
	    s.power[i] = i;
    for(int i = 0;i < s1.len; i++)
	for(int j = 0;j < s2.len;j++){
	    s.co[i+j] += s1.co[i] * s2.co[j];
	}
    return s;
}*/
#endif
//#endif
