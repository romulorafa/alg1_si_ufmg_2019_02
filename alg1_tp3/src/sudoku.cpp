#include <cstdlib>
#include <string>
#include <vector>
#include "Grafo.h"

using namespace std;


bool sudoku(Grafo * gf, int nCores, int lastColored);
/* -1 para solução inválida, 0 para solução incompleta
 * , 1 para solução encontrada */
int testaSolucao(Grafo * gf);


int main(int argc, char** argv)
{
    /* Iniciando contagem de tempo de execução da solução implementada */
    /* clock_t tempoInicial, tempoFinal;
    tempoInicial = clock(); */

    int dim;
    int quadCol;
    int quadLin;
    std::cin >> dim >> quadCol >> quadLin;
    
    Grafo * gf = new Grafo();
    int cor;
    /* Adiciona vértices */
    for (int v=0; v<(dim*dim); v++)
    {
        std::cin >> cor;
        gf->addVertice(v, to_string(v), cor);
    }
    
    /* Cria matrix auxiliar com índices para ligação entre vértices */
    int aux [dim][dim];
    int nVertice = 0;
    for (int i=0; i<dim; i++)
        for (int j=0; j<dim; j++)
        {
            aux[i][j] = nVertice;
            nVertice++;
        }
    
    /* Cria ligação entre vértices em mesma linha e coluna*/
    int lin = 0;
    int col = 0;
    for(int lin=0; lin<dim; lin++)
    {
        for(int col=0; col<dim; col++)
        {
            /* Para cada vértice de número aux[lin][col] */
            for (int adjLin=0; adjLin<dim; adjLin++)
                if (aux[lin][col] != aux[adjLin][col])
                    gf->addAresta(aux[lin][col], aux[adjLin][col]);
            for (int adjCol=0; adjCol<dim; adjCol++)
                if (aux[lin][col] != aux[lin][adjCol])
                    gf->addAresta(aux[lin][col], aux[lin][adjCol]);
        }
    }
    
    /* Cria ligação entre vértices em mesmo quadrante */
    int nQuad = 0;
    for(int lin=0; lin<dim; lin+=quadLin)
    {
        for(int col=0; col<dim; col+=quadCol)
        {
            /* Para cada quadrante iniciando no número aux[lin][col], 
                  para cada vértice, varre todo o quadrante criando relações*/
            for (int qlv=lin; qlv<(lin+quadLin); qlv++)
                for (int qcv=col; qcv<(col+quadCol); qcv++)
                    for (int ql=lin; ql<(lin+quadLin); ql++)
                        for (int qc=col; qc<(col+quadCol); qc++)
                            if(aux[qlv][qcv] != aux[ql][qc])
                                gf->addAresta(aux[qlv][qcv], aux[ql][qc]);
        }
    }
    
    /* Colore o grafo para resolver o Sudoku */
    int incolor = -1;
    for (int i=0; i<gf->getNumVertices(); i++)
        if (gf->getColor(i) == 0)
        {
            incolor = i;
            break;
        }
    if (sudoku(gf, quadCol * quadLin, incolor))
        std::cout << "solução" << std::endl;
    else
       std::cout << "sem solução" << std::endl;
    for (int i=0; i<(dim*dim); i++)
    {
        if (i%dim == 0)
            std::cout << std::endl;
        std::cout << gf->getColor(i) << " ";
    }
    
    /* Terminando a contagem de tempo de execução da solução implementada */
    /*tempoFinal = clock();
    printf("Tempo: %lf\n", (tempoFinal - tempoInicial) * 1000.0 / CLOCKS_PER_SEC);*/

    return 0;
}


bool sudoku(Grafo * gf, int nCores, int lastColored)
{
    int sol = testaSolucao(gf);
    /* Testa se grafo é inválido para o Sudoku */
    if (sol == -1)
        return false;
    /* Testa se grafo é solução válida para o Sudoku */
    else if (sol == 1)
    {
        return true;
    }
    /* Testa se grafo é solução incompleta para o Sudoku */
    else
    {
        /* Busca aresta sem cor */
        int incolor = -1;
        for (int i=0; i<gf->getNumVertices(); i++)
            if (gf->getColor(i) == 0)
            {
                incolor = i;
                break;
            }
        
        if(incolor == -1)
            return false;
        
        int * adjIncolor;
        int adjSize;
        adjIncolor = gf->getArestas(incolor, adjSize);
        int disp = 1;
        bool indisp = false;
        while(disp <= nCores)
        {
            for (int ad=0; ad<adjSize; ad++)
                if (disp == gf->getColor(adjIncolor[ad]))
                {
                    disp++;
                    indisp = true;
                    break;
                }
            
            if(indisp)
            {
                indisp = false;
            }
            else
            {
                gf->setColor(incolor, disp);
                if (sudoku(gf, nCores, incolor))
                {
                    delete(adjIncolor);
                    return true;
                }
                else
                {
                   gf->setColor(incolor, 0);
                }
                disp++;
            }
        }
        return false;
    }
}


int testaSolucao(Grafo * gf)
{
    int * adj;
    bool incompleto = false; 
    /* Verifica se para cada vértice todas as cores dos seus adjacentes 
     * são diferentes. A cor 0 significa ausência de cor, vértice não tingido */
    int color = 0;
    int sz = 0;
    for (int i=0; i<gf->getNumVertices(); i++)
    {
        color = gf->getColor(i);
        if(color != 0)
        {
            adj = gf->getArestas(i, sz);
            for (int a=0; a<sz; a++)
                if (gf->getColor(adj[a]) == color)
                    return -1;
            delete(adj);
        }
        else
            incompleto = true;
    }
    
    if(incompleto)
        return 0;
    else
        return 1;
}
