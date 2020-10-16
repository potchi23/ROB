#ifndef __GRAFO_H
#define __GRAFO_H

#include "lista.h"
#include "DiccionarioHash.h"

class ENodoNoExiste {};
class ENodosNoSuficientes{};
class EGrafoVacio{};
class ENodoExistente{};
class EAristaExistente{};

template <class T>
class Grafo{

    private:
        /**
         * Cada clave del diccionario representa
         * un nodo del grafo.
         * 
         * Diccionario<nodos, lista de aristas>
        */
        DiccionarioHash<T, Lista<T>> nodos;
        unsigned int _nNodos;
        unsigned int _nAristas;
        void recorreLista(const T &ant, const T &origen, const T &act, const T &destino, bool flags[], int &n);
        
        Lista<T> d;

    public: 
        Grafo(): _nNodos(0), _nAristas(0){};

        void creaNodo(const T &nodo);
        void uneNodos(const T &nodo1, const T &nodo2, const int &peso);
        void representa() const;
        unsigned int numNodos() const;
        void muestraCaminos(const T &origen, const T&destino);
        void dijkstra(const T &origen, const T&destino) const;
};


#endif //__GRAFO_H