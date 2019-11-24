#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

#define MAX_ORCAMENTO 10000
#define MIN_ORCAMENTO 100
#define MAX_ILHAS 100
#define MIN_ILHAS 1

int main(){
    cout << "Gerador do TP2 de ALG1!" << endl << endl;
    srand(time(NULL));
    ofstream ofs("./gerados/meu_exemplo.txt", std::ofstream::out);
    int orcamento = 0;
    int numIlhas = 0;
    cout << "Digite o seu orcamento (100 <= orcamento <= 10.000) ";
    cin >> orcamento;
    cout << endl;
    while ((orcamento < MIN_ORCAMENTO) || (orcamento > MAX_ORCAMENTO)){
        cout << "VALOR INVÁLIDO - Digite o seu orcamento (100 <= orcamento <= 10.000) ";
        cin >> orcamento;
        cout << endl;
    }
    cout << "Digite agora o numero de ilhas da sua viagem (! Lembrando que a pontuacao delas variam de 1 a 100 nesse simulador! ";
    cin >> numIlhas;
    cout << endl;
    while ((numIlhas < MIN_ILHAS) || (numIlhas > MAX_ILHAS)){
        cin >> numIlhas;
    }
    ofs << orcamento << " " << numIlhas << endl;
    for (int i = 0; i < numIlhas; i++){
        ofs << (100 + rand() % 10000) << " " << 1 + rand() % 100 << endl;
    }
    ofs.close();
    cout << "Parabens! Arquivo gerado com sucesso" << endl;
    return 0;
}