#include "sortedFrequencyToTree.h"
#include "fileToFrequency.h"


int main() {
    FILE* file = fopen("texte2.txt", "r");

    int* repertoire = repertoireInit();

    charactersFrequency(repertoire, file);

    fclose(file);

    //printDictionary(dictonary);

    LIST* list = listInit();

    for (int i = 0; i < 26; i++) {
        appendToList(list, (char)(i + 'a'), repertoire[i]);
    }

    printRepertoire(repertoire);

    sortList(list);

    NODE* top = sortedFrequenceToTree(list);

    //WORKS

    printf("\nimpression de l'arbre\n");
    printTree(top);

    int* arr = malloc(26*sizeof(int));
    DICTIONARY* dictionary = malloc(26* sizeof(DICTIONARY));

    printf("\nimpression des codes de huffman");
    printf("\nimpression du dictionnaire operationnel\n");
    printHuffCodes(top,arr,0,dictionary);


    FILE* file1 = fopen("compressedFile.txt", "wb");

    FILE* file3 = fopen("texte2.txt", "r");
    char c;
    int index = 0;
    unsigned char z = 0x00;
    while ((c = fgetc(file3)) != EOF) {

        //printf("%c",c);
        int i = 0;

        while (i < dictionary[c-'a'].size) {

            if (dictionary[c-'a'].bit[index] == 1){
                z |= 1 << index;
            } else {
                z = z << 1;
            }
            i++;

            //printf("%d",index);

            if (index % 8 == 0) {

                printf("%x", z);
                index = 0;
                z = 0x00;
            }
            index++;
        }
    }

    return 0;
}




