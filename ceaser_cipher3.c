#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int c, char **v){

        int key;
        FILE *infile, *outfile, *outfileIn;
        char input;
        char freqc[100];
        int freqi[100];
        char encrypted;
        char *infileName, *outfileName;
        int i,j,count;
        int flag;
        int pos, firstpos, secondpos, first, second;
        char mostFreq=' ';
        char int_names[50];

        key=atoi(v[1]);
        printf("\nEntered key is %d\n\n", key);
        infileName=v[2];
        outfileName=v[3];
        infile=fopen(infileName,"r");
        //int_names="ceaser_output3_int"+char(1)+".txt";
        outfileIn=fopen("ceaser_output3_int.txt","w+");
        outfile=fopen(outfileName,"w+");

        pos=0;
        i=0;
        count=0;
         printf("\nEncrypting with the entered key\n");
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
                fprintf(outfileIn,"%c",pos);
                i++;
        }
        rewind(outfileIn);
        while(1){
        i=0;
        count=0;
        pos=0;
        input=tolower(fgetc(outfileIn));
        freqc[0]=input;
        freqi[0]= 1;
        i++;
        while((input=tolower(fgetc(outfileIn)))!=EOF){
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
        first=freqi[0];
        for(i=1;i<=count;i++){
                if(isalpha(freqc[i])){
                        if(freqi[i]>first){
                                first=freqi[i];
                                firstpos=i;
                        }
                }
        }
        mostFreq=freqc[firstpos];
        printf("\nmost frequent letter = %c\n", mostFreq);
        rewind(outfileIn);
        if(mostFreq=='e'){
                printf("\n\nMost frequent letter is 'e'. Stopping encryption.\n\n");
                break;
        }
        printf("\nMost frequent letter not 'e'. Encrypting with the same key again.\n");
        while((input=tolower(fgetc(outfileIn)))!=EOF){
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
        rewind(outfile);
        fclose(outfileIn);
        fclose(outfile);
        outfile=fopen("ceaser_output3_Int.txt","w+");
        outfileIn=fopen(outfileName,"r+");
        }

        printf("\nOutput is in ceaser_output3.txt file\n \n");


        return 1;
}