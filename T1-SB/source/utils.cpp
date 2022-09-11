#include "../include/utils.hpp"

// ESTE ARQUIVO CONTÉM FUNCOES UTILIZADAS TANTO NA MONTAGEM QUANTO NA SIMULAÇÃO



// Tabela de Instrucoes 
map<string, int> TI = {
    {"ADD",    1},
    {"SUB",    2},
    {"MUL",    3},
    {"DIV",    4},
    {"JMP",    5},
    {"JMPN",   6},
    {"JMPP",   7},
    {"JMPZ",   8},
    //Apenas o Copy tem 2 operadores
    {"COPY",   9},
    {"LOAD",   10},
    {"STORE",  11},
    {"INPUT",  12},
    {"OUTPUT", 13},
    {"STOP",   14}
};

//Tabela de diretivas
map<string, int> TD = {
    {"SECTION", 0},
    {"SPACE",   1},
    {"CONST",   1},
};

//Tabela de Simbolos
// Map com chave string e valor int
map<string,int> TS;

//Verifica o tamanho das instrucoes
int TamanhoOp(string instrucao){
    if(instrucao == "COPY"){
        return 3;
    }
    else if(instrucao == "STOP" || instrucao == "SPACE" || instrucao == "CONST"){
        return 1;
    }
    else if(instrucao == "SECTION"){
        return 0;
    }
    else{
        return 2;
    }
}


// Funcao para transformar a string para maiuscula 
string Maiusculo(string str) {
    transform(str.begin(), str.end(),str.begin(), ::toupper);
    return str;
}


Line separa(string str){
    // Cria um vetor de strings
    // Delimitadores para retirarmos o tab e o espaco do programa assembly
    char delimiter1 = ' '; 
    char delimiter2 = '\t';
    char delimiter3 = ':';
    char delimiter4 = ',';
    // String buffer para acumular as palavras 
    string buffer = "";
    // Vetor de strings que ira retornar os termos separados
    string ret[4] = {"","","",""};
    int x = 0;
    // Struct
    Line lineop;

    // Procura na string os dois pontos para identificar a existencia de um rotulo
   if(string::npos == str.find(':')){
       // Se nao houver rotulo, grava a partir do ret[1]
       x = 1; 
   }
    for(auto letra:str)
	{
        
        //Como temos que ignorar os comentarios, se a primeira letra for ";" ignoraremos.
        if(letra == ';'){
            break;
        }
        // Armazenamos no buffer 
		if(letra != delimiter1 && letra != delimiter2 && letra != delimiter3 && letra != delimiter4) {
            buffer+=letra; 
        }

        if( (letra == delimiter1 || letra == delimiter2 || letra == delimiter4 )  && buffer != "" ) { 
            ret[x] = buffer;
            buffer = "";
            x++;
     
        }
	}

    ret[x] = buffer;
    lineop.rotulo = ret[0];
    lineop.operacao = ret[1];
    lineop.operador1 = ret[2];
    lineop.operador2 = ret[3];

    /*cout << "ret[0]" << endl;
    cout << ret[0] << endl;
    cout << "ret[1]" << endl;
    cout << ret[1] << endl;
    cout << "ret[2]" << endl;
    cout << ret[2] << endl;
    cout << "ret[3]" << endl;
    cout << ret[3] << endl;*/

    return lineop;
}

// Funcao para procurar chave em um mapa 
int existe(const string& nome, const map<string, int>& tabela)
{
    auto res = tabela.find(nome);
    if (res != tabela.end())
        return 1;
    else
        return 0;
}

// Funcao para conferir o numero de operandos para cada uma das operacoes 
int ConfereOp(Line lineop){

    if(lineop.operacao == "COPY"){
        if(lineop.operador1 != "" && lineop.operador2 != "" ){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(lineop.operacao == "STOP" || lineop.operacao == "SPACE" ){
        if(lineop.operador1 == "" &&  lineop.operador2 == ""){
            return 1;
        }
        else{
            return 0;
        }

    }
    else{
        if(lineop.operador1 != "" &&  lineop.operador2 == ""){
            return 1;
        }
        else{
            return 0;
        }

    }



}
//Funcao que identifica se a linha esta vazia ou se tem 
// SECTION DATA E SECTION TEXT
int LinhaVazia(Line lineop){
    int empty = 0;
    if(lineop.rotulo == "" ){
        empty++;
    }
    if( lineop.operacao == ""){
        empty++;
    }
    if(lineop.operador1 == ""){
        empty++;
    }
    if(lineop.operador2 == ""){
        empty++;
    }

    if(empty == 4){
        
        return 0;
    }
    else{
        return 1;
    }

}

// AS FUNCOES LISTADAS ABAIXO SÃO UTILIZADAS PARA O SIMULADOR 

//Tabela que armazena os dados obtidos no Section Data 
map<int,int> sData;

//Tabela que armazena os dados obtidos no Section Text
map<int,int> sText;

// Função utilizada para tratar o Section Data e coloca os dados na tabela Section Data 
// tendo a posição como chave e o valor como atributo 
void trataData(string str){
    // Delimitador para retirarmos o espaco da linha do opcode 
    char delimiter1 = ' '; 
    // String buffer para acumular os numeros
    string buffer = "";
    // Contador para saber a posicao da variavel 
    int c = 0;
    int b = 0;
    int x = 0;

    for(auto letra:str)
	{
        // Armazenamos no buffer 
		if(letra != delimiter1) {
            buffer+=letra; 
        }
        if (buffer == "STEXT"){
            x = 1;
            buffer = "";
        }

        if(letra == delimiter1  && buffer != "" && x == 0) { 
            sData[c] = std::stoi(buffer);
            buffer = "";
            c++;
        }
        if(letra == delimiter1  && buffer != "" && x == 1) { 
            sText[b] = std::stoi(buffer);
            buffer = "";
            b++;
        }

	}
    
}



