#include <iostream>

long long gcd(long long a, long long b) {
    return a == 0 || b == 0 ? a + b : gcd(b % a, a);
}

int main() {

    long long a, b;
    std::cin >> a >> b;

    long long lcm = a * b / gcd(a, b);
    long long res = lcm - a - b;
    std::cout << (res < 0 ? res + lcm : res) << '\n';

}