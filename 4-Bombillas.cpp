#include <iostream>
#include <vector>
#include "EnterosInf.h"

using namespace std;

typedef struct {
	int costeFin;
	int potFin;
}tSolucion;

tSolucion resuelveIluminacion(int minPot, int maxPot, vector<int> pB, vector<int> cB) {
	tSolucion sol;
	vector<int> reconst = vector<int>(maxPot + 1, EntInf::_intInf);
	reconst[0] = 0;
	for (int j = 1; j < pB.size(); j++) {
		for (int i = 1; i <= maxPot; i++) {
			if(i >= pB[j])
				reconst[i] = min(reconst[i], reconst[i - pB[j]] + cB[j]);
		}
	}
	sol.costeFin = EntInf::_intInf;
	sol.potFin = -1;

	for (int i = minPot; i < maxPot + 1; i++) {
		if (sol.costeFin > reconst[i]) {
			sol.costeFin = reconst[i];
			sol.potFin = i;
		}
	}

	return sol;
}

bool resuelve() {
	int minPot, maxPot, bombillas;
	cin >> bombillas >> maxPot >> minPot;
	if (!cin) return false;

	vector<int> potBombillas = vector<int>(bombillas + 1, 0);
	vector<int> costBombillas = vector<int>(bombillas + 1, 0);

	for (int i = 1; i < bombillas + 1; i++) {
		cin >> potBombillas[i];
	}

	for (int i = 1; i < bombillas + 1; i++) {
		cin >> costBombillas[i];
	}

	tSolucion sol = resuelveIluminacion(minPot, maxPot, potBombillas, costBombillas);

	if (sol.potFin != -1) {
		cout << sol.costeFin << " " << sol.potFin << endl;
	}
	else {
		cout << "IMPOSIBLE\n";
	}

	return true;
}

int main() {
	while (resuelve());
	return 0;
}