#include <iostream>
#include <cstdlib>

using namespace std;

const int SIZE = 5; // tamaño del tablero

bool esSeguro(int tablero[SIZE][SIZE], int fila, int columna) {
    // Verificar si la fila está segura
    for (int i = 0; i < columna; i++) {
        if (tablero[fila][i]) {
            return false;
        }
    }
    
    // Verificar la diagonal superior izquierda
    for (int i = fila, j = columna; i >= 0 && j >= 0; i--, j--) {
        if (tablero[i][j]) {
            return false;
        }
    }
    
    // Verificar la diagonal inferior izquierda
    for (int i = fila, j = columna; i < SIZE && j >= 0; i++, j--) {
        if (tablero[i][j]) {
            return false;
        }
    }
    
    // La posición es segura
    return true;
}

void imprimirTablero(int tablero[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << tablero[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void colocarReinas() {
    int soluciones = 0;
    int tablero[SIZE][SIZE] = {0};
    
    for (int a = 0; a < SIZE; a++) {
        for (int b = 0; b < SIZE; b++) {
            if (!esSeguro(tablero, a, 0)) {
                continue;
            }
            tablero[a][0] = 1;
            for (int c = 0; c < SIZE; c++) {
                if (!esSeguro(tablero, c, 1)) {
                    continue;
                }
                tablero[c][1] = 1;
                for (int d = 0; d < SIZE; d++) {
                    if (!esSeguro(tablero, d, 2)) {
                        continue;
                    }
                    tablero[d][2] = 1;
                    for (int e = 0; e < SIZE; e++) {
                        if (!esSeguro(tablero, e, 3)) {
                            continue;
                        }
                        tablero[e][3] = 1;
                        for (int f = 0; f < SIZE; f++) {
                            if (!esSeguro(tablero, f, 4)) {
                                continue;
                            }
                            tablero[f][4] = 1;
                            soluciones++;
                            cout << "Solución #" << soluciones << endl;
                            imprimirTablero(tablero);
                            tablero[f][4] = 0;
                        }
                        tablero[e][3] = 0;
                    }
                    tablero[d][2] = 0;
                }
                tablero[c][1] = 0;
            }
            tablero[a][0] = 0;
        }
    }
}

int main() {
    colocarReinas();
    return 0;
}