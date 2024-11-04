#include<stdio.h>
#include<string.h>


//2-bits because of only 3 codes
#define RA_Mc 0b00
#define RB_Mc 0b01
#define RO_Mc 0b10

// 2 bits because 3 operations therefore 2 bits enough
#define Add_Mc 0b001
#define Sub_Mc 0b010
#define Mov_Mc 0b011

int Mc[8];
int ref=0;

int main(char *argv[]){
const char *filename=argv[1];

FILE *fi ; 
fi=fopen(filename,"r");
char Str[10];
char dest[2],R1[2],R2[2],op[2];
int imm;

if (fi == NULL) {
    printf("File not found\n");
    return 1;}


printf("\nUsing the file: %s",filename);

//scanf(fi, "%2s %1s %2s %d %f", );
int i=0,line_num=1;
while (fgets(Str, 10, fi)) {
	if(sscanf(Str, "%2s = %2s %2s %2s", dest, R1, op, R2) == 4){
	
	storebit(Reg_Mc(dest),0,2);
	storebit(Reg_Mc(R1),2,2);
        storebit(Op_Mc(op),4,2);
        storebit(Reg_Mc(R2),6,2);
	
	ref=0;
	printf("Line %d : %s -> Machine Code: ",line_num,Str);
	for(int j=0;j<8;j++){
	printf("%d",Mc[j]);}
	reset_Mc();
	
	
	}else if(sscanf(Str,"%2s = %2s",dest,R1)==2){
	 printf("Line %d : %s -> Machine Code: ",line_num,Str);
        //storing 
	 
	for(int j=0;j<8;j++){
        printf("%d",Mc[j]);}
        reset_Mc();
	
	
	}else if(sscanf(Str,"%2s = %d",dest,&imm)==2){
	storebit(Reg_Mc(dest),0,2);
	storebit(Reg_Mc(imm),0,6);
	printf("Line %d : %s -> Machine Code: ",line_num,Str);
        for(int j=0;j<8;j++){
        printf("%d",Mc[j]);}
        reset_Mc();
	}
		
	
	printf("\n");line_num++; i++;}



fclose(fi);
return 0;}
// a function which turns machine code into binary and store it 
void storebit(int mc_dec,int ref,int size){

for(int i=0;i<size;i++){
Mc[ref+ i] = (mc_dec >> i) & 1 ;}



}


//reset all bits to 0
void reset_Mc() {
for (int i = 0; i < 8; i++) {
Mc[i] = 0;}}


//---------------------get register ->  return Machine code
int Reg_Mc(char* reg){
if(strcmp(reg,"R0") ==0)return R0_Mc ; 
if(strcmp(reg,"RA") ==0)return RA_Mc ;
if(strcmp(reg,"RB") ==0)return RB_Mc ;
return -1;}

//--------------------- get operation ->return machine code
int Op_Mc(char* op){
if(strcmp(op,"+") ==0)return Add_Mc ;
if(strcmp(op,"-") ==0)return Sub_Mc ;
if(strcmp(op,"=") ==0)return Mov_Mc ;
return -1;}






//--------------------- 
void Controller(){}
