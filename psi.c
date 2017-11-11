//This program calculates the Psi value of single letters

#include<stdio.h>
#include<stdlib.h>

int main(int c, char **v){

        int *freqi;
        float *m;
        char *freqc;
        char *infileName;
        char input;
        float psi;
        int i,j,flag,pos,total;
        int size, totalChars;
	FILE *infile;
	
	totalChars=0;
	infileName=v[1];
        infile=fopen(infileName,"r");

	while((input=fgetc(infile))!=EOF){
		totalChars++;
	}

        freqi=malloc(totalChars*sizeof(int));
        freqc=malloc(totalChars*sizeof(char));
        rewind(infile);
        flag=0;
        pos=0;
        i=0;
        j=0;
        total=0;
        input=tolower(fgetc(infile));
        freqi[0]=1;
        freqc[0]=input;
        i++;
        psi=0.0;
        while((input=tolower(fgetc(infile)))!=EOF){
		if(isalpha(input)){
                for(j=0;j<i;j++){
                        if(input==freqc[j]){
                                flag=1;
                                pos=j;
                                break;
                        }
                }
                if(flag==1){
                        freqi[pos]=freqi[pos]+1;
                        flag=0;
                }
                else{
                        freqi[i]=1;
                        freqc[i]=input;
                        i++;
                }
		}
        }
        for(j=0;j<i;j++){
                total+=freqi[j];
        }
        m=malloc(i*sizeof(float));
        for(j=0;j<i;j++){
                m[j]=((float)(freqi[j])/(float)total);
        }

	for(j=0;j<i;j++){
                psi+=(m[j]*m[j]);
        }        

        free(m);
        free(freqi);
        free(freqc);
        printf("\n psi: %f\n", psi);

}


