#include <iostream>

using namespace std;

typedef long long ll;
/* Calculate ( a*b ) %c */
ll mulmod(ll a,ll b,ll c)
{
    ll x = 0 , y = a%c ;
    while(b>0)
    {
        if(b%2) x = (x+y)%c ;
        y=(y*2)%c;
        b/=2;
    }
    return x%c ;
}

/* Calculate ( a^b ) %c */
ll modulo(ll a,ll b,ll c)
{
    ll x = 1 , y = a%c ;
    while( b > 0 )
    {
        if(b%2) x = mulmod(x,y,c) ;
        y=mulmod(y,y,c);
        b/=2;
    }
    return x%c ;
}

bool isPrime(ll p, ll iteration = 50)
{
    if(p<2) return false ;
    if(p%2==0&&p!=2) return false ;
    if (p <= 3) return true;

    ll s = p-1 ;
    while(s%2==0) s/=2;

    for(ll i=1;i<=iteration;i++)
    {
        ll a = rand() % (p-1)+1 , temp = s ;

        ll mod = modulo(a,temp,p);
        while(mod!=1&&mod!=p-1&&temp!=p-1)
        {
            mod = mulmod(mod,mod,p);
            temp*=2;
        }
        if(temp%2==0&&mod!=p-1) return false ;
    }
    return true ;
}

int main() {
	srand(time(NULL));
    
    ll a, b;
    cin >> a >> b;
    if (!isPrime(a) || !isPrime(b)) {
    	cout << -1 << endl;
    	return 0;
    }
    if (isPrime(a - b) || isPrime(b - a)) {
    	cout << 2 << endl << a << " " << b << endl;
    	return 0;
    }

    if (a % 2 == 1 && b % 2 == 1) {
    	if (a == b && isPrime(a - 2)) {
    		cout << 3 << endl << a << " " << a - 2 << " " << a << endl;
    	} else if (a == b && isPrime(a + 2)) {
    		cout << 3 << endl << a << " " << a + 2 << " " << a << endl;
    	} else if (isPrime(a - 2) && isPrime(b - 2)) {
    		cout << 3 << endl << a << " 2 " << b << endl;
    	} else if (a == 3 && b == 7) {
    		cout << 3 << endl << "3 5 7" << endl;
    	} else if (a == 7 && b == 3) {
    		cout << 3 << endl << "7 5 3" << endl;
    	} else {
    		cout << -1 << endl;
    	}
    	return 0;
    }

    if (a == 2 && b == 2) {
    	cout << 3 << endl << "2 5 2" << endl;
    	return 0;
    } else if (a == 2) {
    	if (isPrime(b + 2)) {
    		cout << 3 << endl << "2 " << b + 2 << " " << b << endl;
    	} else {
    		cout << -1 << endl;
    	}
    	return 0;
    } else if (b == 2) {
    	if (isPrime(a + 2)) {
    		cout << 3 << endl << a << " " << a + 2 << " 2" << endl;
    	} else {
    		cout << -1 << endl;
    	}
    	return 0;
    }
    cout << -1 << endl;
    return 0;
}
