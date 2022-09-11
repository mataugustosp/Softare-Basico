Trabalho desenvolvido por: Matheus Augusto Silva Pinho (18/0024906)


COMO COMPILAR O TRABALHO:

g++ -std=c++11 source/main.cpp source/utils.cpp source/montador.cpp source/simulador.cpp  -o montador

COMO TESTAR O TRABALHO:

- A fim de testar seu código em pseudo assembly, insira o seu arquivo com a extensão ".asm" diretamente na pasta "Input" do trabalho. 

MONTADOR

- Após a inserção do arquivo na pasta e a devida compilação do trabalho, utilize o comando:

./montador [nome do seu arquivo].asm 

- "nome do seu arquivo" deve ser substituído pelo nome do arquivo que você inseriu na pasta "Input"
- Após este processo, a saída do montador estará presente na pasta "Output" como [nome do seu arquivo].obj


SIMULADOR

- Para rodar o simulador, utilize o seguinte comando no terminal:

./montador [nome do seu arquivo].obj

- "nome do seu arquivo" deve ser substituído pelo nome do arquivo que você inseriu inicialmente na pasta "Input"
- Após este processo, a saída do simulador estará presente na pasta "Output" como "saida.out"
