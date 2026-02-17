#include<iostream>
#include<cstring>
#include <utility>
using namespace std;

string bintooct(string s)
{
	if(s=="000") return "0"; else;
	if(s=="001") return "1"; else;
	if(s=="010") return "2"; else;
	if(s=="011") return "3"; else;
	if(s=="100") return "4"; else;
	if(s=="101") return "5"; else;
	if(s=="110") return "6"; else;
	if(s=="111") return "7"; 
}
int main()
{
	string binnum,octnum;
	cin>>binnum;
	int n = binnum.length();
	if (n%3 ==1) binnum = "00"+binnum;
	if (n%3 ==2) binnum = "0"+binnum;
	octnum="";
	for(int i=0;i<n;i+=3)
	{
		octnum+=bintooct(binnum.substr(i,3));
	}
	cout<<octnum;
	return 0;
}
