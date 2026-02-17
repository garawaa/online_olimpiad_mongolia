#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <algorithm>
using namespace std;

void ac(const string& okmessage) {
    cout << "1" << endl;
    cerr << okmessage;
    exit(0);
}

void wa(const string& errorMessage) {
    cout << "0" << endl;
    cerr << errorMessage;
    exit(0);
}

int main(int argc, char **argv) {

    string jAns, pAns;
    int n;

    ifstream inf(argv[1]), ouf(argv[2]), ans(argv[3]);

	ans>>jAns;
	ouf>>pAns;
//cout<<pAns<<" "<<jAns<<endl;
    inf >> n;
    string *num = new string[n];
    for (int i = 0; i < n; i++) 
        inf >> num[i];

    if (jAns != "Yes" && jAns != "No") {
        wa("Хариу буруу байна");
    }

    if (jAns == "Yes" && pAns == "No") {
        wa("Таны хариу буруу");
    }

    if (jAns == "No" && pAns == "Yes") {
        wa("Таны хариу буруу");
    }

    if (jAns == "Yes") {
        int *an = new int[10];
        bool *used = new bool[10]();
        for (int i = 0; i < 10; i++) {
            if (!(ans >> an[i]) || an[i] < 0 || an[i] > 9) {
                wa("Цифр биш байна");
            }
            if (used[an[i]]) {
                wa("Ялгаатай үсэг нэг цифртэй харгалзаад байна");
            }
            used[an[i]] = true;
        }

        int *ch = new int[n];
        for (int i = 0; i < n; i++) {
            if (num[i].length() != 1 && an[num[i][0] - 'a'] == 0) {
                wa("0-р эхэлсэн тоо үүсгэхэд хүрч байна");
            }
            ch[i] = 0;
            for (char c : num[i]) {
                ch[i] = ch[i] * 10 + an[c - 'a'];
            }
        }

        for (int i = 1; i < n; i++) {
            if (ch[i - 1] >= ch[i]) {
                wa("Таны хариу буруу");
            }
        }

        delete[] an;
        delete[] used;
        delete[] ch;

        ac("Таны хариулт зөв байна");
    }

    if (jAns == "No" && pAns == "No") {
        ac("Таны хариулт зөв байна");
    }
    delete[] num;
    return 0;
}
