/*
    Conversor de imagens em ASCII Art

    Author: Leandro Assis dos Santos
    Date: 11 jun 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicao de Diretivas
#define OK                  0
#define NUMERO_ARGUMENTOS   5
#define EOS                 '\0'

// Definicao de Erros
#define ARGUMENTO_INVALIDO      0
#define ERRO_ABRINDO_ARQUIVO    1


int main(int argc, char *argv[])
{
    FILE *imagemOriginal, *imagemSaida;
    unsigned alturaSaida, larguraSaida, argumento;
    unsigned short indiceArgumento;
    char *verificacao, *cp = "cp ", *convert = "convert ";
    
    if(argc != NUMERO_ARGUMENTOS)
    {
        printf("Uso incorreto.\n");
        printf("Uso: %s <caminho imagem original> <nome imagem saida> <largura da imagem saida> <altura da imagem de saida>.\n", argv[0]);
        exit(ARGUMENTO_INVALIDO);
    }

    for(indiceArgumento = 3; indiceArgumento <= 4; indiceArgumento++)
    {
        argumento = (unsigned) strtoul(argv[indiceArgumento], &verificacao, 10);
        if(*verificacao != EOS)
        {
            printf("Argumento %c invalido na posicao %u.\n", *verificacao, indiceArgumento);
            exit(ARGUMENTO_INVALIDO);
        }
        if(indiceArgumento == 3) larguraSaida = argumento;
        else if(indiceArgumento == 4) alturaSaida = argumento;
    }

    system("convert gaia.jpeg saida.ppm");
    /*
    system(strcat(strcat(cp, argv[1]), " copia.jpeg"));
    system(strcat(strcat(convert, argv[1]), " imagemOriginal.ppm"));
    */
    //system("convert %s imagemOriginal.ppm", argv[1]);

    imagemOriginal = fopen(argv[1], "r");
    imagemSaida = fopen(argv[2], "w");
    if((!imagemOriginal) || (!imagemSaida))
    {
        printf("Erro abrindo os arquivos.\n");
        exit(ERRO_ABRINDO_ARQUIVO);
    }
    
    return OK;
}