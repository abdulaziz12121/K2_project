#include<stdio.h>
#include<string.h>


void conv_to_binary(int dec, char* imm_binary);
unsigned char convert_to_byte();
void storebit(int mc_dec, int ref, int size);
void reset_Mc();
int Reg_Mc(const char* reg);
int Op_Mc(const char* op);

//2-bits because of only 3 codes
#define R0_Mc 0b00
#define RA_Mc 0b01
#define RB_Mc 0b10

// 2 bits because 3 operations therefore 2 bits enough
#define Add_Mc 0b001
#define Sub_Mc 0b010
#define Mov_Mc 0b011

char Mc[9];
int ref=0;
int Cont[6];
//unsigned char convert_to_byte();


//int main(char *argv[]){
int main(int argc, char *argv[]){
const char *filename=argv[1];
unsigned char byte = convert_to_byte();

FILE *fi ; 
fi=fopen(filename,"r");

FILE *fo ;
fo=fopen("fibonacci.bin","wb");


char Str[16];
char dest[2],R1[2],R2[2],op[2];
//int imm;

if (fi == NULL) {
    printf("Error: input file not found\n");
    return 1;}

if (fo == NULL) {
    printf("Error: output file not found\n");
    return 1;}


printf("\nUsing the file: %s",filename);

//scanf(fi, "%2s %1s %2s %d %f", );
int i=0,line_num=1;
int imm;char imm_binary[4];

while (fgets(Str, 16, fi)) {
	Mc[8] = '\0';
	//printf("\nLine %d: %s -> Machine Code: ",line_num,Str);
	if(strcmp(Str,"RA = RA + RB\n")==0){//RA = RA + RB
	strcpy(Mc,"00000000");}
	//printf("\n%s",Mc);}
	else if(strcmp(Str,"RB = RA + RB\n")==0){//RB = RA + RB
        strcpy(Mc,"00010000");}
	//printf("\n%s",Mc);}
	else if(strcmp(Str,"RA = RA - RB\n")==0){//RA = RA −RB 
        strcpy(Mc,"00000100");}
	//printf("\n%s",Mc);}
	else if(strcmp(Str,"RB = RA - RB\n")==0){//RB = RA −RB 
        strcpy(Mc,"00010100");}
	//printf("\n%s",Mc);}
	else if(strcmp(Str,"R0 = RA\n")==0){//RO = RA 
        strcpy(Mc,"00100000");}
	//printf("\n%s",Mc);}

	else if(strncmp(Str,"RA = ",5)==0){ //RA = imm  need to fix
        strcpy(Mc,"00001");
	sscanf(Str +5,"%d",&imm);
	conv_to_binary(imm,imm_binary);
	//strcpy(Mc,imm_binary);
	strcat(Mc,imm_binary);}
	//printf("\n%s",Mc);}
	
	else if(strncmp(Str,"RB = ",5)==0){//RB = imm
        strcpy(Mc,"00011");
	sscanf(Str +5,"%d",&imm);
        conv_to_binary(imm,imm_binary);
        strcat(Mc,imm_binary);}
	//printf("\n%s",Mc);
	
	else if(strncmp(Str,"JC = ",5)==0){//JC=imm
        strcpy(Mc,"01110");
	sscanf(Str +5,"%d",&imm);
        conv_to_binary(imm,imm_binary);
        strcat(Mc,imm_binary);}
	//printf("\n%s",Mc);

	else if(strncmp(Str,"J = ",4)==0){//J=imm 
        strcpy(Mc,"10110");
	sscanf(Str +4,"%d",&imm);
        conv_to_binary(imm,imm_binary);
        strcat(Mc,imm_binary);}
	//printf("\n%s",Mc);}
	else {return 0;}

        printf("\nLine %d: %s -> Machine Code: ",line_num,Str);
	for(int j=0;j<8;j++){
	printf("%c",Mc[j]);}
	printf("\n");
	
	fputs(Mc,fo);
	fputs("\n",fo);
	line_num++;}
		
	
fclose(fo);
fclose(fi);
return 0;}

	
	//if(sscanf(Str, "%2s = %2s %2s %2s", dest, R1, op, R2) == 4){		
		
	/*	
	storebit(Reg_Mc(dest),0,2);
	storebit(Reg_Mc(R1),2,2);
        storebit(Op_Mc(op),4,2);
        storebit(Reg_Mc(R2),6,2);
	
	//ref=0;
	printf("\nLine %d : %s -> Machine Code: ",line_num,Str);
	for(int j=0;j<8;j++){
	printf("%d",Mc[j]);}

	byte = convert_to_byte();
        fwrite(&byte, sizeof(byte), 1, fo);
        //fputc('\n',fo);
	
	reset_Mc();
	
	
	}else if(sscanf(Str,"%2s = %2s",dest,R1)==2){
	 printf("\nLine %d : %s -> Machine Code: ",line_num,Str);
        storebit(Reg_Mc(R1),0,2);
        storebit(Reg_Mc(dest),0,2);


	 
	 
	 
	 //storing
	//
	 
	for(int j=0;j<8;j++){
        printf("%d",Mc[j]);}


	byte = convert_to_byte();
        fwrite(&byte, sizeof(byte), 1, fo);
        //fputc('\n',fo);

        reset_Mc();
	
	
	}else if(sscanf(Str,"%2s = %d",dest,&imm)==2){
	storebit(Reg_Mc(dest),0,2);
	storebit(imm,2,6);
	printf("\nLine %d : %s -> Machine Code: ",line_num,Str);
        
	for(int j=0;j<8;j++){
        printf("%d",Mc[j]);}

	byte = convert_to_byte();
        fwrite(&byte, sizeof(byte), 1, fo);
        //fputc('\n',fo);

        

        reset_Mc();
	
	
	}
		
	
	printf("\n");line_num++; i++;}
*/


//---------------convert decimal to binary
void conv_to_binary(int dec,char*imm_binary){
int temp;
for(int i=2;i>=0;i--){
imm_binary[2-i]= ( (dec>>i)&1  ) ? '1' :'0';}
imm_binary[3] = '\0';

}





//-------- Mc -> byte
unsigned char convert_to_byte() {
    unsigned char byte = 0;
    for (int i = 0; i < 8; i++) {
        byte = (byte << 1) | Mc[i];
    }
    return byte;
}





// a function which turns machine code to store it
void storebit(int mc_dec,int ref,int size){
for(int i=0;i<size;i++){
Mc[ref + size -1 - i] = (mc_dec >> i) & 1 ;}
 
}


//reset all bits to 0
void reset_Mc() {
for (int i = 0; i < 8; i++) {
Mc[i] = 0;}}


//---------------------get register ->  return Machine code
int Reg_Mc(const char* reg){
if(strcmp(reg,"R0") ==0)return R0_Mc ; 
if(strcmp(reg,"RA") ==0)return RA_Mc ;
if(strcmp(reg,"RB") ==0)return RB_Mc ;
return -1;}

//--------------------- get operation ->return machine code
int Op_Mc(const char* op){
if(strcmp(op,"+") ==0)return Add_Mc ;
if(strcmp(op,"-") ==0)return Sub_Mc ;
if(strcmp(op,"=") ==0)return Mov_Mc ;
return 0;}




