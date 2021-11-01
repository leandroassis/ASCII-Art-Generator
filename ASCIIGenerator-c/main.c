/*
    Image to ASCII Art Converter

    Author: Leandro Assis dos Santos
    Date: 11 jun 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definements
#define OK                  0
#define NUMERO_ARGUMENTOS   5
#define EOS                 '\0'
#define TAMANHOARQUIVO      256
#define CARACTERES          "$@B8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+<>i!I;:,\"^'. "

// Errors definements
#define ARGUMENTO_INVALIDO      0
#define ERRO_ABRINDO_ARQUIVO    1
#define NOME_INVALIDO           2
#define ARQUIVOPPM_CORROMPIDO   3

// Sys commands auxiliary
#define COPY    " arquivocopia"
#define TEMP    " arquivotmp.ppm"
#define REMOVE  "rm arquivocopia arquivotmp.ppm"

int main(int argc, char *argv[])
{
    FILE *imagemOriginal, *imagemSaida;
    unsigned alturaSaida, larguraSaida, argumento, alturaOriginal, larguraOriginal, valorMaximoEscala;
    unsigned indiceLinhas, indiceColunas;
    unsigned short indiceArgumento, intensidadeCinza;
    unsigned char intensidadeVermelho, intensidadeVerde, intensidadeAzul;
    char *verificacao, CP[275] = "cp ", CONVERT[280] = "convert", identificador[3];
    float indiceDivisao;
    
    if(argc != NUMERO_ARGUMENTOS)
    {
        printf("Uso incorreto.\n");
        printf("Uso: %s <caminho imagem original> <nome imagem saida> <largura da imagem saida> <altura da imagem de saida>.\n", argv[0]);
        exit(ARGUMENTO_INVALIDO);
    }
    
    if((strlen(argv[1]) > TAMANHOARQUIVO) || (strlen(argv[2]) > TAMANHOARQUIVO))
    {
        printf("Nome de um dos arquivos excede o limite.\n");
        printf("Tente trazer os arquivos para um diretorio mais proximo.\n");
        exit(NOME_INVALIDO);
    }

    for(indiceArgumento = 3; indiceArgumento < 5; indiceArgumento++)
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

    system(strcat(strcat(CP, argv[1]), COPY)); // Copy the image in an temporary file
    system(strcat(strcat(CONVERT, COPY), TEMP)); // Convert the image in an .ppm file
    
    imagemOriginal = fopen("arquivotmp.ppm", "r");
    imagemSaida = fopen(argv[2], "w");
    if((!imagemOriginal) || (!imagemSaida))
    {
        printf("Erro abrindo os arquivos.\n");
        exit(ERRO_ABRINDO_ARQUIVO);
    }

    fscanf(imagemOriginal, "%s", identificador);
    if(strcmp(identificador,"P6") != 0)
    {
        printf("O arquivo ppm esta corrompido.\n");
        exit(ARQUIVOPPM_CORROMPIDO);
    }
    
    fscanf(imagemOriginal, "%u %u %u", &larguraOriginal, &alturaOriginal, &valorMaximoEscala);
    indiceDivisao = valorMaximoEscala/strlen(CARACTERES);

    printf("Convertendo...\n");
    for(indiceLinhas = 0; indiceLinhas < alturaOriginal; indiceLinhas++)
    {
        for(indiceColunas = 0; indiceColunas < larguraOriginal; indiceColunas++)
        {
            fscanf(imagemOriginal, "%c%c%c", &intensidadeVermelho, &intensidadeVerde, &intensidadeAzul);
            intensidadeCinza = (unsigned short) (0.3*intensidadeVermelho + 0.59*intensidadeVerde + 0.11*intensidadeAzul);
            fprintf(imagemSaida, "%c", CARACTERES[(int)(intensidadeCinza/indiceDivisao)]);
        }
        fprintf(imagemSaida, "\n");
    }

    printf("Convertido com sucesso.\n");
    system(REMOVE); // Clean the temporary files
    fclose(imagemOriginal);
    fclose(imagemSaida);
    return OK;
}