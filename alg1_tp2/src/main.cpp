/*
 * @file main.cpp
 * 
 * @brief Implementação da maximização do proveito da viagem de férias.
 */

#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <time.h>
#include "Viagem.h"

using namespace std;


void guloso(Viagem &viagem, float custoMax);
void dinamico(Viagem &viagem, float custoMax);
std::vector<std::string> split(const std::string& s, char delimiter);


int main(int argc, char** argv)
{
    /* Iniciando contagem de tempo de execução da solução implementada */
    /* clock_t tempoInicial, tempoFinal;
    tempoInicial = clock();*/

    /* Carrega o arquivo no objeto Viagem */
    float custoMaximo = 0.0;
    int numIlhas = 0;
    std::string linha;
    Viagem * viagem_guloso, *viagem_dinamico;
    ifstream arquivo (argv[1], std::ifstream::in);
    int id = 0;
    std::vector<std::string> linhaSplit;
    if (arquivo.is_open())
    {
        getline (arquivo, linha);
        linhaSplit = split(linha, ' ');
        custoMaximo = std::stof(linhaSplit.front());
        numIlhas = std::stoi(linhaSplit.back());
        viagem_guloso = new Viagem(numIlhas);
        viagem_dinamico = new Viagem(numIlhas);
        while ( !arquivo.eof() && id < numIlhas)
        {
            getline (arquivo, linha);
            linhaSplit = split(linha, ' ');
            viagem_guloso->setIlha(id, std::stof(linhaSplit.front())
                , std::stof(linhaSplit.back()));
            viagem_dinamico->setIlha(id, std::stof(linhaSplit.front())
                , std::stof(linhaSplit.back()));
            id++;
        }
    }
    else
    {
        std::cout << "Arquivo fechado antes de ser lido!" << std::endl;
    }
    
    /* Ordena as ilhas por preço */
    viagem_guloso->sort(false);
    
    /* Ordena as ilhas por pontuação */
    viagem_dinamico->sort(true);
    
    /* ALGORITMO GULOSO - Calcula a maior pontuação 
    possível de um roteiro com repetições de ilhas */
    guloso(*viagem_guloso, custoMaximo);
    std::cout << viagem_guloso->getPontuacao() << " "
        << viagem_guloso->getDias() << std::endl;

    /* ALGORITMO PROGRAMAÇÃO DINÂMICA - Calcula a maior pontuação 
    possível de um roteiro sem repetições de ilhas */
    dinamico(*viagem_dinamico, custoMaximo);
    std::cout << viagem_dinamico->getPontuacao() << " "
        << viagem_dinamico->getDias() << std::endl;
    
    /* Liberando memória dos objetos alocados */
    delete(viagem_guloso);
    delete(viagem_dinamico);

    /* Terminando a contagem de tempo de execução da solução implementada */
    /*tempoFinal = clock();
    printf("Tempo: %lf\n", (tempoFinal - tempoInicial) * 1000.0 / CLOCKS_PER_SEC);*/
    return 0;
}


/* Algoritmo Guloso utilizando a classe Viagem */
void guloso(Viagem &viagem, float custoMax)
{
    if ((viagem.getCusto() < custoMax)
        && (viagem.getMinCusto()+viagem.getCusto() <= custoMax))
    {
        /* Busca ilha com melhor preço que caiba no orçamento atual */
        int id = 0;
        while (viagem.getIlha(id).custo+viagem.getCusto() > custoMax)
            id++;
        
        /* Adiciona visita a ilha encontrada */
        viagem.addVisita(id);

        /* Chama o algoritmo recursivamente */
        guloso(viagem, custoMax);
    }
}


/* Algoritmo Programação Dinâmica utilizando a classe Viagem */
void dinamico(Viagem &viagem, float custoMax)
{
    if (viagem.getCusto() < custoMax)
    {
        int id = 0;
        /* Enquanto é possível visitar alguma ilha */
        while (viagem.getMinCusto()+viagem.getCusto() <= custoMax)
        {
            /* Busca ilha não visitada com melhor pontuacao 
             *  que caiba no orçamento atual 
             */
            id = 0;
            while ((viagem.getIlha(id).custo+viagem.getCusto() > custoMax)
                   || viagem.getFrequencia(id) > 0 || id > viagem.getNumIlhas())
                id++;

            /* Adiciona visita a ilha encontrada */
            if (id < viagem.getNumIlhas())
                viagem.addVisita(id);
            else
                break;
        }
    }
}


/* Método auxiliar para ler as entradas do arquivo
podendo utilizar delimitações diferentes, além de espaço simples */
std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}