#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float phi(FILE *infile, int totalChars){
        int *freqi;
        float *m;
        char *freqc;
        char *infileName;
        char input;
        float *phi;
	float phiVal;
        int i,j,flag,pos,total;
	int size;
//        infile=fopen(infileName,"r");
	if(totalChars%2==0){
		size=(totalChars/2)+1;
	}
	else{
		size=(totalChars/2)+2;
	}
        freqi=malloc(size*sizeof(int));
	freqc=malloc(size*sizeof(char));
	rewind(infile);
        flag=0;
        pos=0;
        i=0;
        j=0;
        total=0;
        input=tolower(fgetc(infile));
	//printf("\nphi input\n %c",input);
        freqi[0]=1;
        freqc[0]=input;
        i++;
        phiVal=0.0;
	//printf("\nphi input\n");
        while((input=tolower(fgetc(infile)))!=EOF){
                //printf("%c",input);    
                //if(isalpha(input)){   
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
		//}
		}
        }
	/*for(j=0;j<i;j++){
                 printf("\n%c",freqc[j]);
                 printf("  %d",freqi[j]);
	}*/                                         
        for(j=0;j<i;j++){
                total+=freqi[j];
        }
	//printf("\nphi total= %d\nm[j]",total);
	m=malloc(i*sizeof(float));
        for(j=0;j<i;j++){
                m[j]=((float)(freqi[j])/(float)total);
		//printf("%f ",m[j]);
        }


        for(j=0;j<i;j++){
		//printf("\t Phi: %f",phiVal);
                phiVal+=m[j]*(m[j]- (1.0/(float)total));
        }
	free(m);
	free(freqi);
	free(freqc);
        //printf("\n phi: %f\n", phiVal);
	return phiVal;

}



int main(int c, char **v){

	FILE *infile,*tblfile,*out1file,*outtransfile,*matOut,*out;

	char *infileName;
	char input;
	char table[49][49];
	int i,j,k;
	int matchi,matchj;
	int totalChars, transvar,total;
	char **transmat;
	//char mat[2000][2000];
	float phiVal;
	phiVal=0.0;
	totalChars=0;
	infileName=v[1];
        infile=fopen(infileName,"r");	
	out1file=fopen("adf_output4Q.txt","w+");
	outtransfile=fopen("adf_trans_output4Q.txt","w+");
	tblfile=fopen("adfgvx_table.txt","r");
	matOut=fopen("adf_matOut.txt","w");
	out=fopen("adf_output_4Q.txt","w");	

	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			input=fgetc(tblfile);
			if(input==' ' || input=='\n'){
				input=fgetc(tblfile);
			}
			if((i==0)&&(j==0)){
				table[0][0]=' ';
			}
			else{
				table[i][j]=input;
			}
		}
	}
			
	/*for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			printf("%c   ",table[i][j]);
		}
		printf("\n");
	}*/
	
	fclose(tblfile);
	while((input=fgetc(infile))!=EOF){
		if(isalpha(input)){
			totalChars++;
		}
	}
	
	printf("\n\nTotal Characters= %d", totalChars);
	rewind(infile);
	
	transvar=1;
	total=totalChars;
	
	
	while((totalChars*transvar)>=total){
		transmat=malloc(transvar*sizeof(char*));
		for(j=0;j<transvar;j++){
			transmat[j]=malloc(totalChars*sizeof(char));
			for(k=0;k<totalChars;k++){
				input=fgetc(infile);
				if(input==EOF){
					input=' ';
				}
				transmat[j][k]=input;
			}
		}
		/*printf("\nPutting---\n");
		for(j=0;j<transvar;j++){
                        for(k=0;k<totalChars;k++){
				printf("%c ",transmat[j][k]);
			}	
			printf("\n");
	        }
		printf("\nWriting---\n");*/
	        for(j=0;j<totalChars;j++){
	                for(k=0;k<transvar;k++){
				if(isalpha(transmat[k][j])){
					//printf("%c ",transmat[k][j]);
					fputc(transmat[k][j],outtransfile);
				}
			}
			//printf("\n");
		}		

        	rewind(outtransfile);
		//rewind(infile);
		//rewind(out1file);	
		//input=fgetc(outtransfile);
		//printf(" input : %c\n",input); 
		while((input=toupper(fgetc(outtransfile)))!=EOF){        	
			//printf(" outtrans input: %c\n",input);
			for(i=1;i<7;i++){
				if(input==table[i][0]){
					matchi=i;
					//printf("  matchi: %d",matchi);
					break;
				}
			}
			input=toupper(fgetc(outtransfile));
		
			//printf("outtrans  input: %c\n",input);
			for(j=1;j<7;j++){
				if(input==table[0][j]){
					matchj=j;
					//printf("  matchj: %d\n",matchj);
					break;
				}
			}
			fputc(table[matchi][matchj],out1file);	
		}
		rewind(out1file);
		rewind(outtransfile);
		phiVal=phi(out1file,total);
		fprintf(matOut, "\n%d*%d  %f",transvar,totalChars,phiVal);	
		if(phiVal>=0.05 && phiVal< 0.071){
			printf("\n\nphiVal= %f\n",phiVal);
			printf("\nMatrix Period:\n");
			printf("   %d  *  ", transvar);
			printf("%d\n\n", totalChars);
			rewind(out1file);
			while((input=fgetc(out1file))!=EOF){
				fputc(input,out);
			}
		}	
		//printf("transvar= %d    ", transvar);
                //printf("totalChars= %d\n\n", totalChars);
		//}
		transvar++;
		if(transvar>total){
			break;
		}
                if((total%transvar)==0){
                        totalChars=(total/transvar);
                }
                else{
                        totalChars=(total/transvar)+1;
                }
		free(transmat);
		rewind(infile);
		rewind(outtransfile);
		rewind(out1file);
	}
	fclose(outtransfile);
	fclose(infile);
	fclose(matOut);
}


