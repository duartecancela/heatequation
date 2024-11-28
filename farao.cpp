#include <iostream>
#include <omp.h>
#include <cmath>
#include "farao.h"

int main (int argc, char *argv[]) {
    std::cout << "farao" << std::endl;

    int N = 8;
    double b = 1.0;
    double a = 0.0;

    double area = soma_integral(f, a, b, N);
    std::cout << "area = " << area << std::endl;

    // Inicia a simulação de difusão de calor
    heat_diffusion_2d();

    return 0;
}

