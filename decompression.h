// Ce fichier contient la fonction de decompression
// il prend avantage de l'arbre binaire de huffman
// et des bitshifts decrypter le fichier compress�

void decompress(FILE* read, FILE* write, NODE* top);

void decompress(FILE* read, FILE* write, NODE* top){

    NODE* temp = top;
    int readchar;
    while((readchar = fgetc(read)) != EOF) {

        for (int m = 7; m >= 0; m--) {

            //il lit bit par bit et se d�place dans l'arbre
            //jusqu'� ce qu'il trouve un charact�re
            //si le bit est 0, il se d�place � gauche
            //si le bit est 1, il se d�place � droite

            if(((readchar >> m) & 1) == 0){
                top = top->left;
            } else {
                top = top->right;
            }

            if(top->character != '1') {

                fwrite(&top->character, sizeof(char), 1, write);
                top = temp;

            }
        }
    }

    fclose(write);
    fclose(read);
}