#include "pch.h"
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <omp.h>

#define N 1000
#define chunk 100
#define mostrar 10 


void imprimeArreglo(float *d);

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";
    float a[N], b[N], c[N];
    int i;

    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < N; i++) {
        a[i] = static_cast<float>(rand()) / RAND_MAX * 100; // Random float between 0 and 100
        b[i] = static_cast<float>(rand()) / RAND_MAX * 100; // Random float between 0 and 100
    }
    int pedazos = chunk;

    #pragma omp parallel for \
    shared(a,b,c,pedazos) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++)

        c[i] = a[i] + b[i];

    std::cout << "Imprimiendo los primeros " << mostrar << " Valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " Valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " Valores del arreglo c: " << std::endl;
    imprimeArreglo(c);

}

void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}