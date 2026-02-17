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

bool isNumber(string &str) {
		for (int i = 0; i < str.length(); i++) {
			char c = str[i];
			if (c < '0' || c > '9') {
				return false;
			}
			if (i == 0 && c == '0') {
				return false;
			}
		}
		return true;
}

map<int,int> digitize(string &str) {
		map<int,int> result;
		for (int i = 0; i < str.length(); i++) {
			result[str[i] - '0']++;
		}
		return result;
}
string multiplyLargeNumbers(const string &num1, const string &num2) {
    int len1 = num1.size();
    int len2 = num2.size();
    vector<int> result(len1 + len2, 0);

    // Тоог цифрээр үржүүлэх
    for (int i = len1 - 1; i >= 0; --i) {
        for (int j = len2 - 1; j >= 0; --j) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = mul + result[i + j + 1];
            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }

    // Үр дүнг тэмдэгт мөр болгон хувиргах
    string product;
    for (int num : result) {
        if (!(product.empty() && num == 0)) {
            product.push_back(num + '0');
        }
    }

    return product.empty() ? "0" : product;
}
string isVampire(string &vampireStr, string &fang1Str, string &fang2Str, int n) {
		if (vampireStr != multiplyLargeNumbers(fang1Str,fang2Str)) {
			return "Хоёр шүдний үржвэр буруу байна.";
		}
		if (vampireStr.length() != n) {
			return "Тооны урт буруу байна.";
		}
		if (fang1Str.length() != n / 2) {
			return "Шүд 1 -ийн урт буруу.";
		}
		if (fang2Str.length() != n / 2) {
			return "Шүд 2 -ийн урт буруу.";
		}

		map<int,int> cnt1 = digitize(vampireStr);
		map<int,int> cnt2 = digitize(fang1Str);
		map<int,int> cnt3 = digitize(fang2Str);
		for (int i = 0; i < 10; i++) {
			if (cnt1[i] != (cnt2[i] + cnt3[i])) {
				return to_string(i) + " цифрийн тоо буруу байна.";
			}
		}
		return "";
}
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
vector<string> split(const string &str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

int main(int argc, char* argv[]) {
    ifstream inf(argv[1]), /*ouf(argv[2]),*/ ans(argv[3]);
    int k, n;
    inf >> k >> n;

    set<string> usedNumbers;
    for (int i = 0; i < k; ++i) {
        string line;
        if (!getline(ans, line)) {
            wa(to_string(i + 1)+"-р мөрийг гаргаагүй орхисон.");
        }

        vector<string> data = split(line,'=');
        
		if (data.size() != 2) {
            wa(to_string(i + 1)+"-р мөрөнд '=' байхгүй эсвэл олон байна.");
        }

		if (!isNumber(data[0])) {
			wa(data[0]+" буруу форматтай тоо.");
		}
			
		vector<string> data2 = split(data[1],'x');
		if (data2.size() != 2) {
			wa("Үржих x тэмдэг байхгүй эсвэл олон байна.");
		}
		if (!isNumber(data2[0])) {
			wa("Шүд1 нь буруу форматтай тоо байна.");
		}
		if (!isNumber(data2[1])) {
			wa("Шүд2 нь буруу форматтай тоо байна.");
		}

        string error = isVampire(data[0], data2[0], data2[1], n);
        if (error !="") {
            wa(to_string(i + 1) + "-р мөр: таны гаргасан тоо вампирын тоо биш - " + error);
        }

        if (usedNumbers.find(data[0])!=usedNumbers.end()) {
            wa(to_string (i + 1) + "-р мөр: Таны гаргасан тоо аль хэдийнэ ашиглагдсан байна.");
        }

        usedNumbers.insert(data[0]);
    }

    ac("Таны хариу зөв байна.");
}
