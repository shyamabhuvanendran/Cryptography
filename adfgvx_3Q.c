#include<stdio.h>
#include<stdlib.h>

int main(int c, char **v){

	FILE *infile,*tblfile,*out1file;

	char *infileName;
	char input;
	char table[49][49];
	int i,j;
	int matchi,matchj;

	infileName=v[1];
        infile=fopen(infileName,"r");	
	out1file=fopen("adf_output3Q.txt","w");

	tblfile=fopen("adfgvx_table.txt","r");
	printf("\nadfgvx table used is:\n\n");
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
			
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			printf("%c   ",table[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	fclose(tblfile);
	while((input=toupper(fgetc(infile)))!=EOF){
		if(input==' ' || input=='\n'){
                	continue;
                }
		//printf("  input: %c\n",input);
		for(i=1;i<7;i++){
			if(input==table[i][0]){
				matchi=i;
				//printf("  matchi: %d",matchi);
				break;
			}
		}
		input=toupper(fgetc(infile));
		
		//printf("  input: %c\n",input);
		for(j=1;j<7;j++){
			if(input==table[0][j]){
				matchj=j;
				//printf("  matchj: %d\n",matchj);
				break;
			}
		}
		fputc(table[matchi][matchj],out1file);	
	}

	printf("\nOutput is in adf_output3Q.txt\n\n");
}


