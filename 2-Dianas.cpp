#include <iostream>
#include <vector>
#include "EnteroInf.h"

using namespace std;

typedef struct {
	int nDardos;
	vector<int> puntuados;
}tSolucion;

vector<int> reconstruye(vector<int> reconst, int puntos, vector<int>sectores) {
	vector<int> sol;
	if (reconst[puntos] != EntInf::_intInf) {
		int i = puntos, j = sectores.size();
		while (i > 0) {
			if (sectores[j - 1] <= i && reconst[i] == reconst[i - sectores[j]] + 1) {
				sol.push_back(sectores[j - 1]);
				i = i - sectores[j - 1];
			}
			else {
				j--;
			}
		}
	}
	return sol;
}

tSolucion resuelveDiana(int puntos, vector<int> sectores) {
	tSolucion sol;
	vector<int> reconst = vector<int>(puntos + 1, EntInf::_intInf);
	reconst[0] = 0;
	for (int j = 1; j <= sectores.size(); j++) {
		for (int i = 1; i <= puntos; i++) {
				reconst[i] = min(reconst[i], reconst[i - sectores[j - 1]] + 1);
		}
	}
	
	sol.nDardos = reconst[puntos];
	sol.puntuados = reconstruye(reconst, puntos, sectores);

	return sol;
}

bool resuelve() {
	int puntos, nSectores;
	cin >> puntos >> nSectores;
	if (!cin) return false;

	vector<int> sectores = vector<int>(nSectores, -1);

	for (int i = 0; i < nSectores; i++) {
		cin >> sectores[i];
	}

	tSolucion sol = resuelveDiana(puntos, sectores);

	if (sol.nDardos != EntInf::_intInf) {
		cout << sol.nDardos << ":";
		for (int i = 0; i < sol.puntuados.size(); i++) {
			cout << " " << sol.puntuados[i];
		}
		cout << endl;
	}
	else {
		cout << "Imposible\n";
	}

	return true;
}

int main() {
	while (resuelve());
	return 0;
}