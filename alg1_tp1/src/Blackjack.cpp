/*
 * Classe representando o estilo MIT para jogar Blackjack.
 */


#include "../include/Blackjack.h"

Blackjack::Blackjack(){}

Blackjack::Blackjack(std::string nomeGrafo)
{
    Grafo::setNome(nomeGrafo); 
}


int Grafo::relacao(int a, int b)
{
    int rel = 0;
    /* Verifica se a e b existem */
    int indexa = this->getIndex(a);
    int indexb = this->getIndex(b);
    if(indexa != -1 && indexb != -1)
    {
        /* Verifica se a está direcionado à b */
        if(this->getIndexLista(a, b) != -1)
        {
            rel = 1;
        }
        /* Verifica se b está direcionado à a */
        else if(this->getIndexLista(b, a) != -1)
        {
            rel = -1;
        }
    }

    return rel;
}


int Blackjack::verificaCiclo(int origem, int vertice, bool inicio)
{
    if (vertice == origem && inicio == false)
    {
        return 1;
    }
    else if(this->vertices.at(this->getIndex(vertice)).listaAdj.size() == 0)
    {
        return 0;
    }
    else
    {
        int index = this->getIndex(vertice);
        int contagem = 0;
        for(int i = 0; i < this->vertices.at(index).listaAdj.size(); i++)
            contagem += this->verificaCiclo(origem
                , this->vertices.at(index).listaAdj.at(i), false);
        
        return contagem;
    }
}


bool Blackjack::swap(std::string a, std::string b)
{
    /* Verifica se há aresta a - > b */
    if (this->getIndexLista(b, a) != -1)
    {
        /* Executa swap: remove b em a e adiciona a em b */
        this->rmAresta(b, a);
        this->addAresta(a, b);

        /* Verifica se há ciclo e caso haja, desfaz o swap */
        int aValor = this->nome2valor(a);
        if ( this->verificaCiclo(aValor, aValor, true) != 0)
        {
            this->rmAresta(a, b);
            this->addAresta(b, a);
            std::cout << "S N" << std::endl;
            return false;
        }
        else
        {
            std::cout << "S T" << std::endl;
            return true;
        }
    }
    else
    {
        std::cout << "S N" << std::endl;
        return true;
    }
}   


bool Blackjack::commander(std::string a)
{
    int menor = 1000;
    std::vector<int> commanders;
    
    /* Cria lista dos que comandam o vértice a */
    for(Vertice v : this->vertices)
    {
        if (this->getIndexLista(a, v.nome) != -1)
        {
            commanders.push_back(v.valor);
            if (v.valor < menor)
                menor = v.valor;
        }
    }

    /* Enquanto há cadeia de comando para ser processada */
    int i, tam, com;
    while(commanders.size() > 0)
    {
        tam = commanders.size();
        for (i = 0; i < tam; i++)
        {
            /* Remove os vértices anteriores e adiciona os que os comandam. */
            com = commanders.back();
            commanders.pop_back();
            for(Vertice v : this->vertices)
            {
                if (this->getIndexLista(com, v.valor) != -1)
                {
                    commanders.insert(commanders.begin(), v.valor);
                    if (v.valor < menor)
                        menor = v.valor;
                }
            }
        }
    }
    
    if (menor == 1000)
    {
        std::cout << "C *" << std::endl;
        return false;
    }
    else
    {
        std::cout << "C " << menor << std::endl;
        return true;
    }
}


void Blackjack::meeting()
{
    /* Limpa a lista de flags */
    this->flags.clear();
    
    /* Chama a função recursiva com o vértice que não está em nenhuma
     *  lista de adjacências dos vértices. 
     */
    std::cout << "M ";
    for (Vertice v : this->vertices)
    {
        int master = true;
        for (int aresta=0; aresta<this->vertices.size(); aresta++)
        {
            for(int i = 0; i < this->vertices.at(aresta).listaAdj.size(); i++)
            {
                if (this->vertices.at(aresta).listaAdj.at(i) == v.valor)
                {
                    master = false;
                    break;
                }
            }
            if (!master)
                break;
        }
        if (master)
        {
            std::cout << v.nome << " ";
            this->flags.push_back(v.valor);
            this->meetingRec(v.valor);
        }
    }
}
    

void Blackjack::meetingRec(int atual)
{

    if (this->vertices.at(this->getIndex(atual)).listaAdj.size() != 0)
    {
        /* Adiciona vértice como visitado na lista flags */
        this->flags.push_back(atual);
        /* Imprime os comandados do atual e depois chama a função novamente 
         *  para os que são comandados por eles.
         */
        int index = this->getIndex(atual);
        int contagem = 0;
        int espaco = false;
        for(int i = 0; i < this->vertices.at(index).listaAdj.size(); i++)
        {
            if(!this->jaImpresso(this->vertices.at(index).listaAdj.at(i)))
            {
                std::cout << " " << this->valor2nome(
                    this->vertices.at(index).listaAdj.at(i));
                this->flags.push_back(this->vertices.at(index).listaAdj.at(i));
                espaco = true;
            }
            if (espaco)
                std::cout << "  ";
        }
        for(int i = 0; i < this->vertices.at(index).listaAdj.size(); i++)
            this->meetingRec(this->vertices.at(index).listaAdj.at(i));
    }
}
        

bool Blackjack::jaImpresso(int vertice)
{
    bool found = false;
    for (auto & elem : this->flags)
    {
        if (elem == vertice)
        {
            found = true;
            break;
        }
    }
    return found;
}

Blackjack::~Blackjack() {
}
