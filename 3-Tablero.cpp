#include <iostream>
#include <vector>
#include "Matriz.h"

using namespace std;

typedef struct {
	int valor;
	int casilla;
}tSolucion;

tSolucion resuelveCaso(int N, Matriz<int> m) {
	tSolucion sol;
	sol.casilla = 0;
	sol.valor = 0;

	Matriz<int> tablero = Matriz<int>(N, N, -1);

	for (int j = 0; j < N; j++) {
		tablero[0][j] = m[0][j];
	}

	for (int i = 1; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (j == 0)
				tablero[i][j] = max(tablero[i - 1][j], tablero[i - 1][j + 1]) + m[i][j];
			else if (j == N - 1)
				tablero[i][j] = max(tablero[i - 1][j - 1], tablero[i - 1][j]) + m[i][j];
			else
				tablero[i][j] = max(tablero[i - 1][j - 1], max(tablero[i - 1][j], tablero[i - 1][j + 1])) + m[i][j];
		}
	}

	sol.casilla = 0;
	for (int j = 0; j < N; j++) {
		if (tablero[N - 1][j] > sol.valor) {
			sol.valor = tablero[N - 1][j];
			sol.casilla = j;
		}
	}

	return sol;
}

bool resuelve() {
	int N;
	cin >> N;
	if (!std::cin) return false;
	Matriz<int> m = Matriz<int>(N, N, -1);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> m[i][j];
		}
	}

	tSolucion sol = resuelveCaso(N, m);

	cout << sol.valor << " " << sol.casilla + 1 << endl;
	return true;
}

int main() {
	while (resuelve());

	return 0;
}