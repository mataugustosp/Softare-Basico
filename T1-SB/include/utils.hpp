#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>

using namespace std;

// Tabela de Instrucoes 
extern map<string, int> TI;

//Tabela de diretivas
extern map<string, int> TD;

//Tabela de Simbolos
// Map com chave string e valor int
extern map<string,int> TS;

//Tabela que armazena os dados obtidos no Section Text
extern map<int,int> sText;

//Tabela que armazena os dados obtidos no Section Data 
extern map<int,int> sData;

struct Line {
    string rotulo;
    string operacao;
    string operador1;
    string operador2;
};

int TamanhoOp(string instrucao);
string Maiusculo(string str);
Line separa(string str);
int existe(const string& nome, const map<string, int>& tabela);
int ConfereOp(Line lineop);
int LinhaVazia(Line lineop);
void trataData(string str);

#endif 
