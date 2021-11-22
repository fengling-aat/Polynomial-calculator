#include<iostream>
#include<string>
using namespace std;

bool is_letter(char x){
    return (x >= 'a' && x <= 'z') || (x >= 'A'&& x <= 'Z');
}

bool is_name_valid(const string& name)
{
    if(name.length() != 1)
	    return false;
    for(int i = 0;i<name.size();i++)
	if(!is_letter(name[i]))
		return false;
    return true;
}
