/*
    Para la implementación de la representación del grafo
    se han utilizado las estructuras de datos "Diccionario
    Hash" y "lista" proporcionados por los profesores de la
    asignatura Estructuras de Datos como base para la imple-
    mentación de este grafo.

    El grafo se representa mediante listas de adyacencia, de
    modo que:

    [nodo] -> [nodo, peso] -> ... ->

    Los nodos y el peso deben de ser de tipo entero.
*/
#include "grafo.h"
#include <iostream>
using namespace std;

int main(){
    unsigned int opcion;
    Grafo<int> g;

    cout << "1. Insertar nodo" << endl;;
    cout << "2. Insertar arista" << endl;
    cout << "3. Representar grafo" << endl;
    cout << "4. Salir" << endl << endl;

    do{
        cout << "Seleccione opción: " << endl;
        cin >> opcion;

        if(opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4) cout << "Opción no válida" << endl;
        else{
            string dummy;

            switch(opcion){
                case 1 :
                    int v;
                    cout << "Pon un valor al nodo: " << endl;
                    cin >> v;
                    try{
                        g.creaNodo(v);
                        g.representa();
                        cout << endl;
                        cout << "----------------------------------" << endl;
                    }
                    catch(ENodoExistente){
                        cout << "El nodo ya existe" << endl;
                        cout << "----------------------------------" << endl;
                    }
                    break;

                case 2 : 
                    if(g.numNodos() >= 2){
                        int v1,v2, peso;

                        cout << "Elige dos nodos existentes y asígnales un peso separados por un espacio: " << endl;
                        cout << "Formato: N1 N2 PESO" << endl;
                        cin >> v1 >> v2 >> peso;

                        try{
                            g.uneNodos(v1, v2, peso);
                            g.representa();
                            cout << endl;
                            cout << "----------------------------------" << endl;
                        }
                        catch(ENodoNoExiste){
                            cout << "Algún nodo no existe" << endl;
                            cout << "----------------------------------" << endl;
                        }
                    }
                    else{
                        cout << "Necesitas al menos 2 nodos." << endl;
                        cout << "----------------------------------" << endl;
                    }
                    break;

                case 3 : 
                    try{
                        g.representa();
                        cout << endl;
                        cout << "----------------------------------" << endl;
                    }
                    catch(EGrafoVacio){
                        cout << "El grafo está vacío" << endl;
                        cout << "----------------------------------" << endl;
                    }
                    break;

                case 4 : break;
                default : cout << "Error!" << endl; break;
            }
            
        }

    }while(opcion != 4);

    return 0;
}