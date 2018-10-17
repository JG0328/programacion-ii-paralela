#include <iostream>

#define PRECISION 10000

using namespace std;

int main()
{
    double sum = 0.0;
    double h = 1.0 / (double) PRECISION;

    for(int i = 1; i <= PRECISION; i++)
    {
        double x = h * ((double)i - 0.5);
        sum += (4.0 / (1.0 + x*x));
    }

    double pi = sum * h;

    cout << "PI:" << pi << endl;

    return 0;
}
