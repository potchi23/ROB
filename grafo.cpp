#include <iostream>
#include "grafo.h"
using namespace std;
    
    template<>
    void Grafo<int>::creaNodo(const int &nodo){
        if(nodos.contiene(nodo)) throw ENodoExistente();

        nodos.inserta(nodo, Lista<int>());
        _nNodos++;
    }

    template<>
    void Grafo<int>::uneNodos(const int &nodo1, const int &nodo2, const int &peso){
        if(_nNodos < 2) throw ENodosNoSuficientes();

        DiccionarioHash<int, Lista<int>>::Iterator it1 = nodos.busca(nodo1);
        DiccionarioHash<int, Lista<int>>::Iterator it2 = nodos.busca(nodo2);

        if(it1 == nodos.end() || it2 == nodos.end()) throw ENodoNoExiste();

        Lista<int>::ConstIterator lIt1 = it1.valor().cbegin();
        //Lista<int>::ConstIterator lIt2 = it2.valor().cbegin();


        if(it1.valor().longitud() != 0){
            while(lIt1.elem() != nodo2 && lIt1 != it1.valor().cend()) 
                lIt1.next();

            if(lIt1.elem() == nodo2) throw EAristaExistente();
        }

        it1.valor().pon_final(nodo2, peso);
        it2.valor().pon_final(nodo1, peso);

        _nAristas++;
    }

    template<>
    void Grafo<int>::representa() const{
        if(_nNodos == 0) throw EGrafoVacio();

        DiccionarioHash<int,Lista<int>>::ConstIterator it = nodos.cbegin();
        cout << endl;
        cout << "Lista de adyacencia: " << endl;
        while(it != nodos.cend()){
            Lista<int>::ConstIterator lIt = it.valor().cbegin();
            Lista<int>::ConstIterator lItEnd = it.valor().cend();
            cout << "[" << it.clave()<< "] -> ";
            while(lIt != lItEnd){
                cout << "[" << lIt.elem() << "," << lIt.peso()<< "] -> ";
                lIt.next();
            }
            cout << endl;
            it.next();
        }
    }

    template<>
    unsigned int Grafo<int>::numNodos() const{
        return _nNodos;
    }

    template<>
    void Grafo<int>::recorreLista(const int &ant, const int &origen, const int &act, const int &destino, Lista<int> &lista, bool visitado[], int &n) const{
        DiccionarioHash<int,Lista<int>>::ConstIterator nodo = nodos.cbusca(act);
        Lista<int>::ConstIterator itO = nodo.valor().cbegin();
        int elem;

        if(act == destino){ n++;}
    
        else{
            while(itO != nodo.valor().cend()){ //iteramos sobre cada elemento de la lista
                elem = itO.elem();

                /*
                cout << "nodo: " << act;
                cout << " elemIt: " << elem;
                cout << endl;
                */
                                
                if(elem != origen && !visitado[act] && ant != elem){
                    visitado[act] = true;

                    lista.pon_final(elem, itO.peso());
                    recorreLista(act, origen, elem, destino, lista, visitado, n);
                    for(int i = 0; i < _nNodos; i++) visitado[i] = false; //reiniciamos flags
                }

                itO.next();
            }
        }
    }

    template<>
    void Grafo<int>::muestraCaminos(const int &origen, const int &destino, Lista<int> &lista, bool visitado[]) const{

        int n = 0;
        recorreLista(origen, origen, origen, destino, lista, visitado, n);
        cout << "caminos: " << n << endl;        
    }

    template<>
    void Grafo<int>::dijkstra(const int &origen, const int &destino) const{

    }