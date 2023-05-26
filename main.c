#include "compression.h"
#include "fileToFrequency.h"
#include "sortFrequency.h"
#include "sortedFrequencyToTree.h"
#include "decompression.h"
#include "string.h"


float printCompressionRate(int byte1,int byte2);

// FORMAT :
// compress (encode|decode) <input file> <output file>
// compress stat <compressed file>

//EXEMPLES
// compress encode texte1.txt compressed.txt
// compress decode compressed.txt decompressed.txt
// compress stat compressed.txt

int main() {

    /*********************************************************************************************************************
    * DRIVER CODE
    ********************************************************************************************************************/

    int running = true;

    while(running){
    char prompt[100];
    printf("Enter prompt: ");

    fgets(prompt, sizeof(prompt), stdin);
    prompt[strcspn(prompt, "\n")] = '\0';
    char *token = strtok(prompt, " ");

    if(strcmp(token,"exit") == 0) {
        exit(0);
    }
    if (strcmp(token, "compress") != 0) {
        printf("Invalid prompt\n");
        continue;
    }

    char *action = strtok(NULL, " ");
    char *infile = strtok(NULL, " ");
    char *outfile = strtok(NULL, " ");

    if (action == NULL) {
        printf("Invalid prompt\n");
        continue;
    }

    /*********************************************************************************************************************
     * COMPRESSION
     ********************************************************************************************************************/

    if(strcmp(action,"encode") == 0){

        if (infile == NULL || outfile == NULL) {
            printf("Invalid prompt\n");
            continue;
        }

        int* repertoire = repertoireInit();

        FILE* file = fopen(infile, "r");

        if (file == NULL) {
            printf("infile does not exist\n");
            continue;
        }

        int bytes = charactersFrequency(repertoire, file);

        LIST* list = listInit(repertoire);

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

        float cr = printCompressionRate(bytes,bytes2);

        char prefix[100] = "encoded";
        char newoutfile[100];
        strcpy(newoutfile, prefix);
        strcat(newoutfile, outfile);

        FILE* f = fopen(newoutfile,"w");
        repertoireToFile(repertoire, f,cr);

        free(repertoire);
        free(list);
        free(top);
        free(arr);
        free(dictionary);

        printf("Compression successful\n");

        continue;
    }

    /*********************************************************************************************************************
     * DECOMPRESSION
     ********************************************************************************************************************/

    if(strcmp(action,"decode") == 0){

        if (infile == NULL || outfile == NULL) {
            printf("Invalid prompt\n");
            continue;
        }

        FILE* file1 = fopen(infile, "rb");

        if (file1 == NULL) {
            printf("infile does not exist\n");
            continue;
        }

        FILE* file2 = fopen(outfile, "w");

        char prefix[100] = "encoded";
        char newoutfile[100];
        strcpy(newoutfile, prefix);
        strcat(newoutfile, infile);

        FILE* f = fopen(newoutfile,"r");

        if (f == NULL) {
            printf("Encoded file not here. Please re-encode the desired file\n");
            continue;
        }

        int* repertoire = repertoireInit();

        fileToRepertoire(repertoire, f);

        LIST* list = listInit(repertoire);

        sortList(list);

        NODE* top = sortedFrequenceToTree(list);

        decompress(file1,file2,top);

        free(repertoire);
        free(list);
        free(top);

        printf("Decompression successful\n");
        continue;
    }

    /*********************************************************************************************************************
     * STAT
     ********************************************************************************************************************/

        if(strcmp(action,"stat") == 0) {

        if (infile == NULL) {
            printf("infile does not exist\n");
            continue;
        }

        char prefix[100] = "encoded";
        char newoutfile[100];
        strcpy(newoutfile, prefix);
        strcat(newoutfile, infile);

        FILE *file = fopen(newoutfile, "r");
        if (file == NULL) {
            printf("Encoded file not here. Please re-encode the desired file\n");
            continue;
        }

        int *repertoire = repertoireInit();

        float cr = fileToRepertoire(repertoire, file);

        LIST *list = listInit(repertoire);

        sortList(list);

        NODE *top = sortedFrequenceToTree(list);

        int *arr = malloc(113 * sizeof(int));

        DICTIONARY *dictionary = malloc(113 * sizeof(DICTIONARY));

        convertHuffCodes(top, arr, 0, dictionary, true);

        printf("\nCompression rate : %0.2f\n", cr);

        free(repertoire);
        free(list);
        free(arr);
        free(top);
        free(dictionary);

        continue;
        }
    }
}

float printCompressionRate(int byte1,int byte2){

    //printf("compression rate : %0.2f \n", ((float)byte1/(float)byte2));

    return (float)byte1/(float)byte2;
}



