'''
Image to ASCII Art Converter

Author: Leandro Assis dos Santos
Date: 11 jun 2021
'''

from PIL import Image, ImageDraw, ImageFont

caracteres = list("$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ")
indiceDivisao = 256/len(caracteres)
larguraCaracter = 10
alturaCaracter = 18

fotoOriginal = input("Insira o nome da foto a ser convertida: ")
dimensoesDestino = input("Insira as dimensoes da figura de destino:\nex: 200(largura), 100(altura) ").split(", ")

try:
    imagem = Image.open(fotoOriginal)
    arquivoSaida = open("foto.txt", "w")
except:
    print("Verifique os arquivos de entrada.")
    exit(FileNotFoundError)

larguraOriginal, alturaOriginal = imagem.size
if len(dimensoesDestino) != 2:
    print("Usando as dimensoes originais da imagem.")
    alturaDestino = alturaOriginal
    larguraDestino = larguraOriginal
else:
    try:
        dimensoesDestino[0] = int(dimensoesDestino[0])
        dimensoesDestino[1] = int(dimensoesDestino[1])
    except:
        print("Valores invalidos passados para largura e altura da imagem de destino")
        exit(ValueError)

    fatorProporcao = larguraOriginal/alturaOriginal
    larguraDestino = int(fatorProporcao*dimensoesDestino[1])
    alturaDestino = dimensoesDestino[1]
    if larguraDestino != dimensoesDestino[0]:
        print("Dimensoes inseridas nao permitirão uma imagem proporcional.")
        print(f"Será feita a conversão para {larguraDestino}x{dimensoesDestino[1]}.\n")
    imagem = imagem.resize((larguraDestino, alturaDestino), Image.BICUBIC)

print("Convertendo...")
pixels = imagem.load()
imagemSaida = Image.new(mode="RGB", size=(larguraDestino*larguraCaracter, alturaDestino*alturaCaracter), color=(0,0,0))
imagemDesenho = ImageDraw.Draw(imagemSaida)

for i in range(alturaDestino):
    for j in range(larguraDestino):
        intensidadeVermelho, intensidadeVerde, intensidadeAzul = pixels[j, i]
        gray = int(0.3*intensidadeVermelho + 0.59*intensidadeVerde + 0.11*intensidadeAzul)
        pixels[j, i] = (gray, gray, gray)
        arquivoSaida.write(caracteres[int(gray/indiceDivisao)])
        imagemDesenho.text((j*larguraCaracter, i*alturaCaracter),caracteres[int(gray/indiceDivisao)])
        #imagemDesenho.text((j*larguraCaracter, i*alturaCaracter),caracteres[int(gray/indiceDivisao)], fill=(intensidadeVermelho, intensidadeVerde, intensidadeAzul))
        #Imagem de saida com caracteres coloridos
    arquivoSaida.write("\n")    

imagemSaida.save("foto.png")
print("Convertido com sucesso")