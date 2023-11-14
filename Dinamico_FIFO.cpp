#include <iostream>
#include <stdlib.h>

using namespace std;

int tamano_memoria = 3;

struct ColaPaginas {
    int* elementos;
    int inicio;
    int fin;
    int cantidad;

    ColaPaginas() {
        elementos = new int[tamano_memoria];
        inicio = 0;
        fin = -1;
        cantidad = 0;
    }

    ~ColaPaginas() {
        delete[] elementos;
    }

    void enqueue(int pagina) {
        if (cantidad < tamano_memoria) {
            fin = (fin + 1) % tamano_memoria;
            elementos[fin] = pagina;
            cantidad++;
        } else {
            cout << "La cola esta llena, no se puede encolar mas elementos." << endl;
        }
    }

    int dequeue() {
        if (cantidad > 0) {
            int pagina = elementos[inicio];
            inicio = (inicio + 1) % tamano_memoria;
            cantidad--;
            return pagina;
        } else {
            cout << "La cola esta vacia, no se puede desencolar." << endl;
            return -1;
        }
    }

    bool estaVacia() {
        return cantidad == 0;
    }
};

bool paginaEnMemoria(ColaPaginas &cola, int pagina) {
    for (int i = 0; i < cola.cantidad; i++) {
        if (cola.elementos[(cola.inicio + i) % tamano_memoria] == pagina) {
            return true;
        }
    }
    return false;
}

int main() {
	
	int v=0,w=0;
	float porcentPD=0, porcentPH=0,total=0;
	
    //cout << "Ingrese el tamano de la memoria fisica (frames): ";
   // cin >> tamano_memoria;
    ColaPaginas cola_paginas;
    
 //   int cantidad_paginas;
    //cout << "Ingrese la cantidad de paginas en la secuencia (cantidad de elementos a insertar): ";
  //  int  cantidad_paginas=4;

    int secuencia_paginas[3]={7,1,1};
	
	//secuencia_paginas[3];
	
	system("cls");
	
   /* cout << "Ingrese la secuencia de paginas:" << endl;
    for (int i = 0; i < 3; i++) {
        cin >> secuencia_paginas[i];
    }

*/
    int fallos_pagina = 0;
    int page_hits = 0;

    for (int i = 0; i < tamano_memoria; i++) {
        cola_paginas.enqueue(-1);
    }

    for (int i = 0; i < 3; i++) {
        int pagina = secuencia_paginas[i];

        if (!paginaEnMemoria(cola_paginas, pagina)) {
            int pagina_a_reemplazar = cola_paginas.dequeue();
            cola_paginas.enqueue(pagina);
            fallos_pagina++;
            total++;
        }
        else {
            page_hits++;
			total++; 
        }

        cout << "Estado de la memoria fisica: ";
        for (int j = 0; j < tamano_memoria; j++) {
            cout << cola_paginas.elementos[(cola_paginas.inicio + j) % tamano_memoria] << " ";
        }
        cout << endl;
    }

	v=fallos_pagina;
	w=page_hits;
	
	porcentPD= (v/total)*100;
	porcentPH= (w/total)*100;
    cout << "Page Default: " << porcentPD <<"%" << endl;
    cout << "Page Hits: " << porcentPH <<"%" << endl;

    return 0;
}

