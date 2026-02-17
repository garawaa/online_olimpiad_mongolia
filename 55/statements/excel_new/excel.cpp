#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <string.h>
 
using namespace std;
const int size = 26 * 9;
const int MAX_SIZE = 255 + 10;
enum TYPE {WHITE, GRAY, BLACK};
int n;
vector<string> exp(size);
vector<int> value(size);
vector<set<int> > adj(size);
vector<TYPE> used(size, WHITE);
 
stack<char> opers;
stack<int>  numbers;
void trim(string &str)
{
    while (str[0] == ' ')
        str.erase(0,1);
    while (str[str.size()-1]==' ')
        str.erase(str.size()-1,1);
}
int code(const char *pos) {
    return (*pos - 'A') * 9 + *(pos+1) - '1';
}
int code(const string &s)
{
    return code(s.c_str());
}
 
bool isLetter(char c) {
    return 'A' <= c && c<= 'Z';
}
bool isDigit(char c) {
    return '0'<= c && c <= '9';
}
void fillAdj(int index, string s)
{
    for (int i = 0; i<s.size();i++) {
        if (isLetter(s[i])) {
            adj[index].insert(code(s.substr(i,2)));
        }
    }
}
void input()
{
    scanf("%d\n",&n);
    string str,f,s;
    int pos;
    for (int i=0;i<n;i++)
    {
        getline(cin,str);
        pos = str.find('=');
        f = str.substr(0,pos);
        s = str.substr(pos+1,str.size() - (pos+1));
        trim(f);
        trim(s);    
        exp[code(f)] = s;
        fillAdj(code(f),s);
    }
}
void dfs(int pos, vector<int> &G, bool &isCircle) {
    
    used[pos] = GRAY;
    for (set<int>::iterator it=adj[pos].begin(); it != adj[pos].end(); it++) {
        
        if (isCircle) return;
 
        if (used[*it] == GRAY) {
            isCircle = true;
            break;
        }
        else if (used[*it] == WHITE){
            dfs(*it,G,isCircle);
        }
    }
    G.push_back(pos);
    used[pos] = BLACK;
}
bool topological_sort(vector<int> &G) {
 
    bool isCircle = false;
    dfs(0,G,isCircle);
    return isCircle;
}
inline bool isEnd(const char * pos) {
    return *pos == 0;
}
void SkipSep(char* &pos) {
    while (!isEnd(pos) && *pos == ' ')
        pos++;
}
bool isOper(const char* pos) {
    return !isEnd(pos) &&
     (  *pos == '+' || 
        *pos == '-' ||
        *pos == '*' ||
        *pos == '/' );
}
int prior (const char pos) {
    if (pos == '+' || pos == '-')
        return 1;
    else
        return 2;
}
void ReadCell(char* &pos, int &number) {
    int cell = code(pos);
    pos+=2;
    number = value[cell];
}
void ReadNumber (char* &pos, int &number) {
    number = 0;
    while (!isEnd(pos) && isDigit(*pos)) {
        number = number * 10 + (*pos - '0');
        pos++;
    }
}
void calcExp(char* &pos, int &res);
void ReadNextValue(char* &pos, int &number) {
 
    if (*pos == '(') {
        pos++;
        calcExp(pos,number);
        pos++;
    }
    else {
 
        if (isLetter(*pos))
            ReadCell(pos, number);
        if (isDigit(*pos))
            ReadNumber(pos, number);
    }
}
int calc(int f, int s, char oper) {
    switch(oper) {
        case '+': return f + s;
        case '-': return f - s;
        case '*': return f * s;
        case '/': if (s == 0) 
                      return 0;
                  else
                      return f/s;
    }
}
void calcExp(char* &pos, int &res) {
 
    stack<int> locNumbers;
    stack<char> locOper;
    do
    {
        SkipSep(pos);
        if (isOper(pos)) {
            char curOper = *pos++;
            
            while (!locOper.empty() && prior(locOper.top()) > prior(curOper)) {
                
                int s = locNumbers.top();               locNumbers.pop();
                int f = locNumbers.top();               locNumbers.pop();
                int locRes = calc(f,s,locOper.top());   locOper.pop();
                locNumbers.push(locRes);
            }
            locOper.push(curOper);
        }
        else {
            int number = 0;
            ReadNextValue(pos, number);
            locNumbers.push(number);
        }
        SkipSep(pos);
    } while (!isEnd(pos) && *pos != ')');
 
    while (!locOper.empty()) {
        int s = locNumbers.top(); locNumbers.pop();
        int f = locNumbers.top(); locNumbers.pop();
        int locRes = calc(f,s,locOper.top());
        locOper.pop();
        locNumbers.push(locRes);
    }
    res = locNumbers.top();
}
void solve()
{
    vector<int> G;
    if (topological_sort(G)) {
        cout<<(int)1e6;
    }
    else {
        if (G.empty()) G.push_back(0);
 
        for (int i=0;i<G.size();i++) {
            char *buf = new char[MAX_SIZE];
            strcpy(buf,exp[G[i]].c_str());
            calcExp(buf,value[G[i]]);
        }
        cout<<value[0];
    }
}
int main()
{
    //freopen("input.txt","r",stdin);
   // freopen("output.txt","w",stdout);
 
    input();
    solve();
    return 0;
}
