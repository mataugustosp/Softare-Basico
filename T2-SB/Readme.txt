Trabalho 2 desenvolvido por: Matheus Augusto Silva Pinho (18/0024906)

- ALERTA AO MONITOR: Após a revisão do meu "Trabalho 1" com o professor Bruno, descobriu-se uma incompatibilidade 
do meu programa desenvolvido em MACOS com as máquinas Linux e Windows, portanto, de acordo com o professor,
a correção do meu trabalho deve ser feita junto a mim, com o programa rodando em meu computador.

COMO COMPILAR O TRABALHO:

g++ -std=c++11 source/main.cpp source/utils.cpp source/montador.cpp source/simulador.cpp  source/ligador.cpp -o montador

COMO TESTAR O TRABALHO:

- A fim de testar seu código em pseudo assembly, insira o seu arquivo com a extensão ".asm" diretamente na pasta "Input" do trabalho. 

MONTADOR

- Após a inserção do arquivo na pasta e a devida compilação do trabalho, utilize o comando:

./montador [nome do seu arquivo].asm [nome do seu arquivo 2].asm [nome do seu arquivo 3].asm 

- "nome do seu arquivo" deve ser substituído pelo nome do arquivo que você inseriu na pasta "Input"
- Após este processo, a saída do montador estará presente na pasta "Output" como [nome do seu arquivo].obj

LIGADOR
 - O Ligador será gerado automaticamente após o montador na pasta OUTPUT com o nome de ligador.obj

SIMULADOR

- Para rodar o simulador, utilize o seguinte comando no terminal:

./montador [nome do seu arquivo].obj

- "nome do seu arquivo" deve ser substituído pelo nome do arquivo que você inseriu inicialmente na pasta "Input"
- Após este processo, a saída do simulador estará presente na pasta "Output" como "saida.out"
