/*
 * @file Viagem.cpp
 * 
 * Classe para implementações da maximização do proveito da viagem de férias.
 */

#include <math.h>
#include "Viagem.h"


Viagem::Viagem(int numIlhas)
{
    this->numIlhas = numIlhas;
    this->pontuacao = 0.0;
    this->pontMin = std::numeric_limits<float>::max();
    this->custoMin = std::numeric_limits<float>::max();
    this->custo = 0.0;
    this->dias = 0;
    this->porPontuacao = true;
    this->frequencia = new int[this->numIlhas];
    this->ilhas = new Ilha[this->numIlhas];
    for (int i=0; i<this->numIlhas; i++)
    {
        this->frequencia[i] = 0;
        this->ilhas[i].id = i;
        this->ilhas[i].custo = 0.0;
        this->ilhas[i].pontuacao = 0.0;
        this->ilhas[i].preco = 0.0;
    }
}


void Viagem::setIlha(int id, float custo, float pontuacao)
{
    this->ilhas[id].custo = custo;
    this->ilhas[id].pontuacao = pontuacao;
    this->ilhas[id].preco = custo/pontuacao;
    if (pontuacao < this->pontMin)
        this->pontMin = pontuacao;
    if (custo < this->custoMin)
        this->custoMin = custo;
}


Ilha Viagem::getIlha(int id)
{
    Ilha i;
    i.custo = this->ilhas[id].custo;
    i.pontuacao = this->ilhas[id].pontuacao;
    i.preco = this->ilhas[id].preco;
    i.id = id;
    
    return i;
}


int Viagem::getFrequencia(int id)
{
    return this->frequencia[id];
}


int Viagem::getNumIlhas()
{
    return this->numIlhas;
}


void Viagem::addVisita(int id)
{
    this->frequencia[id]++;
    this->pontuacao += this->ilhas[id].pontuacao;
    this->custo += this->ilhas[id].custo;
    this->dias++;
}


bool Viagem::rmVisita(int id)
{
    bool removida = true;
    if (this->frequencia[id] > 0)
    {
        this->frequencia[id]--;
        this->pontuacao -= this->ilhas[id].pontuacao;
        this->custo -= this->ilhas[id].custo;
        this->dias--;
    }
    else
        removida = false;
    
    return removida;
}


float Viagem::getPontuacao()
{
    return this->pontuacao;
}


float Viagem::getCusto()
{
    return this->custo;
}


float Viagem::getMinPont()
{
    return this->pontMin;
}


float Viagem::getMinCusto()
{
    return this->custoMin;
}


int Viagem::getDias()
{
    return this->dias;
}


Viagem::~Viagem()
{
    delete(this->frequencia);
    delete(this->ilhas);
}


void Viagem::sort(bool porPontuacao)
{
    if (porPontuacao)
        this->porPontuacao = true;
    else
        this->porPontuacao = false;
    this->mergeSort(0,this->numIlhas-1);
}


void Viagem::swap(int idA, int idB)
{
    Ilha swap;
    swap.id = this->ilhas[idA].id;
    swap.pontuacao = this->ilhas[idA].pontuacao;
    swap.custo = this->ilhas[idA].custo;
    swap.preco = this->ilhas[idA].preco;
    this->ilhas[idA].id = this->ilhas[idB].id;
    this->ilhas[idA].pontuacao = this->ilhas[idB].pontuacao;
    this->ilhas[idA].custo = this->ilhas[idB].custo;
    this->ilhas[idA].preco = this->ilhas[idB].preco;
    this->ilhas[idB].id = swap.id;
    this->ilhas[idB].pontuacao = swap.pontuacao;
    this->ilhas[idB].custo = swap.custo;
    this->ilhas[idB].preco = swap.preco;
}


/* Método para unir as soluções ordenadas do Mergesort */
int Viagem::merge(int esquerda, int m, int direita) 
{
    int n1 = m - esquerda + 1; 
    int n2 = direita - m; 

    Ilha e[n1];
    Ilha d[n2]; 

    int i, j; 
    for (i = 0; i < n1; i++) 
        e[i] = this->getIlha(esquerda + i); 
    for (j = 0; j < n2; j++) 
        d[j] = this->getIlha(m + 1+ j); 


    i = 0;  
    j = 0;
    int k = esquerda;
    while (i < n1 && j < n2) 
    { 
        if (this->porPontuacao)
        {
            if (e[i].pontuacao > d[j].pontuacao) 
            { 
                this->ilhas[k] = e[i]; 
                    i++; 
            } 
            else
            { 
                this->ilhas[k] = d[j]; 
                j++; 
            } 
            k++; 
        }
        else
        {
            if (e[i].preco <= d[j].preco) 
            { 
                this->ilhas[k] = e[i]; 
                i++; 
            } 
            else
            { 
                this->ilhas[k] = d[j]; 
                j++; 
            } 
            k++; 
        }
    } 

    while (i < n1) 
    { 
            this->ilhas[k] = e[i]; 
            i++; 
            k++; 
    } 

    while (j < n2) 
    { 
            this->ilhas[k] = d[j]; 
            j++; 
            k++; 
    } 
} 


/* Método Mergesort para ordenação das ilhas conforme algum atributo
utilizado como estratégia de solução ótima */
void Viagem::mergeSort(int l, int r) 
{ 
    if (l < r) 
    {  
        int m = l+(r-l)/2; 

        this->mergeSort(l, m); 
        this->mergeSort(m+1, r); 

        this->merge(l, m, r); 
    } 
} 