/*
 * Classe representando um grafo orientado.
 */


#include "../include/Grafo.h"


Grafo::Grafo(){}


Grafo::Grafo(std::string nome)
{
    this->nome = nome;
}


bool Grafo::addVertice(int vertice, std::string nome)
{
    /* Adiciona caso não exista. */
    if(this->getIndex(vertice) == -1)
    {
        Vertice v;
        v.nome = nome;
        v.valor = vertice;
        this->vertices.push_back(v);
        return true;
    }
    else
    {
        return false;
    }
}


bool Grafo::rmVertice(int vertice)
{
    /* Remove caso exista */
    int index = this->getIndex(vertice);
    if(index != -1)
    {
        /* Esvazia a lista de adjacências */
        this->vertices.at(index).listaAdj.clear();
        /* Remove vértice */
        this->vertices.erase(this->vertices.begin()+index);
        return true;
    }
    else
    {
        return true;
    }
}

bool Grafo::rmVertice(std::string nomeVertice)
{
    this->rmVertice(this->nome2valor(nomeVertice));
}


bool Grafo::addAresta(int vertice, int aresta)
{
    /* Adiciona caso a aresta exista e o vértice já não esteja nela */
    int index = this->getIndexLista(vertice, aresta);
    if(index == -1)
    {
        /* Adiciona o vértice na lista de adjacências */
            this->vertices.at(
                this->getIndex(aresta)).listaAdj.push_back(vertice);
        return true;
    }
    else
    {
        return false;
    }
}


bool Grafo::addAresta(std::string nomeVertice, std::string nomeAresta)
{
    return this->addAresta(this->nome2valor(nomeVertice)
        , this->nome2valor(nomeAresta));
}


bool Grafo::rmAresta(int vertice, int aresta)
{
    /* Verifica se existe um vértice na lista de adjacências da aresta */
    int index = this->getIndexLista(vertice, aresta);
    if(index != -1)
    {
        /* Remove o vértice da lista de adjacência */
        this->vertices.at(
            this->getIndex(aresta)).listaAdj.erase(
            this->vertices.at(this->getIndex(aresta)).listaAdj.begin()+index);
        return true;
    }
    else
    {
        return false;
    }
}


bool Grafo::rmAresta(std::string nomeVertice, std::string nomeAresta)
{
    return this->rmAresta(this->nome2valor(nomeVertice),
            this->nome2valor(nomeAresta));
}


int Grafo::getIndex(int vertice)
{
   vector<string>::iterator it;
   int i = 0;
   int index = -1;
   for (Vertice v : this->vertices)
   {
        if ( v.valor == vertice )
        {
            index = i;
            break;
        }
        i++;
   }
   
   return index;
}


int Grafo::getIndex(std::string nome)
{
   vector<string>::iterator it;
   int i = 0;
   int index = -1;
   for (Vertice v : this->vertices)
   {
        if ( v.nome == nome )
        {
            index = i;
            break;
        }
        i++;
   }
   
   return index;
}


int Grafo::getIndexLista(int vertice, int aresta)
{
    int index = -1;
    int indexAresta = this->getIndex(aresta);
    /* Verifica se existe o vértice relativo à aresta */
    /* Verifica se existe o vértice relativo à aresta */
    if(indexAresta != -1)
    {
        /* Verifica se o vértice já existe na lista de adjacências
         *  E atualiza "index" caso exista.
         */
        for(int i = 0; i<this->vertices.at(indexAresta).listaAdj.size(); i++)
            if (this->vertices.at(indexAresta).listaAdj.at(i) == vertice)
                index = i;
    }
    
    return index;
}


int Grafo::getIndexLista(std::string vertice, std::string aresta)
{
    int index = -1;
    int indexAresta = this->getIndex(aresta);
    int verticeInt = this->nome2valor(vertice);
    /* Verifica se existe o vértice relativo à aresta */
    if(indexAresta != -1)
    {
        /* Verifica se o vértice já existe na lista de adjacências
         *  E atualiza "index" caso exista.
         */
        for(int i = 0; i<this->vertices.at(indexAresta).listaAdj.size(); i++)
            if (this->vertices.at(indexAresta).listaAdj.at(i) == verticeInt)
                index = i;
    }
    
    return index;
}


void Grafo::imprimeVertices()
{
    std::cout << "Vértices do Grafo " << this->nome 
              << ": " << this->vertices.size() << std::endl << std::endl;
    for (Vertice v : this->vertices)
        std::cout << v.nome << " : " << v.valor << std::endl;
    std::cout << std::endl;
}


void Grafo::imprimeGrafo()
{
    std::cout << "Grafo " << this->nome << std::endl << std::endl;
    for (Vertice v : this->vertices)
    {
        if (v.listaAdj.empty())
        {
            std::cout << v.nome << " : " << v.valor << std::endl;
        }
        else
        {
            for (int i=0; i<v.listaAdj.size(); i++)
                std::cout << v.nome << " : " << v.valor 
                    << " -> " << v.listaAdj.at(i) << std::endl;
        }
    }
}


void Grafo::setNome(std::string nome)
{
    this->nome = nome;
}


int Grafo::nome2valor(std::string nomeVertice)
{
    return this->vertices.at(this->getIndex(nomeVertice)).valor;
}


std::string Grafo::valor2nome(int vertice)
{
    return this->vertices.at(this->getIndex(vertice)).nome;
}


Grafo::~Grafo(){}
