#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const string alphabet = "abcdefghijklmnopqrstuvwxyz/<>";


static bool isWord(string const & s)
{
	for (int i = 0; i < (int) s.length(); i++)
	{
		if (s[i] < 'a' || s[i] > 'z')
		{
			return false;
		}
	}
	return true;
}

static bool checkXML(string const & s)
{
	vector <string> st;
	for (int curPos = 0; curPos < (int) s.length(); )
	{
		if (s[curPos] != '<')
		{
			return false;
		}
		int pos = s.find(">", curPos);
		if (pos < 0)
		{
			return false;
		}
		string w = s.substr(curPos + 1, pos - curPos - 1);
		if (w.empty())
		{
			return false;
		}
		if (w[0] == '/')
		{
			w = w.substr(1);
			if (!isWord(w))
			{
				return false;
			}
			if (st.empty() || st.back() != w)
			{
				return false;
			}
			st.pop_back();
		}
		else
		{	
			if (!isWord(w))
			{
				return false;
			}
			st.push_back(w);
		}
		curPos = pos + 1;
	}
	return st.empty();
}

int main() 
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	string s;
	fin >> s;
	for (int i = 0; i < (int) s.length(); i++)
	{
		char old = s[i];
		for (int j = 0; j < (int) alphabet.length(); j++)
		{
			s[i] = alphabet[j];
			if (checkXML(s)) 
			{
				fout << s;
				return 0;
			}
		}
		s[i] = old;
	}
	throw 1;
}
