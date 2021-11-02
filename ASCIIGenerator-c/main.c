/*
    Image to ASCII Art Converter

    Author: Leandro Assis dos Santos
    Date: 11 jun 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ImageMagick-7/MagickWand/MagickWand.h>

// Definements
#define OK                  0
#define NUMERO_ARGUMENTOS   3
#define EOS                 '\0'
#define CARACTERES          "$@B8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+<>i!I;:,\"^'. "

// Errors definements
#define ARGUMENTO_INVALIDO      0
#define ERRO_ABRINDO_ARQUIVO    1
#define NOME_INVALIDO           2
#define ARQUIVOPPM_CORROMPIDO   3

int main(int argc, char *argv[])
{
    FILE *imagemOriginal, *imagemSaida;
    unsigned int alturaOriginal, larguraOriginal, valorMaximoEscala;
    uint32_t indiceLinhas, indiceColunas;
    uint16_t indiceArgumento, intensidadeCinza;
    MagickWand *mw = NULL;
    unsigned char intensidadeVermelho, intensidadeVerde, intensidadeAzul;
    char *verificacao, identificador[3];
    float indiceDivisao;
    
    if(argc != NUMERO_ARGUMENTOS)
    {
        printf("Uso incorreto.\n");
        printf("Uso: %s <caminho imagem original> <nome imagem saida>.\n", argv[0]);
        exit(ARGUMENTO_INVALIDO);
    }

    MagickWandGenesis();
    mw = NewMagickWand();
    
    MagickReadImage(mw, argv[1]); // Read the source image

    alturaOriginal = MagickGetImageHeight(mw);
    larguraOriginal = MagickGetImageWidth(mw);

    printf("%d %d\n", alturaOriginal, larguraOriginal);
    if(larguraOriginal > 1024){
        printf("Reconfigurado tamanho.\n");
        alturaOriginal = (1024*alturaOriginal)/larguraOriginal;
        larguraOriginal = 1024;
        MagickResizeImage(mw,larguraOriginal,alturaOriginal,LanczosFilter);
        MagickSetImageCompressionQuality(mw,95);
    }

    MagickWriteImage(mw, "arquivotmp.ppm");

    imagemOriginal = fopen("arquivotmp.ppm", "r");
    imagemSaida = fopen(argv[2], "w");
    if((!imagemOriginal) || (!imagemSaida))
    {
        printf("Erro abrindo os arquivos.\n");
        exit(ERRO_ABRINDO_ARQUIVO);
    }

    fscanf(imagemOriginal, "%s", identificador);
    if(strcmp(identificador,"P6"))
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
//    MagickWriteImage(mw, argv[1]);
    if(mw) mw = DestroyMagickWand(mw);
    fclose(imagemOriginal);
    fclose(imagemSaida);
    MagickWandTerminus();
    system("rm -rf arquivotmp.ppm");
    return OK;
}