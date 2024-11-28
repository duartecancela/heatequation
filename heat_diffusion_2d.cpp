#include <iostream>
#include <fstream>
#include <cmath>
#include "farao.h"

void heat_diffusion_2d() {
    double alfa_gold = 127; // Difusividade térmica (mm²/ms)

    int M = 100; // Dimensão X da placa (mm)
    int N = 100; // Dimensão Y da placa (mm)

    // Alocação de memória para as temperaturas da placa
    double** A = new double*[M];
    double** B = new double*[M];
    for (int m = 0; m < M; m++) {
        A[m] = new double[N];
        B[m] = new double[N];
    }

    double T0 = 25.0; // Temperatura inicial (°C)
    double Tb = 100.0; // Temperatura nas bordas (°C)

    // Inicialização: Condições internas e de contorno
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            A[m][n] = T0;
            B[m][n] = T0;
        }
    }

    for (int m = 0; m < M; m++) {
        A[m][0] = B[m][0] = Tb;
        A[m][N - 1] = B[m][N - 1] = Tb;
    }
    for (int n = 0; n < N; n++) {
        A[0][n] = B[0][n] = Tb;
        A[M - 1][n] = B[M - 1][n] = Tb;
    }

    // Evolução temporal
    double t = 0.0;
    double final_time = 30000.0; // 30 segundos em milissegundos
    double dt = 1.0; // Passo de tempo (ms)

    while (t < final_time) {
        for (int m = 1; m < M - 1; m++) {
            for (int n = 1; n < N - 1; n++) {
                double a0 = A[m][n]; // Centro
                double aW = A[m + 1][n]; // Oeste
                double aE = A[m - 1][n]; // Leste
                double aN = A[m][n + 1]; // Norte
                double aS = A[m][n - 1]; // Sul

                B[m][n] = a0 + (aW + aE + aN + aS - 4.0 * a0) / alfa_gold;
            }
        }

        // Atualiza A com os novos valores
        for (int m = 1; m < M - 1; m++) {
            for (int n = 1; n < N - 1; n++) {
                A[m][n] = B[m][n];
            }
        }

        t += dt;
    }

    // Salva os resultados
    std::ofstream out_file("simul30seg");
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            out_file << m << ' ' << n << ' ' << A[m][n] << std::endl;
        }
        out_file << std::endl;
    }
    out_file.close();

    // Libera memória
    for (int m = 0; m < M; m++) {
        delete[] A[m];
        delete[] B[m];
    }
    delete[] A;
    delete[] B;
}

