#include <iostream>
#include <stdlib.h>

using namespace std;

int tamano_memoria = 3.;

struct Pagina {
    int numero;
    int tiempo;
};

int main() {
    int v = 0, w = 0;
    float porcentPD = 0, porcentPH = 0, total = 0;

    /*cout << "Ingrese el tamano de la memoria fisica (frames): ";
    cin >> tamano_memoria;
*/

    int cantidad_paginas=15;
    /*cout << "Ingrese la cantidad de paginas en la secuencia (cantidad de elementos a insertar): ";
    cin >> cantidad_paginas;
*/

    int secuencia_paginas[cantidad_paginas]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2};
    int memoria_fisica[tamano_memoria];


    for (int i = 0; i < tamano_memoria; i++) {
        memoria_fisica[i] = -1;
    }

    system("cls");

   cout << "Ingrese la secuencia de paginas:" << endl;
    for (int i = 0; i < cantidad_paginas; i++) {
        cout << secuencia_paginas[i]<<" ";
    }
    
    cout<<"\n";

    int fallos_pagina = 0;
    int page_hits = 0;

    Pagina paginas_en_memoria[tamano_memoria];

    for (int i = 0; i < cantidad_paginas; i++) {
        int pagina = secuencia_paginas[i];

        bool found = false;
        for (int j = 0; j < tamano_memoria; j++) {
            if (memoria_fisica[j] == pagina) {
                found = true;
                paginas_en_memoria[j].tiempo = i;
                break;
            }
        }

        if (!found) {
            fallos_pagina++;
            total++;
            if (i < tamano_memoria) {
                
                memoria_fisica[i] = pagina;
            } else {
                
                int indice_pagina_lru = 0;
                int tiempo_lru = paginas_en_memoria[0].tiempo;
                for (int j = 1; j < tamano_memoria; j++) {
                    if (paginas_en_memoria[j].tiempo < tiempo_lru) {
                        tiempo_lru = paginas_en_memoria[j].tiempo;
                        indice_pagina_lru = j;
                    }
                }
                memoria_fisica[indice_pagina_lru] = pagina;
                paginas_en_memoria[indice_pagina_lru].numero = pagina;
                paginas_en_memoria[indice_pagina_lru].tiempo = i;
            }
        } else {
            page_hits++;
            total++;
        }

        cout << "Estado de la memoria fisica: ";
        for (int j = 0; j < tamano_memoria; j++) {
            cout << memoria_fisica[j] << " ";
        }
        cout << endl;
    }

    v = fallos_pagina;
    w = page_hits;

    porcentPD = (v / total) * 100;
    porcentPH = (w / total) * 100;
    cout << "Page Default: " << porcentPD << "%" << endl;
    cout << "Page Hits: " << porcentPH << "%" << endl;

    return 0;
}

