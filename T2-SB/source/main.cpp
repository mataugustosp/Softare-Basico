#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h>
#include "../include/utils.hpp"
#include "../include/montador.hpp"
#include "../include/simulador.hpp"
#include "../include/ligador.hpp"

using namespace std;

int main(int argc, char **argv)
{
    // O nome do arquivo a ser aberto e o segundo argumento
    string arqv = argv[1];
    int tamanho = arqv.size();
    // Se o arquivo passado por parametro tiver a extensão .obj,
    // iniciaremos o simulador
    if (argc == 2)
    {
        if (arqv.substr(tamanho - 4, tamanho) == ".obj")
        {
            Simulador(arqv);
        }
        else if (arqv.substr(tamanho - 4, tamanho) == ".asm")
        {
            PrimeiraPassagem(arqv);
            SegundaPassagem(arqv, 0);
            Ligador(argv[1], "0", "0" , 1);
        }
        else
        {
            cout << " ERRO: O arquivo passado não tem a extensão adequada. " << endl;
        }
    }
    if(argc == 3)
    {
        PrimeiraPassagem(argv[1]);
        SegundaPassagem(argv[1], 1);
        PrimeiraPassagem(argv[2]);
        SegundaPassagem(argv[2], 1);       
    }
    if(argc == 4)
    {
        PrimeiraPassagem(argv[1]);
        SegundaPassagem(argv[1], 1);
        PrimeiraPassagem(argv[2]);
        SegundaPassagem(argv[2],1);
        PrimeiraPassagem(argv[3]);
        SegundaPassagem(argv[3],1);
    }

    return 0;
}