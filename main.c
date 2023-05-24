#include "compression.h"
#include "fileToFrequency.h"
#include "sortFrequency.h"
#include "sortedFrequencyToTree.h"
#include "decompression.h"
#include "string.h"


void printCompressionRate(int byte1,int byte2);

// FORMAT :
// compress (encode|decode) <input file> <output file>
// compress stat <compressed file>

//EXEMPLES
// compress encode texte1.txt compressed.txt
// compress decode compressed.txt decompressed.txt
// compress stat compressed.txt

//TODO: ERROR HANDLING (invalid file, etc)

int main() {

    char prompt[100];
    printf("Enter prompt: ");
    fgets(prompt, sizeof(prompt), stdin);
    prompt[strcspn(prompt, "\n")] = '\0'; // remove newline character
    char *token = strtok(prompt, " ");

    if(strcmp(token,"exit") == 0) {
        exit(0);
    }
    if (strcmp(token, "compress") != 0) {
        printf("Invalid prompt\n");
        main();
    }

    char *action = strtok(NULL, " ");
    char *infile = strtok(NULL, " ");
    char *outfile = strtok(NULL, " ");


    if (action == NULL) {
        printf("Invalid prompt\n");
        main();
    }
//    printf("Action: %s\n", action);
//    printf("Input files: %s\n", infile);
//    printf("Output files: %s\n", outfile);

    if(strcmp(action,"encode") == 0){

        if (infile == NULL || outfile == NULL) {
            printf("Invalid prompt\n");
            main();
        }

        int* repertoire = repertoireInit();


        FILE* file = fopen(infile, "r");
        int bytes = charactersFrequency(repertoire, file);

        LIST* list = listInit(repertoire);


        char prefix[100] = "encoded";
        char newoutfile[100];
        strcpy(newoutfile, prefix);
        strcat(newoutfile, outfile);
        //printf("New outfile: %s\n", newoutfile);


        FILE* f = fopen(newoutfile,"w");
        repertoireToFile(repertoire, f);
        //printRepertoire(repertoire);


        sortList(list);

        NODE* top = sortedFrequenceToTree(list);


        //printf("\nimpression de l'arbre\n");
        //printTree(top);

        int* arr = malloc(113*sizeof(int));
        DICTIONARY* dictionary = malloc(113 * sizeof(DICTIONARY));


        convertHuffCodes(top, arr, 0, dictionary, false);


        FILE* file1 = fopen(outfile, "wb");
        FILE* file2 = fopen(infile, "r");

        int bytes2 = compression(file2,file1,dictionary);

        printCompressionRate(bytes,bytes2);


        main();
    }

    if(strcmp(action,"decode") == 0){

        if (infile == NULL || outfile == NULL) {
            printf("Invalid prompt\n");
            main();
        }

        if (action == NULL || infile == NULL || outfile == NULL) {
            printf("Invalid prompt\n");
            main();
        }

        FILE* file1 = fopen(infile, "rb");
        FILE* file2 = fopen(outfile, "w");


        char prefix[100] = "encoded";
        char newoutfile[100];
        strcpy(newoutfile, prefix);
        strcat(newoutfile, infile);
        //printf("New outfile: %s\n", newoutfile);


        FILE* f = fopen(newoutfile,"r");
        int* repertoire = repertoireInit();
        fileToRepertoire(repertoire, f);

        LIST* list = listInit(repertoire);

        sortList(list);

        NODE* top = sortedFrequenceToTree(list);

        decompress(file1,file2,top);

        main();
    }

    if(strcmp(action,"stat") == 0) {

        if (infile == NULL) {
            printf("Invalid prompt\n");
            main();
        }

        char prefix[100] = "encoded";
        char newoutfile[100];
        strcpy(newoutfile, prefix);
        strcat(newoutfile, infile);


        FILE *file = fopen(newoutfile, "r");
        int *repertoire = repertoireInit();
        fileToRepertoire(repertoire, file);
        LIST *list = listInit(repertoire);

        sortList(list);

        NODE *top = sortedFrequenceToTree(list);

        int *arr = malloc(113 * sizeof(int));
        DICTIONARY *dictionary = malloc(113 * sizeof(DICTIONARY));

        convertHuffCodes(top, arr, 0, dictionary, true);

        main();
    }
}

void printCompressionRate(int byte1,int byte2){

    //printf("\nbytes : %d", byte1);
    //printf("\nbytes2 : %d", byte2);

    printf("compression rate : %0.2f \n", ((float)byte1/(float)byte2));
}



