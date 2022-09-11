#ifndef MONTADOR_H
#define MONTADOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "../include/utils.hpp"

using namespace std;

void PrimeiraPassagem(string arqv);
void SegundaPassagem(string arqv, int flag_end_begin);
void Simulador(string arqv);


#endif