/*
 * @file Viagem.h
 * 
 * Classe para implementações da maximização do proveito da viagem de férias.
 */

#ifndef VIAGEM_H
#define VIAGEM_H

#include <limits>


struct Ilha
{
    int id;
    float custo;
    float pontuacao;
    float preco;
};

class Viagem
{
public:
    Viagem(int numIlhas);
    void setIlha(int id, float custo, float pontuacao);
    Ilha getIlha(int id);
    void addVisita(int id);
    bool rmVisita(int id);
    float getPontuacao();
    float getCusto();
    int getFrequencia(int id);
    int getNumIlhas();
    float getMinPont();
    float getMinCusto();
    int getDias();
    void sort(bool porPontuacao);
    ~Viagem();

private:
    int numIlhas;
    Ilha *ilhas;
    int *frequencia;
    float pontuacao;
    float custo;
    float pontMin;
    float custoMin;
    int dias;
    bool porPontuacao;
    void swap(int idA, int idB);
    int merge(int esquerda, int m, int direita);
    void mergeSort(int esquerda, int direita);
};

#endif /* VIAGEM_H */
