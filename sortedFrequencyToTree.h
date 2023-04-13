#include "sortFrequency.h"
#include "math.h"

//Dans cette étape, je vais convertir ma liste chainée triée en arbre binaire de huffman


//renvoie le haut de l'arbre
NODE *sortedFrequencyToTree(LIST *list);
void printTree(NODE *node);
void printArray(int arr[], int n);
void printHuffCodes(NODE *top, int arr[], int etage, int* dictonary);
void putInDictionary(int* dictonary, char character, int n, int *arr);


void printHuffCodesV2(NODE *top, int arr[], int etage);


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



void printHuffCodes(NODE *top, int arr[], int etage, int* dictonary) {
    if (top == NULL)
        return;

    arr[etage] = 0;
    printHuffCodes(top->left, arr, etage + 1,dictonary);

    if(top->character != '1') {
        printf("%c   | ", top->character);
        printArray(arr, etage );
        putInDictionary(dictonary, top->character, etage,arr);
    }

    arr[etage] = 1;
    printHuffCodes(top->right, arr, etage + 1,dictonary);
}



void printHuffCodesV2(NODE *top, int arr[], int etage) {
    if(top->left){
        arr[etage] = 0;
        printHuffCodesV2(top->left, arr, etage + 1);
    }

    if(top->right){
        arr[etage] = 1;
        printHuffCodesV2(top->right, arr, etage + 1);
    }

    if(!top->left && !top->right){
        printf("%c   | ", top->character);
        printArray(arr, etage);
    }
}

void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);

    printf("\n");
}

//WIP

void putInDictionary(int* dictonary, char character, int n, int* arr){
    int i;
    for (i = 0; i<n;++i){
        dictonary[character-'a'] = 10 * dictonary[character-'a'] + arr[i];
    }
}