#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <set>
#include <map>

using namespace std;

const int MAXN = 100;

const int MAXLEN = 5000000;

const double PerTest = 1.0;

string cur[MAXN];
string need[MAXN];
                     

const int    dx[4] = {  1,  0, -1,  0};
const int    dy[4] = {  0,  1,  0, -1};
const char name[4] = {'d','r','u','l'};


int getScore(int x,int n){
	if (x <= 3*n*n) return 5;
	if (x <= 5*n*n) return 4;
	if (x <= 10*n*n) return 3;
	if (x <= 2.5*n*n*n) return 2;
	return 1;
}

void ac(const string& okmessage) {
    cout << "1" << endl;
    cerr << okmessage;
    exit(0);
}
void ac1(int score, const string& okmessage) {
    cout << to_string(score*0.2) << endl;
    cerr << okmessage;
    exit(0);
}

void wa(const string& errorMessage) {
    cout << "0" << endl;
    cerr << errorMessage;
    exit(0);
}

int main(int argc, char* argv[]) {
    ifstream inf(argv[1]), ouf(argv[2]), ans(argv[3]);
	int n;
	inf>>n;

	for (int i = 0; i < n; i++){
		inf>>need[i];
		cur[i] = string(n,'W');
	}

	cur[0][0] = 'B';

	string out;

	ans>>out;

	if ((int)out.length() > MAXLEN)
		wa("Таны хариулт хэтэрхий урт байна!");
                    
	int curx = 0, cury = 0;

	for (int i = 0; i < (int)out.size(); i++){
		for (int j = 0; j <= 4; j++){
			if (j == 4)
				wa("Буруу тэмдэгт ашигласан байна!");
			if (name[j] == out[i] || name[j] == out[i] + 'a' - 'A'){
				 curx += dx[j];
				 cury += dy[j];

				 if (!(0 <= curx && 0 <= cury && curx < n && cury < n)){
				 	wa("Таны шилжилт өгсөн талбайгаас гарсан!");
				 }

				 if ('A' <= out[i] && out[i] <= 'Z')
				 	cur[curx][cury] = cur[curx - dx[j]][cury - dy[j]];
				 break;
			}
		}	    

	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (cur[i][j] != need[i][j])
				wa("Таны хариулт буруу!");

	if (n <= 25)
		ac("Таны хариулт зөв. N = "+to_string(n)+" курсор шилжсэн тоо: "+to_string(out.size()));
    else {
    	if ((int)out.size() <= 3 * n * n)
			ac("Таны хариулт зөв. N = "+to_string(n)+" курсор шилжсэн тоо: "+to_string(out.size()));    		
		else {
			int tmp = getScore(out.size(), n);
			ac1(tmp, "Таны хариулт зөв. Оноо: "+to_string(tmp)+", N = "+to_string(n)+" курсор шилжсэн тоо: "+to_string(out.size()));    		
		}          
    }
  return 0;
}
