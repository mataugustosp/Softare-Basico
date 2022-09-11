#include "../include/montador.hpp"


int erro = 0;

// A PARTIR DE AGORA INICIAMOS COM A PRIMEIRA PASSAGEM DO MONTADOR, QUE IRA IDENTIFICAR O ENDERECO DE CADA UM DOS ROTULOS
void PrimeiraPassagem(string arqv){
    ifstream teste;
    string linha;
    teste.open("Input/" + arqv);
    int contador_posicao = 0;
    int contador_linha = 1;    
    if(teste.is_open()){
        // Enquanto o arquivo nao chegou ao fim 
        while(!teste.eof()){
            // Obtenho uma linha do arquivo fonte 
            getline(teste,linha);
            
            //Vamos agora separar as palavras da linha lida 
            Line lineop = separa(Maiusculo(linha));
            
            if(lineop.rotulo.size() > 50){
                cout << "ERRO: O rótulo deve ter menos que 50 caracteres (Linha:" << contador_linha << ")."<< endl;
                erro++;
            }
            if(lineop.rotulo[0] == '0' || lineop.rotulo[0] == '1' || lineop.rotulo[0] == '2' || lineop.rotulo[0] == '3' || lineop.rotulo[0] == '4' || lineop.rotulo[0] == '5' || lineop.rotulo[0] == '6' || lineop.rotulo[0] =='7' || lineop.rotulo[0] == '8' || lineop.rotulo[0] == '9') {
                cout << "ERRO: O primeiro caractere de um rótulo não pode ser um número (Linha:" << contador_linha << ")."<< endl;
                erro++;
            }  
            // Se existe rótulo, iremos procura - lo na tabela de simbolos
            if (lineop.rotulo != ""){
                // Verifica se o rotulo já existe na tabela de simbolos
                if(existe(lineop.rotulo,TS)){
                    cout << "ERRO: Simbolo redefinido (Linha:" << contador_linha << ")" << endl;
                    erro++;
                }
                else{
                    // Se nao existe, insere na tabela 
                    TS[lineop.rotulo] = contador_posicao;
                }  
            }
            if(lineop.operacao != ""){
                if(existe(lineop.operacao,TI)){
                    contador_posicao += TamanhoOp(lineop.operacao);
                }   
                else{
                    // Procura operacao na tabela de diretivas
                    if(existe(lineop.operacao,TD)){
                        contador_posicao += TamanhoOp(lineop.operacao);
                    }
                    else{
                        //ERRO
                        cout<< "ERRO: Operação não identificada: "<<  lineop.operacao << " (Linha:" << contador_linha << ")"<< endl;
                        erro++;                       
                    }   
                }
            }
            // Incrementamos o contador da linha
            
            contador_linha++;
        }
        /*for(auto it= TS.begin(); it != TS.end(); it++){
            cout << it->first << " -> " << it->second << endl;
        }*/

        teste.close();
    }
    else{
        //ERRO
        cout << "ERRO: Nao foi possivel abrir o arquivo." << endl;
        exit(1);
    }

}


// A PARTIR DE AGORA INICIAMOS COM A SEGUNDA PASSAGEM DO MONTADOR, QUE IRA PASSAR PARA O ARQUIVO OBJETO OS OPCODES
void SegundaPassagem(string arqv){
    ifstream teste;
    // Arquivo de saida 
    ofstream teste_saida;

    string linha;
    teste.open("Input/" + arqv);
    int contador_posicao = 0;
     int contador_posicao2 = 0;
    int contador_linha = 1;
    int sub = 0;   
    int stext = 0;
    teste_saida.open("Output/" + arqv.substr( 0, arqv.size() - 4 ) + ".obj");

    // Enquanto o arquivo nao chegou ao fim 
    while(!teste.eof()){ 
        sub = 0;       
        // Obtenho uma linha do arquivo fonte 
        getline(teste,linha);

        //Vamos agora separar as palavras da linha lida 
        Line lineop = separa(Maiusculo(linha));

        // Se tivermos o SECTION TEXT usaremos a label STEXT PARA IDENTIFICAR SEU COMECO
        if(lineop.operacao == "SECTION" && lineop.operador1 == "TEXT"){
            teste_saida << "STEXT" << " ";
            stext = 1;
        }
        if(lineop.operacao != "SECTION" && lineop.operador1 != "TEXT" && stext == 0){
            contador_posicao2 += TamanhoOp(lineop.operacao);
        }

        if(lineop.operacao != "" && existe(lineop.operacao,TI)){
            contador_posicao = contador_posicao + TamanhoOp(lineop.operacao);
            if(ConfereOp(lineop)){
                teste_saida << TI[lineop.operacao];
                teste_saida << " ";

                if(lineop.operacao == "JMP" || lineop.operacao == "JMPP" || lineop.operacao == "JMPN" || lineop.operacao == "JMPZ"){
                    sub = 1;
                }

                if(lineop.operador1 != "" && existe(lineop.operador1,TS) && sub == 0) {
                    teste_saida << TS[lineop.operador1];
                    teste_saida << " "; 
                }
                else if(lineop.operador1 != "" && existe(lineop.operador1,TS) && sub == 1){
                    teste_saida << TS[lineop.operador1] - contador_posicao2 ;
                    teste_saida << " "; 
                }
                else if(lineop.operador1 != "" && !existe(lineop.operador1,TS)) {
                    cout << "ERRO: Símbolo indefinido (Linha:" << contador_linha << ")" << endl;
                    erro++; 
                }
                if(lineop.operador2 != "" && existe(lineop.operador2,TS)){
                    teste_saida << TS[lineop.operador2];
                    teste_saida << " ";   
                }
                else if(lineop.operador2 != "" && !existe(lineop.operador2,TS)){
                    cout << "ERRO: Simbolo indefinido (Linha:" << contador_linha << ")" << endl;
                    erro++; 
                }
            }
            else{
                cout << "ERRO: Quantidade incorreta de operandos (Linha:" << contador_linha << ")" << endl;
                erro++; 
            }  
        }
        else{
            if(lineop.operacao != ""){
                // Procura operacao na tabela de diretivas
                    if(existe(lineop.operacao,TD)){
                        if(lineop.operacao == "CONST"){
                            teste_saida << lineop.operador1;
                            teste_saida << " ";

                        }
                        else if(lineop.operacao == "SPACE"){
                            teste_saida << "0";
                            teste_saida << " ";

                        }
                    } 
            }
        }
        contador_linha++;
        
    }
    cout << "Arquivo objeto gerado com [" << erro << "] erros."<< endl;
    teste.close();
    teste_saida.close();

}








    



