#include <bits/stdc++.h>
using namespace std;

void ac() {
    printf("1\n");
    fprintf(stderr,"answer is correct.\n");
}
void wa() {
    printf("0\n");
    fprintf(stderr,"answer is incorrect\n");
}


int main(int argc, char **argv) { 
	long m;
	string pa,ja,sn;
    ifstream inf(argv[1]); //Оролт унших файл
    ifstream ans(argv[2]); //Шүүгч
    ifstream ouf(argv[3]); //Оролцогч

	ouf>>pa;
    ans>>ja;
    inf>>sn>>m;

	bool flag = false;
        if (ja == "-1") {
            if (pa == "-1") {
                ac(); return 0;
            }
            flag = true;
        }

        if (pa == "-1") {
            wa(); return 0;
        }

        if (pa.length() != sn.length()) {
            wa(); return 0;
        }

        if (pa.length() > 1 && pa[0] == '0') {
            wa(); return 0;
        }

long pn;
try {
    pn = stol(pa); // string → long хөрвүүлнэ
} catch (const invalid_argument& e) {
    wa(); return 0;
} catch (const out_of_range& e) {
    wa(); return 0;
}
        if (pn < 0) {
            wa(); return 0;
        }

        if (pn % m != 0) {
            wa(); return 0;
        }

        if (flag) {
            wa(); return 0;
        }

        int balp = 0, balj = 0;

        for (int i = 0; i < sn.length(); ++i) {
            if (pa[i] != sn[i]) {
                ++balp;
            }
            if (ja[i] != sn[i]) {
                ++balj;
            }
        }

        if (balp > balj) {
            wa(); return 0;
        }

        if (balp < balj) {
            wa(); return 0;
        }
    ac();
    return 0;
}
