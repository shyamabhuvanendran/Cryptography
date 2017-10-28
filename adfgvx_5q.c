#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float phi(FILE *infile, int total){
        int *freqi;
        float *m;
        char *freqc;
        char *infileName;
        char input;
        float *phi;
	float phiVal;
        int i,j,flag,pos;
	int size;

        freqi=malloc(total*sizeof(int));
	freqc=malloc(total*sizeof(char));
	rewind(infile);
        flag=0;
        pos=0;
        i=0;
        j=0;
        input=tolower(fgetc(infile));

        freqi[0]=1;
        freqc[0]=input;
        i++;
        phiVal=0.0;

        while((input=tolower(fgetc(infile)))!=EOF){
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

	m=malloc(i*sizeof(float));
        for(j=0;j<i;j++){
                m[j]=((float)(freqi[j])/(float)total);
        }

        for(j=0;j<i;j++){
                phiVal+=m[j]*(m[j]- (1.0/(float)total));
        }
	free(m);
	free(freqi);
	free(freqc);
        //printf("\n phi: %f\n", phiVal);
	return phiVal;
}


float phiPair(FILE *infile, int total){

        int *freqi;
        float *m;
        char input1, input2;
        float phipair;
        int i,j,flag,pos;
        char **freqc;

        flag=0;
        pos=0;
        i=0;
        j=0;

        m=malloc(total*sizeof(float));
        freqi=malloc(total*sizeof(int));
        freqc=malloc(total*sizeof(char*));

        for(j=0;j<total;j++){
                freqc[j]=malloc(2*sizeof(char));
        }

        input1=tolower(fgetc(infile));
        freqi[0]=1;
        freqc[0][0]=input1;
        input2=tolower(fgetc(infile));
        freqc[0][1]=input2;
        i++;
        phipair=0.0;


        while((input1=tolower(fgetc(infile)))!=EOF){
                input2=tolower(fgetc(infile));
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
        for(j=0;j<i;j++){
                m[j]=((float)(freqi[j])/(float)total);
        }


        for(j=0;j<i;j++){
                phipair+=m[j]*(m[j]- (1.0/(float)total));
        }

	//printf("\nPhi Pair= %f\n", phipair);
        free(freqc);
        free(m);
        free(freqi);
        return phipair;
        
}



float phiThree(FILE *infile, int total){

        int *freqi;
        float *m;
        char input1, input2, input3;
        float phith;
        int i,j,flag,pos;
        char **freqc;

        flag=0;
        pos=0;
        i=0;
        j=0;

        m=malloc(total*sizeof(float));
        freqi=malloc(total*sizeof(int));
        freqc=malloc(total*sizeof(char*));

        for(j=0;j<total;j++){
                freqc[j]=malloc(3*sizeof(char));
        }

        input1=tolower(fgetc(infile));
        freqi[0]=1;
        freqc[0][0]=input1;
        input2=tolower(fgetc(infile));
        freqc[0][1]=input2;
		input3=tolower(fgetc(infile));
		freqc[0][2]=input3;
        i++;
        phith=0.0;


        while((input1=tolower(fgetc(infile)))!=EOF){
                input2=tolower(fgetc(infile));
                if(input2==EOF){
                        break;
                }
		
		input3=tolower(fgetc(infile));
		if(input3==EOF){
			break;
		}

                for(j=0;j<i;j++){
                        if(input1==freqc[j][0]){
                                if(input2==freqc[j][1]){
					if(input3==freqc[j][2]){
						flag=1;
						pos=j;
						break;
					}
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
			freqc[i][2]=input3;
                        i++;
                }
        }
        for(j=0;j<i;j++){
                m[j]=((float)(freqi[j])/(float)total);
        }


        for(j=0;j<i;j++){
                phith+=m[j]*(m[j]- (1.0/(float)total));
        }

        //printf("\nPhi Three= %f\n", phith);
        free(freqc);
        free(m);
        free(freqi);
        return phith;

}



int main(int c, char **v){

        FILE *infile,*threeboat,*phithree,*phin, *output;

        char *infileName,*input2Name;
        char input;
	char out;
        int i,j,k;
        int matchi,matchj;
        float phiIn, phiTh, phipairIn, phipairTh, phithreeIn, phithreeTh;
        int insize, sizecount;
	int fp;

        infileName=v[1];
	input2Name=v[2];
        infile=fopen(infileName,"r");
        //outfile=fopen("adf_output5Q.txt","w+");
        threeboat=fopen(input2Name,"r");
        phithree=fopen("phiThree_temp_5Q.txt","w+");
        phin=fopen("phin_temp_5Q.txt","w+");
	output=fopen("adf_OutputFinal_5Q.txt","w");

        insize=0;
        sizecount=0;

        while((input=fgetc(infile))!=EOF){
                if(isalpha(input) || isdigit(input)){
                        insize++;
                        fputc(input,phin);
                }
        }

        rewind(infile);
        phiIn=0.0;
        phiTh=0.0;
	phipairIn=0.0;
	phipairTh=0.0;
	phithreeIn=0.0;
	phithreeTh=0.0;

	fp=0;

        printf("\ninsize: %d \n",insize);
        rewind(phin);
        phiIn=phi(phin,insize);

	rewind(phin);
	phipairIn=phiPair(phin,insize);

	rewind(phin);
	phithreeIn=phiThree(phin,insize);

        printf("\nphiIn: %f\n",phiIn);
	printf("\nphipairIn: %f\n",phipairIn);
	printf("\nphithreeIn: %f\n",phithreeIn);

	fseek(threeboat,fp,SEEK_SET);
        while((input=fgetc(threeboat))!=EOF){
                if(isalpha(input) || isdigit(input)){
                fputc(input,phithree);
                sizecount++;
                if(sizecount==insize){
                        //printf("\nsizecount: %d insize: %d\n ",sizecount,insize);
                        rewind(phithree);
                        phiTh=phi(phithree,sizecount);
                        //printf("\nphiTh: %f\n",phiTh);
                        if(phiTh==phiIn){
				printf("\n***********************************************************************\n");
                                printf("\nSAME PHI VALUES!!!          phiIn= %f       phiTh= %f \n",phiIn,phiTh);
				printf("\nfp= %d",fp);
				rewind(phithree);
				phipairTh=phiPair(phithree,sizecount);
				if(phipairTh==phipairIn){
					//printf("\n\n*******************************************************************************\n");
                                	//printf("\nSAME PHI VALUES!!!          phiIn= %f       phiTh= %f \n",phiIn,phiTh);
					printf("\n--------------AND--------------\n");
					printf("\nSAME PHI-PAIR VALUES!!! 	phipairIn= %f   phipairTh= %f \n",phipairIn, phipairTh);
					//printf("\nfp pair= %d\n",fp);
					rewind(phithree);
					phithreeTh=phiThree(phithree,sizecount);

					if(phithreeTh==phithreeIn){
						printf("\n--------------AND--------------\n");
	                                        printf("\nSAME PHI-THREE VALUES!!!       phithreeIn= %f   phithreeTh= %f \n",phithreeIn, phithreeTh);
						//printf("\nfp= %d\n",fp);
						printf("\n*******************************************************************************\n");
						rewind(phithree);
						while((out=fgetc(phithree))!=EOF){
							fputc(out,output);
						}
						//break;
					}
                        	}
				
				//printf("\n***********************************************************************\n\n");
			}
                        sizecount=0;
			fp++;
			fseek(threeboat,fp,SEEK_SET);
                        rewind(phithree);
                }
                }
        }
	fclose(phithree);
	fclose(infile);
	fclose(output);
	fclose(phin);
	fclose(threeboat);

}


