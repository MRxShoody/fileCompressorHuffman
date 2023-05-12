#include "sortedFrequencyToTree.h"
#include "fileToFrequency.h"


int main() {
    FILE* file = fopen("texte1.txt", "r");

    int* repertoire = repertoireInit();

    int bytes = charactersFrequency(repertoire, file);

    fclose(file);

    //printDictionary(dictonary);

    LIST* list = listInit();

    for (int i = 0; i < 113; i++) {
        appendToList(list, (char)(i + '\n'), repertoire[i]);
    }

    printRepertoire(repertoire);

    sortList(list);

    NODE* top = sortedFrequenceToTree(list);

    //WORKS

    printf("\nimpression de l'arbre\n");
    printTree(top);

    int* arr = malloc(113*sizeof(int));
    DICTIONARY* dictionary = malloc(113 * sizeof(DICTIONARY));

    printf("\nimpression des codes de huffman");
    printf("\nimpression du dictionnaire operationnel\n");
    printHuffCodes(top,arr,0,dictionary);


    FILE* file1 = fopen("compressedFile.txt", "wb");
    FILE* file2 = fopen("texte1.txt", "r");

    char c;
    int index = 0;
    int i;
    int bytes2 = 0;
    unsigned char z = 0b00000000;

    while ((c = fgetc(file2)) != EOF){


        i = 0;

        while (i < dictionary[c-'\n'].size) {

            if (dictionary[c-'\n'].bit[i] == 1){
                z |= 0b00000001;
            }

            z = z << 1;

            //printf("%d", dictionary[c-'a'].bit[i]);

            i++;

            if (index % 8 == 0 && index != 0) {

                fflush(file1);


                fwrite(&z, sizeof(unsigned char), 1, file1);


                //printf("%c", z);

                bytes2++;
                index = 0;
                z = 0b00000000;
            }


            index++;
        }

    }

    printf("\nbytes : %d", bytes);
    printf("\nbytes2 : %d", bytes2);

    printf("\ncompression rate : ");
    printf("%f", (float)bytes2/(float)bytes);

    return 0;
}




