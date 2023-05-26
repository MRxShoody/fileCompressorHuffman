// Ce fichier contient la fonction de compression
// il prend avantage des codes de Huffman g�n�r�s par le programme
// et des bitshifts pour �crire dans le fichier compress�

#include "structures.h"

int compression(FILE* read,FILE* write, DICTIONARY* dictionary);

int compression(FILE* read,FILE* write, DICTIONARY* dictionary){

    char c;
    int index = 0;
    int i;
    int bytes2 = 0;
    unsigned char z = 0b00000000;

    while ((c = fgetc(read)) != EOF) {

        i = 0;

        while (i < dictionary[c - '\n'].size) {

            index++;

            z = z << 1;

            if (dictionary[c - '\n'].bit[i] == 1) {
                z = z | 0b00000001;
            }

            i++;

            if (index % 8 == 0 && index != 0) {

                fwrite(&z, sizeof(unsigned char), 1, write);

                bytes2++;
                index = 0;
                z = 0b00000000;
            }

        }
    }

    if (index != 0) {

        z = z << (8 - index);

        fwrite(&z, sizeof(char), 1, write);

        bytes2++;
    }

    //si le dernier octer n'est pas rempli, on le remplit avec des 0
    //cependant si un code de huffman est du style 000, alors des charact�res inexistants
    //seront ajout�s � la fin du fichier compress�

    fclose(read);
    fclose(write);
    return bytes2;
}