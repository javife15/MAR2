#include <iostream>
#include <string>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;

typedef struct {
	int letras;
	vector<char> palindromo;
}tSolucion;

tSolucion aibofobia(string p) {
	tSolucion sol;
	int n = p.length();

	Matriz<int> mat = Matriz<int>(n, n, EntInf::_intInf);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			mat[i][j] = 0;
		}
	}

	for (int i = n - 1; i >= 0; i--) {
		for (int j = i; j < n; j++) {
			if (i < j) {
				if (p[i] != p[j] && i == n - 1) {
					mat[i][j] = mat[i][j - 1];
				}
				else if (p[i] != p[j] && j == 0) {
					mat[i][j] = mat[i + 1][j];
				}
				else if (p[i] != p[j]) {
					mat[i][j] = min(mat[i + 1][j] + 1, mat[i][j - 1] + 1);
				}
				else mat[i][j] = mat[i + 1][j - 1];

			}
		}
	}

	sol.letras = mat[0][n - 1];
	int i = 0, j = n - 1;
	int k = 0, l = p.length() + sol.letras;
	sol.palindromo = vector<char>(l, ' ');
	l--;
	while (i <= j) {
		if (p[i] == p[j]) {
			sol.palindromo[k] = p[i];
			sol.palindromo[l] = p[j];
			i++;
			j--;
		}
		else {
			if (mat[i + 1][j] < mat[i][j - 1]) {
				sol.palindromo[k] = p[i];
				sol.palindromo[l] = p[i];
				i++;
			}
			else {
				sol.palindromo[k] = p[j];
				sol.palindromo[l] = p[j];
				j--;
			}
		}
		k++;
		l--;
	}

	return sol;
}

bool resuelve() {
	string palabra;
	cin >> palabra;
	if (!std::cin) return false;

	tSolucion sol = aibofobia(palabra);

	cout << sol.letras << " ";
	for(int i = 0; i < sol.palindromo.size(); i++)
		cout << sol.palindromo[i];
	cout << endl;

	return true;
}

int main() {
	while (resuelve());
	return 0;
}