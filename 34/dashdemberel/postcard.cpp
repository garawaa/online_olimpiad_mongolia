    #include <iostream>
    #include <cmath>
     
    using namespace std;
     
    double pi = 2*acos(0.0);
    int h,w,H,W;
    void input()
    {
        cin>>h>>w;
        cin>>H>>W;
    }
    double Fabs(double a)
    {
        if (a<0)
            return -a;
        return a;
    }
    double eps = 1e-9;
    bool Equal(double a, double b)
    {
        return Fabs(a-b) <= eps;
    }
    bool LessEqual(double a, double b)
    {
        return a<b || Equal(a,b);
    }
    bool isInside(int w, int h, int W, int H)
    {
        if (h>w) swap(h,w);
        if (H>W) swap(H,W);
        // ??????????? ??????
        if (h<=H && w<=W)
            return true;
        else // ??? ?????
        {
            double beta = acos((double)H / sqrt((double)(h*h + w*w)));
            double phi  = acos((double)W / sqrt((double)(h*h + w*w)));
     
            double alpha = 2* atan((double)h/(double)w);
            double Alpha = pi/2 - beta - phi;
            return LessEqual(alpha,Alpha);
        }
    }
    void solve()
    {
        if (isInside(w,h,W,H))
            cout<<"Possible";
        else
            cout<<"Impossible";
    }
    int main()
    {
        input();
        solve();
        return 0;
    }
