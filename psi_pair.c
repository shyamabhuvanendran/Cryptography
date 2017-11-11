//This program calculates the Psi value of pairs of letters

#include<stdio.h>
#include<stdlib.h>

int main(int c, char **v){

        FILE *infile;

        int freqi[1000];
        float m[1000];
        char *infileName;
        char input1, input2;
        float psi;
        int i,j,flag,pos, total;
        char freqc[1000][2];
        infileName=v[1];
        infile=fopen(infileName,"r");
        flag=0;
        pos=0;
        i=0;
        j=0;
        total=0;
        input1=tolower(fgetc(infile));
        freqi[0]=1;
        freqc[0][0]=input1;
        input2=tolower(fgetc(infile));
        freqc[0][1]=input2;
        i++;
        psi=0.0;

        while((input1=tolower(fgetc(infile)))!=EOF){
            	if(isalpha(input1)){
		while((input2=tolower(fgetc(infile)))!=EOF){
			if(isalpha(input2)){
				break;
			}
		}

		if(input2==EOF){
			break;
		}
		
                for(j=0;j<i;j++){
                        if(input1==freqc[j][0]){
                                if(input2==freqc[j][1]){
                                        flag=1;
                                        pos=j;
                                        break;
                                }
                        }
                }
                if(flag==1){
                        freqi[pos]=freqi[pos]+1;
                        flag=0;
                }
                else{
                        freqi[i]=1;
                        freqc[i][0]=input1;
                        freqc[i][1]=input2;
                        i++;
                }
		}
	}
        /*for(j=0;j<i;j++){
                printf("\n%c%c: ",freqc[j][0],freqc[j][1]);
                printf("%d \n",freqi[j]);
        }*/

        for(j=0;j<i;j++){
                total+=freqi[j];
        }
        //printf("\nTotal Characters= %d",total);
        for(j=0;j<i;j++){
                m[j]=((float)(freqi[j])/(float)total);
                //printf("\nm[j] %f",m[j]);
        }


        for(j=0;j<i;j++){
                psi+=(m[j]*m[j]);
        }

        printf("\nPsi Pair= %f\n", psi);

}



