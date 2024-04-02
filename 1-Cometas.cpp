#include <iostream>
#include <fstream>
#include <vector>
#include "EnterosInf.h"
#include "Matriz.h"

using namespace std;

typedef struct {
	bool posible;
	long long int nPosibles;
	EntInf minCuerdas;
	EntInf minCoste;
}tSolucion;

typedef struct {
	int l; //Longitud de la cuerda
	int c; //Coste de la cuerda
}tCuerda;

//Para resolver el ejercicio he seguido el esquema del problema de la mochila solo que trabajé con minización en vez de maximización ya que quiero mínimos
// costes y mínimas cuerdas en vez de máximo número de objetos o máximo peso


//Para obtener todas las veces que se pueda formar la cuerda con los fragmentos dados tengo:
//nudos[j] = número de combinaciones que se pueden hacer con las cuerdas para formar una sola de longitud j
// 
//CASO BASE:
//
//nudos[0] = 1; Ya que siempre formré una cuerda de 0 nudos, una vez llego a 0 es que he podido formar la cuerda
//nudos[j] = 0 cuando i == 0 ya que significará que no hay ninguna cuerda más por lo que no se podrá completar si aún queda longitud por conseguir
//
//CASO RECURSIVO:
//
//nudos[j] = nudos[j] + nudos[j - cuerdas[i.l] si la longitud de la cuerda es menor de lo que queda de longitud por formar se suman los nudos hasta 
//ahora con los nudos que se formarían si añadiese la cuerda.
//Si la cuerda es mayor entonces se mantendrá como nudos[j] = nudos[j] ya que no podré añadir cuerda
long long int contPosibles(const vector<tCuerda>& cuerdas, int longitud, vector<long long int>& nudos) {
	for (int i = 0; i < cuerdas.size(); i++) {
		for (int j = longitud; j >= cuerdas[i].l; j--) {
			if (j == 0) {
				nudos[j] = 1;
			}
			else if (i == 0) {
				nudos[j] = 0;
			}
			else if (cuerdas[i].l <= j) {
				nudos[j] = nudos[j] + nudos[j - cuerdas[i].l];
			}
		}
	}
	return nudos[longitud];
}

EntInf usarMinCuerdas(const vector<tCuerda>& cuerdas, int longitud, vector<EntInf>& nudos) {
	for (int i = 0; i < cuerdas.size(); i++) {
		for (int j = longitud; j >= cuerdas[i].l; j--) {
			if (j == 0) {
				nudos[j] = 0;
			}
			else if (i == 0) {
				nudos[j] = EntInf::_intInf - 1;
			}
			else if (cuerdas[i].l <= j) {
				nudos[j] = min(nudos[j], nudos[j - cuerdas[i].l] + 1);
			}
		}
	}
	return nudos[longitud];
}

EntInf usarMinCoste(const vector<tCuerda>& cuerdas, int longitud, vector<EntInf>& nudos) {
	for(int i = 0; i < cuerdas.size(); i++) {
		for (int j = longitud; j >= cuerdas[i].l; j--) {
			if (j == 0) {
				nudos[j] = 0;
			}
			else if (i == 0) {
				nudos[j] = EntInf::_intInf - 1;
			}
			else if (cuerdas[i].l <= j) {
				nudos[j] = min(nudos[j], nudos[j - cuerdas[i].l] + cuerdas[i].c);
			}
		}
	}
	return nudos[longitud];
}

tSolucion resolver(const int& longitud, const vector<tCuerda>& cuerdas) {
	tSolucion sol;
	vector<long long int> nudosInt = vector<long long int>(longitud + 1, -1);
	vector<EntInf> nudos = vector<EntInf>(longitud + 1, EntInf::_intInf);
	vector<EntInf> nudos2 = vector<EntInf>(longitud + 1, EntInf::_intInf);
	sol.nPosibles = contPosibles(cuerdas, longitud, nudosInt);
	sol.posible = sol.nPosibles > 0;
	if (sol.posible) {
		sol.minCuerdas = usarMinCuerdas(cuerdas, longitud, nudos);
		sol.minCoste = usarMinCoste(cuerdas, longitud, nudos2);
	}
	return sol;
}

bool resuelve() {
	int nCuerdas, longitud;
	cin >> nCuerdas >> longitud;
	if (!cin) return false;

	vector<tCuerda> cuerdas = vector<tCuerda>(nCuerdas + 1);
	for (int i = 1; i < nCuerdas + 1; i++)
		cin >> cuerdas[i].l >> cuerdas[i].c;

	tSolucion sol = resolver(longitud, cuerdas);

	if (sol.posible)
		cout << "SI " << sol.nPosibles << " " << sol.minCuerdas << " " << sol.minCoste << endl;
	else
		cout << "NO\n";

	return true;
}

int main() {
	while (resuelve());
	return 0;
}
