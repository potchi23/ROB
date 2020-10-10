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

    public: 
        Grafo(): _nNodos(0), _nAristas(0){};

        void creaNodo(const T &nodo);
        void uneNodos(const T &nodo1, const T &nodo2, const int &peso);
        void representa() const;
        unsigned int numNodos() const;
};


#endif //__GRAFO_H