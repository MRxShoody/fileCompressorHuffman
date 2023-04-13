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

    sortList(list);

    NODE* top = sortedFrequenceToTree(list);

    //WORKS

    printf("\nimpression de l'arbre\n");
    printTree(top);

    char * arr = malloc(sizeof(int));
    int* dictionaire = repertoireInit();

    printf("\nimpression des codes de huffman\n");
    printHuffCodes(top,arr,0,dictionaire);

    //WIP
    //TODO array d'une structure contenat un array de charactere et un int
    printf("\ntentative de creation d'un dictionnaire\n");
    printRepertoire(dictionaire);

    return 0;
}




