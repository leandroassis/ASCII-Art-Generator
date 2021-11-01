# ASCII Art Generator
### Author: Leandro Assis
### Date: 11 jun 2021
#### Note: Ins't complete yet. That are some changes and improvements to be done in c code.

# Introduction

This is an ASCII Art Generator made both in C and Python. Basicaly the user give an input image file and the script creates an output image in ASCII art by changing the pyxel's colors for characters. In the current version it works better with smallers image.

Note: This project isn't optimezed, so the scripts (principally the python one) can slow down or even crash the pc. I'll improve the perfomance some day :p

# Requirements

- Python:
    Only uses the PIL library.

- C:
    ImageMagick is required.

# Usage:

To use the python application you just have to run "python3 main.py" and answer the questions with your desired image informations.
To use the C application you first have to compile it, and than run:
    "[.exe output file] [path to image] [path to output file] [image lenght] [image height]"