//This program encrypts an input file with an entered key to produce a ceaser cipher.

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main(int c, char **v){

        int key;
        FILE *infile, *outfile;
        char input;
        char encrypted;
        char *infileName, *outfileName;
        int pos,i;

        if(c<4){
                fprintf(stderr, "please enter key, input file and output file to execute \n");
                exit(0);
        }

        key=atoi(v[1]);
        printf("key %d ",key);

        infileName=v[2];
        outfileName=v[3];

        infile=fopen(infileName,"r");
        outfile=fopen(outfileName,"w");

        while((input=tolower(fgetc(infile)))!=EOF){
                pos=input;
                if(isalpha(input)){
                        pos=pos-96;
                        pos=pos+key;
                        if(pos>26){
                                pos=pos%26;
                        }
                        pos=pos+96;

                }

                fprintf(outfile,"%c",pos);
                i++;
        }

        printf("\nEncrypted text is in the output file.\n\n ");

        return 1;
}
