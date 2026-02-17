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

const int minN = 2, maxN = 100000;

int n, k;
vector <int> a (n), b (n);
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

bool checkAns (ifstream &in) {
  int t;
  in>>t;
  if(t<0 && t>n){
	  wa("Таны гаргасан бөхийн дугаар буруу!");
  }
  t = t - 1;
  if (t == -1) {
    return false;
  } else {
    vector <bool> is (n, false);
    is[t] = true;
    for (int i = 1; i < k; ++i) {
	  in>>t;
	  if(t<1 && t>n) wa("Таны гаргасан бөхийн дугаар буруу!");
      t = t - 1;
      if (is[t]) {
        wa(to_string(t + 1)+" бөхийн дугаар 2 удаа гарсан!");
      }
      is[t] = true;
    }
    for (int i = 0; i < n; ++i) {
      if (is[a[i]] && is[b[i]]) {
        wa(to_string(1 + a[i])+" ба "+to_string(1 + b[i])+" хоёр бөх аль хэдийнэ барилдсан байна!");
      }
    }
    return true;
  }
}

int main(int argc, char* argv[]) {
    ifstream inf(argv[1]), ouf(argv[2]), ans(argv[3]);
  inf>>n;
  a.resize (n);
  b.resize (n);
  for (int i = 0; i < n; ++i) {
	  inf>>a[i]>>b[i];
    a[i] = a[i] - 1;
    b[i] = b[i] - 1;
  }
  inf>>k;
  bool ja = checkAns (ans);

  bool pa = checkAns (ouf);
  if (ja) {
    if (pa) {
      ac("Таны хариу зөв байна.");
    } else {
      wa("Таны хариу буруу!");
    }
  } else {
    if (pa) {
      wa("Таны хариу буруу!");
    } else {
      ac("Таны хариулт зөв байна.");
    }
  }
  return 0;
}
