#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <set>
#include <map>

using namespace std;

int INFTY = 10e6;

int n,M;
vector<int> B;
vector<int> C;

bool distanciados(const vector<int> &v) {
    if (v.empty()) return false; 
    if (v.size() == 1) return true;
    bool cumple = true;
    for (int i = 0; i < v.size() - 2; i ++) {
        if (v[i] + 1 == v[i + 1]) cumple = false;
    }
    return cumple;
}

int FB(int i, int b, int c, vector<int> indices) {
    // Caso base.
    if (i == n) return c <= M && distanciados(indices) ? b : -INFTY;
    // Recursión.
    int no_agrego = FB(i+1, b, c,indices);
    indices.push_back(i);
    int agrego = FB(i+1, b + B[i], c + C[i],indices);
    return max(no_agrego, agrego);
}

bool poda_factibilidad = true; // define si la poda por factibilidad esta habilitada.
bool poda_optimalidad = true; // define si la poda por optimalidad esta habilitada.
int Bmax = 0;
int Brem = 0;


int BT(int i, int b, int c, int Brem){
	// Caso base.
    if (i >= n){
    	if (c <= M ){
            Bmax = max(Bmax,b);
            return Bmax;
        }else{
            return -INFTY;
        }
    }
    
    // Poda por factibilidad.
    if (poda_factibilidad && c > M) return -INFTY;

    // Poda por optimalidad.
    if (poda_optimalidad && b + Brem <= Bmax) return -INFTY;

    // Recursión.
    //caso borde 
    int sumaAux;
    if(i == n-1){
        sumaAux = 0;
    }else{
        sumaAux = B[i+1];
    }
    int no_agrego = BT(i+1,b, c, Brem - B[i]); 
    int agrego = BT(i+2, b+B[i],  c + C[i],Brem - B[i] - sumaAux);
    return max(no_agrego, agrego);
}

vector<vector<int>> Mat; // Memoria de DP.
const int UNDEFINED = -1;

int DP(int i, int m) {
	if (m < 0) return -INFTY;
	if (Mat[i][m] == UNDEFINED) {
        if (i >= n) {
            Mat[i][m] = 0;
        } else {
            Mat[i][m] = max(DP(i + 2, m - C[i]) + B[i],DP(i + 1, m));
        }
    }
	return Mat[i][m];
}



int main(int argc, char** argv) {
	// Leemos el parametro que indica el algoritmo a ejecutar.
	map<string, string> algoritmos_implementados = {
		{"FB", "Fuerza Bruta"}, {"BT", "Backtracking con podas"}, {"BT-F", "Backtracking con poda por factibilidad"}, 
		{"BT-O", "Backtracking con poda por optimalidad"}, {"DP", "Programacion dinámica"}
	};

	// Verificar que el algoritmo pedido exista.
	if (argc < 2 || algoritmos_implementados.find(argv[1]) == algoritmos_implementados.end()) {
		cerr << "Algoritmo no encontrado: " << argv[1] << endl;
		cerr << "Los algoritmos existentes son: " << endl;
		for (auto& alg_desc: algoritmos_implementados) cerr << "\t- " << alg_desc.first << ": " << alg_desc.second << endl;
		return 0;
	}
	string algoritmo = argv[1];

    // Leemos el input.
    cin >> n >> M;
    B.assign(n, 0);
    C.assign(n, 0);
    for (int i = 0; i < n; ++i) cin >> B[i] >> C[i];

    // Ejecutamos el algoritmo y obtenemos su tiempo de ejecución.
	int optimum;
	optimum = INFTY;
	auto start = chrono::steady_clock::now();
	if (algoritmo == "FB"){
		optimum = FB(0, 0, 0, {});
	} else if (algoritmo == "BT") {     
        for(int i = 0; i<n; i++){
            Brem += B[i];
        }
		poda_optimalidad = poda_factibilidad = true;
		optimum = BT(0, 0, 0, Brem);
	} else if (algoritmo == "BT-F") {
		poda_optimalidad = false;
		poda_factibilidad = true;
		optimum = BT(0, 0, 0,Brem);
	} else if (algoritmo == "BT-O") {
        for(int i = 0; i<n; i++){
            Brem += B[i];
        }
		poda_optimalidad = true;
		poda_factibilidad = false;
		optimum = BT(0, 0, 0,Brem);
		
	} else if (algoritmo == "DP") {
		// Inicializamos la matriz.
		Mat = vector<vector<int>>(n+2, vector<int>(M+1, UNDEFINED));
		// Obtenemos la solucion optima.
		optimum = DP(0, M);
	}
	auto end = chrono::steady_clock::now();
	double total_time = chrono::duration<double, milli>(end - start).count();

	// Imprimimos el tiempo de ejecución por stderr.
	clog << total_time << endl;

    // Imprimimos el resultado por stdout.
    cout << (optimum == INFTY ? -1 : optimum) << endl;
    return 0;
}


