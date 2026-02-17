#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int main(void)
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
  int sz;
  while(cin >> sz)
  {
    vector<string> grid(sz);
    for(int i=0; i<sz; ++i)
      cin >> grid[i];
    // Find two lines with the same list of letters. This is 
    // the list of letters of the Latin square.
    set<string> lineSet;
    string letterList;
    for(int i=0; i<3; ++i)
    {
      string lTmp = grid[i];
      sort(lTmp.begin(), lTmp.end());
      if(lineSet.find(lTmp) != lineSet.end())
        letterList = lTmp;
      lineSet.insert(lTmp);
    }

    int foundR = -1;
    int foundC = -1;
    for(int r=0; r<sz; ++r)
    {
      for(int c1=0; c1<sz; ++c1)
      {
        
        char curCh = grid[r][c1];        
        for(int c2=0; c2<c1; ++c2)        
          if(foundR == -1 && curCh == grid[r][c2])
          {
            foundR = r;
            for(int rx=0; rx<sz; ++rx)
              if(rx!=r && grid[rx][c1] == curCh)
                foundC = c1;
            if(foundC == -1)
              foundC = c2;
          }
        // If the current letter is not in the list of letters of the Latin square,
        // then this is the error position.
        if(letterList.find(curCh) == string::npos)
        {
          foundR = r;
          foundC = c1;
        }
      }
    }

    // The correct letter for the error position is the one from the letter list
    // that does not occur in the line with the error position.
    for(char ch : letterList)
      if(grid[foundR].find(ch) == string::npos)
        cout << foundR+1 << " " << foundC+1 << " " << ch << endl;
  }
  return 0;
}
