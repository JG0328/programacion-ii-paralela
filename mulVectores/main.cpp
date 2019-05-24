#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    int tam;
    cout << "Digite el tamano de los vectores: " << endl;
    cin >> tam;

    long vec1[tam];
    long vec2[tam];

    for(int i = 0; i < tam; i++)
    {
        vec1[i] = i + 1;
        vec2[i] = (i + 1) * 10;
    }

    long total = 0;

    for(int i = 0; i < tam; i++)
    {
        total += vec1[i] * vec2[i];
    }

    cout << "Resultado: " << total << endl;

    return 0;
}
