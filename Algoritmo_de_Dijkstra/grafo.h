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
         * Tabla para resolver el algoritmo de Dijkstra
         */
        typedef struct{
            int distanciaMasCorta; //distancia más corta hasta origen
            T nodoAnterior; //vértice anterior
        } tablaDijkstra;

        /**
         * Cada clave del diccionario representa
         * un nodo del grafo.
         * 
         * Diccionario<nodos, lista de aristas>
        */
        DiccionarioHash<T, Lista<T>> nodos;
        unsigned int _nNodos;
        unsigned int _nAristas;
        void recorreLista(const T &origen, const T &destino, int peso, bool visitado[], Lista<T> lista, int &n);
        void resuelveDijkstra(const T &origen, bool visitado[], DiccionarioHash<T, tablaDijkstra> &tabla, Lista<T> cola);
        void muestraCaminoMasCorto(const T& origen, const T &destino, const DiccionarioHash<T, tablaDijkstra> &tabla, Lista<T> lista);
        //Lista<Lista<int>> listaOrdenada;

    public: 
        Grafo(): _nNodos(0), _nAristas(0){};

        void creaNodo(const T &nodo);
        void uneNodos(const T &nodo1, const T &nodo2, const int &peso);
        void representa() const;
        unsigned int numNodos() const;
        void muestraCaminos(const T &origen, const T&destino);
        void dijkstra(const T &origen, const T&destino);
};


#endif //__GRAFO_H