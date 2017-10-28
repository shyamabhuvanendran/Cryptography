#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int c, char **v){

        int key;
        FILE *infile, *outfile;
        char input;
        char freqc[100];
        int freqi[100];
        char encrypted;
        char *infileName, *outfileName;
        int i,j,count;
        int flag;
        int pos, firstpos, secondpos, first, second;

        flag=0;
        if(c<3){
                fprintf(stderr, "please enter input file and output file to execute \n");
                exit(0);
        }

        infileName=v[1];
        outfileName=v[2];
        infile=fopen(infileName,"r");
        outfile=fopen(outfileName,"w");
        i=0;
        input=tolower(fgetc(infile));
        freqc[0]=input;
        freqi[0]= 1;
        i++;

        printf("\nFrequency of each alphabet in the cipher text:\n");
        while((input=tolower(fgetc(infile)))!=EOF){
                if(!isalpha(input)){
                        continue;
                }
                for (j=0;j<i;j++){
                        if(input==freqc[j]){
                                flag=1;
                                pos=j;
                                break;
                        }
                }
                if(flag==1){
                        freqi[pos]+=1;
                        flag=0;
                }
                else{
                        freqc[i]=input;
                        freqi[i]=1;
                        count=i;
                        i++;
                }
        }
        /*for(i=0;i<=count;i++){
                fputc(freqc[i], outfile);
                fprintf(outfile,"%s"," - ");
                fprintf(outfile,"%d",freqi[i]);
                fprintf(outfile,"%s","\n");
                fputc('\n',outfile);
        }       */
        for(i=0;i<=count;i++){
                printf(" %c ",freqc[i]);
                printf("%d\n",freqi[i]);
        }
        first=0;
        firstpos=0;
        second=0;
        secondpos=0;

        for(i=0;i<=count;i++){
                if(isalpha(freqc[i])){
                        if(freqi[i]>first){
                                first=freqi[i];
                                firstpos=i;
                        }
                }
        }

        for(i=0;i<=count;i++){
                if((isalpha(freqc[i])) && i!=firstpos){
                        if(freqi[i]>second){
                                second=freqi[i];
                                secondpos=i;
                        }
                }
        }

        printf("\nMost Frequent character= %c",freqc[firstpos]);
        printf("\nSecond most Frequent character= %c\n\n",freqc[secondpos]);

//      if(freqc[firstpos]-'e'==freqc[secondpos]-'t'){
                key=freqc[firstpos]-'e';
//      }

        printf("\n Key is %d\n\n", key);
        fclose(infile);
        infile=fopen(infileName,"r");


        pos=0;
        i=0;
        while((input=tolower(fgetc(infile)))!=EOF){
                pos=input;
                if(isalpha(input)){
                        pos=pos-96;
                        pos=pos+26-key;
                        if(pos>26){
                                pos=pos%26;
                        }
                        pos=pos+96;

                }

                fprintf(outfile,"%c",pos);
                i++;
        }

         printf("\nOutput is in ceaser_output2.txt file\n \n");


        return 1;
}