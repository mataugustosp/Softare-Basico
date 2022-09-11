#include "../include/montador.hpp"

int erro = 0;


// A PARTIR DE AGORA INICIAMOS COM A PRIMEIRA PASSAGEM DO MONTADOR, QUE IRA IDENTIFICAR O ENDERECO DE CADA UM DOS ROTULOS
void PrimeiraPassagem(string arqv)
{
    ifstream teste;
    string linha;
    teste.open("Input/" + arqv);
    int contador_posicao = 0;
    int contador_linha = 1;

    // Limpando todos os maps para nao gerar conflitos
    TS.clear();
    TU.clear();
    TDEF.clear();
    TEXTERN.clear();

    if (teste.is_open())
    {
        // Enquanto o arquivo nao chegou ao fim
        while (!teste.eof())
        {
            // Obtenho uma linha do arquivo fonte
            getline(teste, linha);

            //cout << "CONTADOR: " << contador_posicao;
            //Vamos agora separar as palavras da linha lida
            Line lineop = separa(Maiusculo(linha));

            // Popula a Tabela de Definições
            if (lineop.operacao == "PUBLIC")
            {
                TDEF[lineop.operador1] = contador_posicao;
            }

            if (lineop.rotulo.size() > 50)
            {
                cout << "ERRO: O rótulo deve ter menos que 50 caracteres (Linha:" << contador_linha << ")." << endl;
                erro++;
            }
            if (lineop.rotulo[0] == '0' || lineop.rotulo[0] == '1' || lineop.rotulo[0] == '2' || lineop.rotulo[0] == '3' || lineop.rotulo[0] == '4' || lineop.rotulo[0] == '5' || lineop.rotulo[0] == '6' || lineop.rotulo[0] == '7' || lineop.rotulo[0] == '8' || lineop.rotulo[0] == '9')
            {
                cout << "ERRO: O primeiro caractere de um rótulo não pode ser um número (Linha:" << contador_linha << ")." << endl;
                erro++;
            }
            // Se existe rótulo, iremos procura - lo na tabela de simbolos
            if (lineop.rotulo != "")
            {
                // Verifica se o rotulo já existe na tabela de simbolos
                if (existe(lineop.rotulo, TS))
                {
                    cout << "ERRO: Simbolo redefinido (Linha:" << contador_linha << ")" << endl;
                    erro++;
                }
                else
                {
                    // Se nao existe, insere na tabela
                    // Se as operaçoes forem EXTERN ou BEGIN adiciona 0
                    if (lineop.operacao == "EXTERN")
                    {
                        TS[lineop.rotulo] = 0;
                        //Adiciona na tabela que contem apenas simbolos extern
                        TEXTERN[lineop.rotulo] = 0;
                    }
                    // Seleciona as variaveis publicas
                    else
                    {
                        TS[lineop.rotulo] = contador_posicao;
                    }
                }
            }
            if (lineop.operacao != "")
            {
                if (existe(lineop.operacao, TI))
                {
                    contador_posicao += TamanhoOp(lineop.operacao);
                }
                else
                {
                    // Procura operacao na tabela de diretivas
                    if (existe(lineop.operacao, TD))
                    {
                        contador_posicao += TamanhoOp(lineop.operacao);
                    }
                    else
                    {
                        //ERRO
                        cout << "ERRO: Operação não identificada: " << lineop.operacao << " (Linha:" << contador_linha << ")" << endl;
                        erro++;
                    }
                }
            }
            // Incrementamos o contador da linha
            contador_linha++;
        }

        //for (auto it = TS.begin(); it != TS.end(); it++)
        //{
        //    cout << it->first << " -> " << it->second << endl;
        //}

        // Populando tabela de definicoes corretamente
        for (auto it = TS.begin(); it != TS.end(); it++)
        {
            if (existe(it->first, TDEF))
            {
                TDEF[it->first] = it->second;
            }
        }

        teste.close();
    }
    else
    {
        //ERRO
        cout << "ERRO: Nao foi possivel abrir o arquivo." << endl;
        exit(1);
    }
}

// A PARTIR DE AGORA INICIAMOS COM A SEGUNDA PASSAGEM DO MONTADOR, QUE IRA PASSAR PARA O ARQUIVO OBJETO OS OPCODES
void SegundaPassagem(string arqv, int flag_end_begin)
{

    ifstream teste;

    // vetor que armazena mapa de bits
    vector<int> mapa_bits;
    // vetor que armazena texto
    vector<int> texto;
    string linha;
    teste.open("Input/" + arqv);
    int contador_posicao = 0;
    int contador_posicao2 = 0;
    int contador_linha = 1;
    int stext = 0;
    int sub = 0;
    //variavel para ver se os arquivos tem begin e END
    int begin_end = 0;

    // Enquanto o arquivo nao chegou ao fim
    while (!teste.eof())
    {
        sub = 0;
        // Obtenho uma linha do arquivo fonte
        getline(teste, linha);

        //Vamos agora separar as palavras da linha lida
        Line lineop = separa(Maiusculo(linha));

        // Se tivermos o SECTION TEXT usaremos a label STEXT PARA IDENTIFICAR SEU COMECO
        if (lineop.operacao == "SECTION" && lineop.operador1 == "TEXT")
        {
            texto.push_back(1234567890);
            stext = 1;
        }

        if (lineop.operacao == "BEGIN" || lineop.operacao == "END")
        {
            begin_end++;
        }

        if (lineop.operacao != "SECTION" && lineop.operador1 != "TEXT" && stext == 0)
        {
            contador_posicao2 += TamanhoOp(lineop.operacao);
        }

        if (lineop.operacao != "" && existe(lineop.operacao, TI))
        {
            contador_posicao = contador_posicao + TamanhoOp(lineop.operacao);
            if (ConfereOp(lineop))
            {
                texto.push_back(TI[lineop.operacao]);
                // Mapa de Bits
                mapa_bits.push_back(0);

                if (lineop.operacao == "JMP" || lineop.operacao == "JMPP" || lineop.operacao == "JMPN" || lineop.operacao == "JMPZ")
                {
                    sub = 1;
                }

                if (lineop.operador1 != "" && existe(lineop.operador1, TS) && sub == 0)
                {
                    // Popula o texto
                    texto.push_back(TS[lineop.operador1]);
                    // Popula Mapa de Bits
                    mapa_bits.push_back(1);

                    if (existe(lineop.operador1, TEXTERN))
                    {
                        TU[contador_posicao] = lineop.operador1;
                    }
                }
                else if (lineop.operador1 != "" && existe(lineop.operador1, TS) && sub == 1)
                {
                    // Popula o texto
                    if(flag_end_begin == 0)
                    {
                        texto.push_back( (TS[lineop.operador1] - contador_posicao2) );
                    }
                    else
                    {
                        texto.push_back(TS[lineop.operador1]);
                    }
                    // Popula Mapa de Bits
                    mapa_bits.push_back(1);

                    if (existe(lineop.operador1, TEXTERN))
                    {

                        TU[contador_posicao] = lineop.operador1;
                    }
                }
                else if (lineop.operador1 != "" && !existe(lineop.operador1, TS))
                {
                    cout << "ERRO: Símbolo indefinido (Linha:" << contador_linha << ")" << endl;
                    erro++;
                }

                if (lineop.operador2 != "" && existe(lineop.operador2, TS))
                {
                    // Popula o texto
                    texto.push_back(TS[lineop.operador2]);
                    // Popula Mapa de Bits
                    mapa_bits.push_back(1);
                }
                else if (lineop.operador2 != "" && !existe(lineop.operador2, TS))
                {
                    cout << "ERRO: Simbolo indefinido (Linha:" << contador_linha << ")" << endl;
                    erro++;
                }
            }
            else
            {
                cout << "ERRO: Quantidade incorreta de operandos (Linha:" << contador_linha << ")" << endl;
                erro++;
            }
        }
        else
        {
            if (lineop.operacao != "")
            {
                // Procura operacao na tabela de diretivas
                if (existe(lineop.operacao, TD))
                {
                    if (lineop.operacao == "CONST")
                    {
                        texto.push_back(stoi(lineop.operador1));
                        // Popula Mapa de Bits
                        mapa_bits.push_back(0);
                    }
                    else if (lineop.operacao == "SPACE")
                    {
                        texto.push_back(0);
                        mapa_bits.push_back(0);
                    }
                }
            }
        }
        contador_linha++;
    }
    if (flag_end_begin == 1 && begin_end != 2)
    {
        cout << "ERRO: As diretivas END e BEGIN devem ser devidamente inseridas" << endl;
        erro++;
    }
    else if (flag_end_begin == 0 && begin_end != 0)
    {
        cout << "ERRO: As diretivas END e BEGIN não devem ser inseridas para arquivos sem módulos" << endl;
        erro++;
    }

    imprimeObjeto(arqv, texto, mapa_bits);

    cout << "Arquivo objeto gerado com [" << erro << "] erros." << endl;
    teste.close();
}
