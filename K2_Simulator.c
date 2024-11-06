#include "Simulator.h"


int main(int argc, char *argv[]){
char mode;
if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }	
	
loader(argv[1]);
//decoder();

printf("\nSelect one of the following mode\nR - Run in continuous mode\nS - Run step-by-step\nSelect mode: ");

scanf("%c",&mode);

if(mode == 'S'){
run_sbs();}
else if(mode == 'R'){
run_con();}
else{printf("Error:invalid input");}

return 0;}
/*




//run in continious mode
void run_con(){
printf("\nStarting Simulator in continuous mode...");
printf("\nExecution (Register RO output):");

//call ins memory
//program counter
//Mux
//ALU

while(PC<ins_num){



printf("\nR0=%d",R0)
PC++;}



} 






//--------run in  step-by-step 
void run_sbs(){
printf("\nStarting Simulator in step-by-step mode...");
int i=1;
char asm_line[8];
char byte[8];//instruction in bits

	for(int i=0;i<Number_of_ins;i++){
	printf("\nInstruction %d",i);
	printf("%s",Mc_asm(byte));
	printf("	[Press Enter to continue]");
	while (getchar() != '\n');
					}


}


//ins= lines
char*  Mc_asm(char *byte){
    	
strncpy(imm, byte + 5, 3);
    imm[3]='\0';

if (strncmp(byte, "00000000") == 0) {
        strcpy(asm_line, "RA=RA+RB");
    }else if (strncmp(byte, "00010000") == 0) {
        strcpy(asm_line, "RB=RA+RB");
   
    }else if (strncmp(byte, "00000100") == 0) {
        strcpy(asm_line, "RA=RA-RB");
   
    }else if (strncmp(byte, "00010100") == 0) {
        strcpy(asm_line, "RB=RA-RB");
   
    }else if (strncmp(byte, "00100000") == 0) {
        strcpy(asm_line, "RO=RA");
   
    }else if( strncmp(byte,"00001",5) ==0 ){         //with imm
        strcpy(asm_line, "RA=%d",bin_dec(imm ));
    
    }else if( strncmp(byte,"00011",5) ==0 ){
        strcpy(asm_line, "RB=%d",bin_dec(imm ));
    
    }else if( strncmp(byte,"01110",5) ==0 ){
        strcpy(asm_line, "JC=%d",bin_dec(imm ));
    
    }else if( strncmp(byte,"10110",5) ==0 ){
        strcpy(asm_line, "J=%d",bin_dec(imm ));
    }


return asm_line;}


//-------------------
int bin_dec(char *bin){
int dec=0;

for (int i = 0; i < 3; i++) {
dec = (dec << 1) | (bin[i] - '0');}

return decimal;}


//-----------------------
void imm_bin(char *byte,char *imm){
  strncpy(imm, byte + 5, 3);
  imm[3] = '\0'; }*/







//---------------------------------
//char* Ins_memory(int j,int c,int D0,int D1,int Sr,int S){int address=0;return address;}


//---------------------------------
//int ALU(int A,int B,int op){return 0;}

//---------------------------------
//int MUX(int Sr){return 0;}

//---------------------------------
//int fetch(char *Memory,int PC){return Memory[PC];}


