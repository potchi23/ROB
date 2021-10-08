#include <iostream>
#include "grafo.h"

//Suponemos que el valor máximo de los caminos es 100000
#define INFINITO 100000;

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

    // 1 1 1 2 1 3 1 4 2 1 2 5 2 1 3 4 2 2 4 2 2 3 4 1 4 1 4 //secuencia para generar automaticamente un grafo de prueba

    template<>
    void Grafo<int>::recorreLista(const int &origen, const int &destino, int peso, bool visitado[], Lista<int> lista, int &n){
        
        visitado[origen] = true;

        if(origen == destino){
            n++;
            Lista<int>::ConstIterator it = lista.cbegin();

            while(it != lista.cend()){
                cout << "[" << it.elem() << "]";
                it.next();

                if(it != lista.cend()) cout << "->";
            }
            cout << " peso: " << peso << endl;
        }

        else{
            DiccionarioHash<int,Lista<int>>::ConstIterator nodo = nodos.cbusca(origen);
            Lista<int>::ConstIterator it = nodo.valor().cbegin();
            Lista<int>::ConstIterator itEnd = nodo.valor().cend();
            int elem;

            while(it != itEnd){
                elem = it.elem();

                if(!visitado[elem]){
                    visitado[elem] = true;
                    lista.pon_final(elem, it.peso());
                    recorreLista(elem, destino, peso + it.peso(), visitado, lista, n);
                    lista.quita_final();
                }

                it.next();
            }
        }

        visitado[origen] = false;
        peso = 0;
    }

    

    template<>
    void Grafo<int>::muestraCaminos(const int &origen, const int &destino) {
        int n = 0;
        bool visitado[_nNodos];
        Lista<int> lista;
        for(int i = 0; i < _nNodos; i++) visitado[i] = false; //reiniciamos flags

        lista.pon_final(origen, 0);

        recorreLista(origen, destino, 0, visitado, lista, n);

        cout << "Se han encontrado " << n << " caminos. " << endl << endl;
    }

    template<>
    void Grafo<int>::muestraCaminoMasCorto(const int &origen, const int &destino, const DiccionarioHash<int, tablaDijkstra> &tabla, Lista<int> lista){
        
        if(destino == origen){
            lista.pon_ppio(origen, 0);

            Lista<int>::ConstIterator listaIt = lista.cbegin();
            Lista<int>::ConstIterator listaItEnd = lista.cend();

            while(listaIt != listaItEnd){
                cout << "[" << listaIt.elem() << "]" ;

                listaIt.next();
                if(listaIt != listaItEnd) cout << "->";
            }

            cout << endl;
        }

        else{
            lista.pon_ppio(destino, 0);
            muestraCaminoMasCorto(origen, tabla.valorPara(destino).nodoAnterior, tabla, lista);
        }
    }

    template<>
    void Grafo<int>::resuelveDijkstra(const int &origen, bool visitado[], DiccionarioHash<int, tablaDijkstra> &tabla, Lista<int> cola){
        int nodo, peso, act;

        while(!cola.esVacia()){
            Lista<int> lista = nodos.valorPara(cola.primero());
            Lista<int>::ConstIterator listaIt = lista.cbegin();
            Lista<int>::ConstIterator listaItEnd = lista.cend();
            act = cola.primero();

            while(listaIt != listaItEnd){
                nodo = listaIt.elem();
                peso = listaIt.peso();
                DiccionarioHash<int,tablaDijkstra>::Iterator tAct = tabla.busca(nodo);

                if(!visitado[act]){
                    DiccionarioHash<int,tablaDijkstra>::Iterator tAnt = tabla.busca(act);

                    tablaDijkstra valores = tAct.valor();

                    int n = tAnt.valor().distanciaMasCorta + peso;

                    if(n < tAct.valor().distanciaMasCorta){
                        valores.nodoAnterior = act;
                        valores.distanciaMasCorta = n;
                    }

                    tAct.setVal(valores);
                }

                listaIt.next();
            }
            
            visitado[act] = true;
            cola.quita_ppio();
        }
    }

    template<>
    void Grafo<int>::dijkstra(const int &origen, const int &destino) {
        bool visitado[_nNodos];
        DiccionarioHash<int, tablaDijkstra> tabla;
        Lista<int> cola;

        for(int i = 0; i < _nNodos; i++) visitado[i] = false; //reiniciamos flags

        DiccionarioHash<int,Lista<int>>::ConstIterator it = nodos.cbusca(origen);
        DiccionarioHash<int,Lista<int>>::ConstIterator itEnd = nodos.cend();

        //iniciamos la tabla
        while(it != itEnd){ 
            tablaDijkstra valores;
            valores.distanciaMasCorta = it.clave() == origen ? 0 : INFINITO;

            tabla.inserta(it.clave(), valores);
            cola.pon_final(it.clave(), 0);
            it.next();
        }
        
        if(cola.longitud() < _nNodos){
            DiccionarioHash<int,Lista<int>>::ConstIterator aux = nodos.cbegin();
            DiccionarioHash<int,Lista<int>>::ConstIterator auxEnd = nodos.cbusca(origen);
            while(aux != auxEnd){
                tablaDijkstra valores;
                valores.distanciaMasCorta = aux.clave() == origen ? 0 : INFINITO;
                tabla.inserta(aux.clave(), valores);

                cola.pon_final(aux.clave(), 0);
                aux.next();
            }
        }

        //Resolvemos el algoritmo

        resuelveDijkstra(origen, visitado, tabla,cola);

        //MOSTRAR TABLA GENERADA POR EL ALGORITMO DE DIJKSTRA
        DiccionarioHash<int,tablaDijkstra>::ConstIterator tIt = tabla.cbegin();
        DiccionarioHash<int,tablaDijkstra>::ConstIterator tItEnd = tabla.cend();
        
        cout << "Tabla generada por el algoritmo de Dijkstra: "<< endl;
        cout << "nodo" << " | " << "distancia" << "  | " << "nodo anterior" << endl;
        while(tIt != tItEnd){
            cout << tIt.clave() << "    | " 
                 << tIt.valor().distanciaMasCorta << "          | ";

            if(tIt.clave() == origen)
                cout << "-" << endl;
            else
                cout << tIt.valor().nodoAnterior << endl;

            tIt.next();
        }

        //Mostramos el camino más corto
        cout << endl << "Camino más corto: ";
        muestraCaminoMasCorto(origen, destino, tabla, Lista<int>());        
    }