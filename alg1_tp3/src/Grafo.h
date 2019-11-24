/*
 * Classe representando um grafo orientado com coloração.
 */


#ifndef GRAFO_H
#define GRAFO_H


#include <map>
#include <vector>
#include <iostream>
#include <stdlib.h>
using namespace std;


/* Estrutura representando um vértice */
struct Vertice
{
    int valor;
    std::string nome;
    std::vector<int> listaAdj;
    int color;
};
        

class Grafo
{
    public:
        Grafo();
        Grafo(std::string nome);
        bool addVertice(int vertice, std::string nome, int color);
        bool rmVertice(int vertice);
        bool rmVertice(std::string nomeVertice);
        bool addAresta(int vertice, int aresta);
        bool addAresta(std::string nomeVertice, std::string nomeAresta);
        bool rmAresta(int vertice, int aresta);
        bool rmAresta(std::string nomeVertice, std::string nomeAresta);
        void imprimeVertices();
        void imprimeGrafo();
        void setNome(std::string nome);
        void setColor(int vertice, int color);
        int getColor(int vertice);
        int * getArestas(int vertice, int &sz);
        int getNumVertices();
        virtual ~Grafo();
    protected:
        /* Retorna 0 se não há aresta, retorna 1 se a -> b e -1 se b -> a */
        int relacao(int a, int b);
        /* Vértices do Grafo */
        std::vector<Vertice> vertices;
        /* Busca índice de um vértice, retorna -1 se não existir */
        int getIndex(int vertice);
        /* Busca índice de um vértice, retorna -1 se não existir */
        int getIndex(std::string nome);
        /* Busca vértice na lista de adjacências de um vértice
         *  Retorna -1 se não existir
         */
        int getIndexLista(int vertice, int aresta);
        /* Busca vértice na lista de adjacências de um vértice
         *  Retorna -1 se não existir
         */
        int getIndexLista(std::string vertice, std::string aresta);
        /* Resolve o número do vértice pelo nome */
        int nome2valor(std::string nomeVertice);
        /* Resolve o nome do vértice pelo valor */
        std::string valor2nome(int vertice);
    private:
        /* Nome do Grafo */
        std::string nome;
};

#endif /* GRAFO_H */
