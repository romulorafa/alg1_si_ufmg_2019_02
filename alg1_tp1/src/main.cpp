/*
 *  Executa método MIT para jogar Blackjack
 */


#include "../include/Blackjack.h"
#include <cstdlib>
#include <sstream>
using namespace std;

string IntToString(int a);

string IntToString(int a)
{
    ostringstream temp;
    temp << a;
    return temp.str();
}

int main(int argc, char** argv)
{
    /* Recebe o número de alunos, relações e instruções */
    int alunos, relacoes, instrucoes; 
    std::cin >> alunos;
    std::cin >> relacoes;
    std::cin >> instrucoes;

    if ((alunos == 0) || (relacoes == 0)){
        std::cout << 0;
        return 0;
    }
    else{
        Blackjack * bjack = new Blackjack("Blackjack MIT");
        
        /* Cria os vértices dos alunos, dando para cada um o nome de 1 até alunos */
        int leitor;
        for(int i=0; i<alunos; i++)
        {
            std::cin >> leitor;
            bjack->addVertice( leitor, IntToString(i+1));
        }
            
        /* Cria as relações entre os alunos */
        std::string x, y;
        for(int i=0; i<relacoes; i++)
        {
            std::cin >> x;
            std::cin >> y;
            bjack->addAresta(y, x);
        }
        
        /* Guarda as instruções */
        char inst;
        std::string a, b;
        std::string insts [instrucoes][3];
        for(int i=0; i<instrucoes; i++)
        {
            std::cin >> inst;
            switch(inst)
            {
                case('S'):
                    std::cin >> a;
                    std::cin >> b;
                    insts[i][0] = "S";
                    insts[i][1] = a;
                    insts[i][2] = b;
                    break;
                case('C'):
                    std::cin >> a;
                    insts[i][0] = "C";
                    insts[i][1] = a;
                    break;
                case('M'):
                    insts[i][0] = "M";
                    break;
            }
        }
        
        std::cout << std::endl;
        
        /* Executa as instruções */
        for(int i=0; i<instrucoes; i++)
        {
            if(insts[i][0] == "S")
            {
                bjack->swap(insts[i][1], insts[i][2]);
            }
            else if(insts[i][0] == "C")
            {
                bjack->commander(insts[i][1]);
            }
            else if (insts[i][0] == "M")
            {
                bjack->meeting();
            }
        }
        delete bjack;
    }
    return 0;
}