#include <iostream>
#include <vector>
#include "Matriz.h"

using namespace std;

typedef struct {
	int p;
	int m;
}tCofre;

typedef struct {
	int monedas;
	int cofres;
	vector<tCofre> listaCofres;
}tSolucion;

tSolucion cazatesoros(int T, int n, vector<tCofre> cofres) {
	tSolucion sol;
	Matriz<int> mat = Matriz<int>(n + 1, T + 1, -1);

	for (int i = 0; i <= n; i++) {
		mat[i][0] = 0;
	}
	for (int j = 0; j <= T; j++) {
		mat[0][j] = 0;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= T; j++) {
			if (j >= (3 * cofres[i].p)) {
				mat[i][j] = max(mat[i - 1][j], mat[i - 1][j - (3 * cofres[i].p)] + cofres[i].m);
			}
			else mat[i][j] = mat[i - 1][j];
		}
	}

	sol.monedas = mat[n][T];
	sol.cofres = 0;
	int i = n, j = T;
	tCofre auxCofre;
	auxCofre.p = 0;
	auxCofre.m = 0;
	while(i > 0 && j > 0) {
		if (mat[i-1][j] != mat[i][j]) {
			sol.cofres++;
			sol.listaCofres.push_back(cofres[i]);
			j -= (cofres[i].p * 3);
		}
		i--;
	}
	return sol;
}

bool resuelve() {
	int T, n;
	cin >> T >> n;
	if (!std::cin) return false;

	tCofre c;
	c.p = 0;
	c.m = 0;
	vector<tCofre> cofres = vector<tCofre>(n + 1, c);
	for (int i = 1; i <= n; i++) {
		cin >> cofres[i].p >> cofres[i].m;
	}

	tSolucion sol = cazatesoros(T, n, cofres);

	cout << sol.monedas << endl << sol.cofres << endl;

	for (int i = sol.cofres - 1; i >= 0; i--) {
		cout << sol.listaCofres[i].p << " " << sol.listaCofres[i].m << endl;
	}
	cout << "---\n";

	return true;
}

int main() {
	while (resuelve());
	return 0;
}