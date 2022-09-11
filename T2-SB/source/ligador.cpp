#include "../include/ligador.hpp"

// Ligador recebe 3 strings e o um int tamanho que indica a quantidade de arquivos
// mandados

int tamanho;

void Ligador(string a, string b, string c, int tamanho)
{
    if (tamanho == 1)
    {
        // String que pega linha do arquivo
        string linha;
        // Abre o arquivo dado
        ifstream teste;
        teste.open("Output/" + a.substr(0, a.size() - 4) + ".obj");
        // Enquanto não chegamos ao fim do arquivo, faremos:
        getline(teste, linha);

        imprimeLigador(linha);
        
        teste.close();
    }
}

