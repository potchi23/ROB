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

    cout << "1. Insertar nodo" << endl;
    cout << "2. Insertar arista" << endl;
    cout << "3. Representar grafo" << endl;
    cout << "4. Mostrar todos los caminos de origen a destino" << endl;
    cout << "5. Mostrar el camino más corto de origen a destino" << endl;
    cout << "0. Salir" << endl << endl;


    do{
        cout << "> Seleccione opción: " << endl;
        cin >> opcion;

        
        if(opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4 && opcion != 5 && opcion != 6) cout << "Opción no válida" << endl;
        else{
            string dummy;
            Lista<int> l;
            bool visitado[g.numNodos()];
            int origen, destino;
            
            switch(opcion){
                case 1 :
                    int v;
                    cout << "> INSERTAR NODO: " << endl;
                    cout << "> Pon un valor al nodo: " << endl;
                    cin >> v;
                    try{
                        g.creaNodo(v);
                        g.representa();
                        cout << endl;
                        cout << "----------------------------------" << endl;
                    }
                    catch(ENodoExistente){
                        cout << "> El nodo ya existe" << endl;
                        cout << "----------------------------------" << endl;
                    }
                    break;

                case 2 : 
                    if(g.numNodos() >= 2){
                        int v1,v2, peso;
                        cout << "> INSERTAR ARISTA: " << endl;
                        cout << "> Elige dos nodos existentes y asígnales un peso separados por un espacio: " << endl;
                        cout << "> Formato: N1 N2 PESO" << endl;
                        cin >> v1 >> v2 >> peso;

                        try{
                            g.uneNodos(v1, v2, peso);
                            g.representa();
                            cout << endl;
                            cout << "----------------------------------" << endl;
                        }
                        catch(ENodoNoExiste){
                            cout << "> Algún nodo no existe" << endl;
                            cout << "----------------------------------" << endl;
                        }
                        catch(EAristaExistente){
                            cout << "> Ese arista ya existe" << endl;
                            cout << "----------------------------------" << endl;
                        }
                    }
                    else{
                        cout << "> Necesitas al menos 2 nodos." << endl;
                        cout << "----------------------------------" << endl;
                    }
                    break;

                case 3 : 
                    cout << "> REPRESENTAR GRAFO: " << endl;

                    try{
                        g.representa();
                        cout << endl;
                        cout << "----------------------------------" << endl;
                    }
                    catch(EGrafoVacio){
                        cout << "> El grafo está vacío" << endl;
                        cout << "----------------------------------" << endl;
                    }
                    break;
                case 4:
                    cout << "> BUSCAR TODOS LOS CAMINOS DE ORIGEN A DESTINO: " << endl;
                    cout << "> Introduce origen y destino separados por un espacio:" << endl;
                    cin >> origen >> destino;
                   
                    for(int i = 0; i < g.numNodos(); i++) visitado[i] = false;
                    
                    g.muestraCaminos(origen, destino, l, visitado);
                    cout << "----------------------------------" << endl;
                    break;
                case 5 :
                    cout << "> BUSCAR EL CAMINO MAS CORTO DE ORIGEN A DESTINO: " << endl;
                    cout << "> Introduce origen y destino separados por un espacio:" << endl;
                    cin >> origen >> destino;

                    g.dijkstra(origen, destino);
                    cout << "----------------------------------" << endl;
                    break;
                case 0: break;
                default : cout << "> Error!" << endl; break;
            }
            
        }

    }while(opcion != 0);

    return 0;
}