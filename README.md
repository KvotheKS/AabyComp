# Simple Compilador
    Compilador para a matéria Compiladores 2023/1
## Integrantes 
-   Alexsander Correa de Oliveira
-   Bruno Abreu Kamienski 
-   Karen Lima Macêdo
-   Marco Antonio Souza de Athayde

## Fase final - Gerador de Código
    Para rodar o nosso programa, sugerimos que seja utilizado o WinFlex no windows, que contém tanto a versão mais recente do bison quanto a do flex. Além disso, sugerimos também que o compilador utilizado seja o tdm-gcc64, dado que ele vem com uma versão relativamente recente do mingw, aliado também ao mingw32-make, que é necessário para compilar o programa.

## Como compilar
    Na pasta base do projeto, use o mingw32-make.

## Como rodar
    Após a compilação, um executavel chamado parser é gerado. O programa recebe 2 parametros separados: o arquivo de input e o de output.
    Exemplo:
        
        parser ./Testes/test001.txt ./AabyExemplo.s

    O arquivo output está escrito em RISCV. Para rodar ele, basta rodarmos o FPGRARS com o input sendo o output do nosso programa.
    Exemplo:
        fpgrars ./AabyExemplo.s

    Adendo: As funções READ/WRITE no fpgrars interagem com o terminal e NÃO com a tela criada pelo programa.