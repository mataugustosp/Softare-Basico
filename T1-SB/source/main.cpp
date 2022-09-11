#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h>
#include "../include/utils.hpp"
#include "../include/montador.hpp"
#include "../include/simulador.hpp"

using namespace std;


int main(int argc, char **argv)
{
    // O nome do arquivo a ser aberto e o segundo argumento
    string arqv = argv[1];
    int tamanho = arqv.size();
    // Se o arquivo passado por parametro tiver a extensão .obj,
    // iniciaremos o simulador
    if( arqv.substr( tamanho - 4, tamanho) == ".obj"){
        Simulador(arqv);
    }
    else if(arqv.substr( tamanho - 4, tamanho) == ".asm"){
        PrimeiraPassagem(arqv);
        SegundaPassagem(arqv);
    }
    else{
        cout << " ERRO: O arquivo passado não tem a extensão adequada. " << endl;
    }
    
    return 0;

}