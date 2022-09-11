#include "../include/simulador.hpp"


// A PARTIR DE AGORA, INICIAREMOS A SIMULAÇÃO
void Simulador(string arqv){

    // Abrindo o arquivo .obj
    ifstream teste;
    // Arquivo de saida 
    ofstream teste_saida;

    teste.open("Output/" + arqv);
    // Arquivo de saida gerado 
    teste_saida.open("Output/saida.out");
    int ACC = 0;
    int PC = 0;
    int output = 0;
    int x = 0; 
    string linha;
    
    // Obtenho uma linha do arquivo fonte 
    getline(teste,linha);
    // Funcao para tratar a secao de dados e de texto 
    trataData(linha);

    /*for(auto it= sText.begin(); it != sText.end(); it++){
        cout << it->first << " -> " << it->second << endl;
    }*/
    

    while(sText[PC] != 14){

        switch(sText[PC]){
            
            case 1:
                cout << "- Depois da instrução ADD:" << endl;
                ACC = ACC + sData[sText[PC + 1]];
                PC += 2;
                break;

            case 2:
                cout << "- Depois da instrução SUB:" << endl;
                ACC = ACC - sData[sText[PC + 1]];
                PC += 2;
                break;

            case 3:
                cout << "- Depois da instrução MUL:" << endl;
                ACC = ACC * sData[sText[PC + 1]];
                PC += 2;
                break;

            case 4:
                cout << "- Depois da instrução DIV:" << endl;
                ACC = ACC / sData[sText[PC + 1]];
                PC += 2;
                break;
            case 5:
                cout << "- Depois da instrução JMP:" << endl;
                PC = sText[PC + 1];

                break;
            case 6:
                cout << "- Depois da instrução JMPN:" << endl;
                if(ACC < 0){
                    PC = sText[PC + 1];
                }
                else{
                    PC += 2;
                }
                break;
            case 7:
                cout << "- Depois da instrução JMPP:" << endl;
                if(ACC > 0){
                    PC = sText[PC + 1];
                }
                else{
                    PC += 2;
                }
                break;
            case 8:
                cout << "- Depois da instrução JMPZ:" << endl;
                if(ACC == 0){
                    PC = sText[PC + 1];
                }
                else{
                    PC += 2;
                }
                break;
            case 9:
                cout << "- Depois da instrução COPY:" << endl;
                sData[sText[PC + 2]] = sData[sText[PC + 1]];
                PC += 3;

                break;
            case 10:
                cout << "- Depois da instrução LOAD:" << endl;
                ACC = sData[sText[PC + 1]];
                PC += 2;
                break;
            case 11:
                cout << "- Depois da instrução STORE:" << endl;
                sData[sText[PC + 1]] = ACC;
                PC += 2;
                break;
            case 12:
                cout << "- Insira um valor para o operador:" << endl;
                cin >> sData[sText[PC + 1]];
                PC += 2;

                break;
            case 13:
                cout << "- Depois da instrução OUTPUT:" << endl;
                output = sData[sText[PC + 1]];
                teste_saida << output;
                teste_saida << " ";
                PC += 2;
                break;
        }
        
        cout << "PC" << " <- "<< PC << endl;
        cout << "ACC" << " <- " << ACC << endl;
        
    
    }   
    teste.close();

}