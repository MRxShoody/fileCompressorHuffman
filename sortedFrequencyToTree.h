#include <stdbool.h>
#include "sortFrequency.h"
#include "math.h"

//Dans cette étape, je vais convertir ma liste chainée triée en arbre binaire de huffman


//renvoie le haut de l'arbre
NODE *sortedFrequencyToTree(LIST *list);
void printTree(NODE *node);
void printArray(int arr[], int n);
void printHuffCodes(NODE *top, int bitsArray[], int etage, DICTIONARY* dictionary);
void putInDictionary(int* arr, int etage,DICTIONARY* dictionary,char character);


void printHuffCodesV2(NODE *top, int arr[], int etage,DICTIONARY* dictionary);


NODE *sortedFrequenceToTree(LIST *list){

    NODE* nodesOfList = list->first;

    while (list->size > 1) {

        NODE *node = malloc(sizeof(NODE));

        node->character = '1';
        node->frequency = nodesOfList->frequency + nodesOfList->next->frequency;

        node->left = nodesOfList;
        node->right = nodesOfList->next;

        appendNode(list, node);

        sortList(list);

        //debuggage
/*      printf("\n");
        printList(list);*/

        removeHead(list);
        removeHead(list);


        nodesOfList = list->first;

    }
    return list->first;
}

void printTree(NODE *top){
    if (top == NULL)
        return;

    printTree(top->left);

    if(top->character != '1')
        printf("%c : %d\n", top->character, top->frequency);

    printTree(top->right);
}



void printHuffCodes(NODE *top, int* bitsArray, int etage, DICTIONARY* dictionary) {
    if (top == NULL)
        return;

    bitsArray[etage] = 0;
    printHuffCodes(top->left, bitsArray, etage + 1, dictionary);

    if(top->character != '1') {
        printf("%c   | ", top->character);
        printArray(bitsArray, etage );
        putInDictionary(bitsArray,etage,dictionary,top->character);
        printf("\n");
    }

    bitsArray[etage] = 1;
    printHuffCodes(top->right, bitsArray, etage + 1, dictionary);
}



void printHuffCodesV2(NODE *top, int arr[], int etage,DICTIONARY* dictionary) {
    if(top->left){
        arr[etage] = 0;
        printHuffCodesV2(top->left, arr, etage + 1, dictionary);
    }

    if(top->right){
        arr[etage] = 1;
        printHuffCodesV2(top->right, arr, etage + 1,dictionary);
    }

    if(!top->left && !top->right){
        printf("%c   | ", top->character);
        printArray(arr, etage);
        putInDictionary(arr,etage,dictionary,top->character);
        printf("\n");
    }
}

void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; ++i) {
        printf("%d", arr[i]);
    }
}

void putInDictionary(int arr[], int etage, DICTIONARY* dictionary, char character){
    int index = character-'a';
    dictionary[index].size = etage;
    dictionary[index].bit = malloc(etage * sizeof(int));

    printf("\ndictionary for %c array : ", character);

    for (int i = 0; i < etage; ++i){
        printf("%d", arr[i]);
        dictionary[index].bit[i] = arr[i];
    }
}