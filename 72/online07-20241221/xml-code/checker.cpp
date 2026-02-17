#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
using namespace std;

const int MAXN = 100000;
void ac(const string& okmessage)
{
	cout<<"1"<<endl;
    cerr <<okmessage;
    exit(0);
}
void wa(const string& errorMessage) {
	cout<<"0"<<endl;
    cerr <<errorMessage;
    exit(0);
}

bool checkXML(const string& s, vector<string>& stack) {
    int curPos = 0;
    int cur = 0;
    while (curPos < s.length()) {
        if (s[curPos] != '<') {
            wa("Invalid XML in output file: position #" + std::to_string(curPos) + ", expected '<'");
        }
        int p = -1;
        for (int i = curPos + 1; i < s.length(); i++) {
            if (s[i] == '>') {
                p = i;
                break;
            }
        }
        if (p == -1) {
            wa("Invalid XML in output file: '>' expected after position #" + std::to_string(curPos));
        }
        if ((p - curPos < 2) || ((p - curPos < 3) && (s[curPos + 1] == '/'))) {
            wa("Invalid XML in output file: empty name of tag in position #" + std::to_string(curPos));
        }
        for (int i = curPos + 1; i < p; i++) {
            if (!(s[i] >= 'a' && s[i] <= 'z') && (i > curPos + 1 || s[i] != '/')) {
                wa("Invalid XML in output file: name of tag in position #" + std::to_string(curPos) + " contains invalid characters");
            }
        }
        if (s[curPos + 1] == '/') {
            string t = s.substr(curPos + 2, p - curPos - 2);
            if (--cur < 0 || stack[cur] != t) {
                wa("Invalid XML in output file: no pair for closing tag in position #" + std::to_string(curPos) + " was found");
            }
        } else {
            string t = s.substr(curPos + 1, p - curPos - 1);
            if (cur >= MAXN) {
                wa("Stack overflow");
            }
            stack[cur++] = t;
        }
        curPos = p + 1;
    }
    if (cur != 0) {
        wa("Invalid XML in output file: no pair for some tag <" + stack[cur - 1] + "> was found");
    }
    return true;
}

int main(int argc, char **argv) {

    string s, t;
    ifstream inf(argv[1]),ouf(argv[2]),ans(argv[3]);

	inf>>s;
	ans>>t;

    if (s.length() != t.length()) {
        wa("Length of output string isn't equal to the length of input string");
    }

    std::vector<std::string> stack(MAXN);
    if (!checkXML(t, stack)) {
        wa("Invalid XML in output file");
    }

    int changes = 0;
    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] != t[i]) {
            changes++;
        }
    }

    if (changes > 1) {
        wa("Contestant made " + std::to_string(changes) + " changes to the input string, but not more than one change is allowed");
    }

    for (size_t i = 0; i < t.length(); i++) {
        if (!(t[i] >= 'a' && t[i] <= 'z') && t[i] != '/' && t[i] != '<' && t[i] != '>') {
            wa("Invalid character in output: " + std::string(1, t[i]));
        }
    }

/*    if (changes == 0) {
        wa("FAIL", "Good XML in input file");
    }*/

    ac("Contestant found valid XML");
//    return 0;
}

