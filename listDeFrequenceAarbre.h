// Ce code convertit la liste triée par fréquence en un arbre binaire de huffman.
// et créer les codes de huffman associées à chaque caractère

#include <stdbool.h>
#include <math.h>

NODE *sortedFrequenceToTree(LIST *list);
void printTree(NODE *node);
void printArray(int arr[], int n);
void convertHuffCodes(NODE *top, int bitsArray[], int etage, DICTIONARY *dictionary, int print);
void putInDictionary(int arr[], int etage, DICTIONARY *dictionary, char character);

void printHuffCodesV2(NODE *top, int arr[], int etage,DICTIONARY* dictionary);


NODE *sortedFrequenceToTree(LIST *list){

    NODE* nodesOfList = list->first;

    //on créer un noeud qui réunit les deux premiers noeuds de la liste
    //on l'ajoute à la liste
    //on trie la liste par fréquence
    //(cela fait office de queue prioritaire)
    //on supprime les deux premiers noeuds de la liste
    //on recommence jusqu'à ce qu'il ne reste qu'un seul noeud
    while (list->size > 1) {

        NODE *node = malloc(sizeof(NODE));

        node->character = '1';
        node->frequency = nodesOfList->frequency + nodesOfList->next->frequency;

        node->left = nodesOfList;
        node->right = nodesOfList->next;

        appendNode(list, node);

        sortList(list);

        removeHead(list);
        removeHead(list);


        nodesOfList = list->first;
    }
    return list->first;
}
//fonction qui affiche l'arbre binaire de huffman avec les fréquences
void printTree(NODE *top){
    if (top == NULL)
        return;

    printTree(top->left);

    if(top->character != '1') {
        if (top->character == '\n') {
            printf("\\n : %d\n", top->frequency);
        } else {
            printf("%c : %d\n", top->character, top->frequency);
        }
    }

    printTree(top->right);
}

//on réutilise le principe utilisée dans le printTree
//sauf qu'ici on garde en mémoire si l'on est allé à gauche ou à droit
//grâce au bitsArray
//si on est allé à gauche, on met un 0 dans le tableau
//si on est allé à droite, on met un 1 dans le tableau
//on fait cela jusqu'à ce qu'on arrive à un noeud qui contient un caractère
//on ajoute alors le caractère et le tableau dans le dictionnaire de huffman grâce
//à la fonction putInDictionary
//on recommence jusqu'à ce qu'on ait parcouru tout l'arbre

void convertHuffCodes(NODE *top, int bitsArray[], int etage, DICTIONARY *dictionary, int print) {
    if (top == NULL)
        return;

    bitsArray[etage] = 0;
    convertHuffCodes(top->left, bitsArray, etage + 1, dictionary,print);

    if(top->character != '1') {
        if(print) {
            if (top->character == '\n') {
                printf("\\n   | ");
            } else {
                printf("%c   | ", top->character);
            }
            printArray(bitsArray, etage );

            printf("\n");
        }

        putInDictionary(bitsArray, etage, dictionary, top->character);

    }

    bitsArray[etage] = 1;
    convertHuffCodes(top->right, bitsArray, etage + 1, dictionary,print);
}


//fonction qui affiche le code de huffman associé à chaque caractère
//si besoin
void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; ++i) {
        printf("%d", arr[i]);
    }
}

//fonction qui ajoute le caractère et le tableau de bits associé
//grâce au tableau arr et à l'étage où l'on se trouve
// dans le dictionnaire de huffman
void putInDictionary(int arr[], int etage, DICTIONARY *dictionary, char character) {
    int index = character-'\n';
    dictionary[index].size = etage;
    dictionary[index].bit = malloc(etage * sizeof(int));

    for (int i = 0; i < etage; ++i){
        dictionary[index].bit[i] = arr[i];
    }
}

// version 2 de printHuffCodes
//void printHuffCodesV2(NODE *top, int arr[], int etage,DICTIONARY* dictionary) {
//    if(top->left){
//        arr[etage] = 0;
//        printHuffCodesV2(top->left, arr, etage + 1, dictionary);
//    }
//
//    if(top->right){
//        arr[etage] = 1;
//        printHuffCodesV2(top->right, arr, etage + 1,dictionary);
//    }
//
//    if(!top->left && !top->right){
//        printf("%c   | ", top->character);
//        printArray(arr, etage);
//        putInDictionary(arr,etage,dictionary,top->character);
//        printf("\n");
//    }
//}