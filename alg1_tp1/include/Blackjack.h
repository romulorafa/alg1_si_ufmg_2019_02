/*
 * Classe representando o estilo MIT para jogar Blackjack.
 */


#ifndef BLACKJACK_H
#define BLACKJACK_H


#include "Grafo.h"


class Blackjack : public Grafo{
public:
    Blackjack();
    Blackjack(std::string nomeGrafo);
    bool swap(std::string a, std::string b);
    bool commander(std::string a);
    void meeting();
    virtual ~Blackjack();
private:
    std::vector<int> flags;
    int relacao(int a, int b);
    int verificaCiclo(int origem, int vertice, bool inicio);
    void meetingRec(int atual);
    bool jaImpresso(int vertice);
};

#endif /* BLACKJACK_H */
