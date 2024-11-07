#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Simulator.h"

int N; 
//char lines[9][10];
char lines[Max_lines][10];  
int ins_num = 0;
char imm[4];
char J[10];
char C[10];
char D1[10];
char D0[10];
char s_reg[10];
char s[10];
int counter=0;
int ALU_r=0 ;
int RA=0, RB=0 , R0=0 , PC = 0;  
bool carry;
//-------------loader 
void loader(const char *filename) {
FILE *file = fopen(filename, "r"); 
    if (!file) {
        perror("Error opening file");
     	 exit(EXIT_FAILURE);}


      
    //int index = 0;

 while (fgets(lines[ins_num], sizeof(lines[0]), file) != NULL) {
        
        size_t len = strcspn(lines[ins_num], "\n");
        if (lines[ins_num][len] == '\n') {
            lines[ins_num][len] = '\0';         }

     
        ins_num++;

     
        if (ins_num >= Max_lines) {
            fprintf(stderr, "Array is full, increase array size if needed.\n");
            break;
        }
    }
// N=index;
 

    fclose(file);


    
   // printf("Contents of fibonacci.bin loaded into array:\n");
     printf("Loaded %d instructions from %s\n", ins_num, filename);

    
}
//----------------Decoder
void decoder(int pc){
if (PC < 0 || PC >= ins_num) {
    printf("Error: PC out of bounds.\n");
    exit(1);
}
  
       
	J[pc] = lines[pc][0];
    C[pc] = lines[pc][1];
    D1[pc] = lines[pc][2];
    D0[pc] = lines[pc][3];
    s_reg[pc] = lines[pc][4];
    s[pc] = lines[pc][5];
    printf("D1[%d]: %c\n", pc, D1[pc]);
    printf("D0[%d]: %c\n", pc, D0[pc]);
    printf("s_reg[%d]: %c\n", pc, s_reg[pc]);
    printf("s[%d]: %c\n", pc, s[pc]);

    }
//----------------------------- program counter
int Procount(int PC, int carry){

if(  (C[PC]=='1' && carry )|| J[PC]=='1'){
strncpy(imm, lines[PC] + 5, 3);
    imm[3]='\0';
int imm_dec = bin_dec(imm);
 if (imm_dec < 0 || imm_dec >= ins_num) {
            printf("Error: Invalid jump address %d\n", imm_dec);
            exit(1);
        }
return imm_dec;
}

return PC+1;}







//--------------ALU
int ALU(int A, int B, char sign) {
    carry=0;int Alu_out;
	if (sign == '0') {  // Addition
       Alu_out = A+B;
       if(Alu_out > 15){
       carry =1;
       Alu_out= Alu_out & 15;}

	return Alu_out;

    } else if (sign == '1') {  // Subtraction
          Alu_out = A-B;
	if(Alu_out<0){
	carry=1;
	Alu_out = Alu_out & 15;
	}
	  return Alu_out;
    } else { 
        printf("Invalid operation\n");
        return Alu_out;}
}


// 2-to-1 MUX function
int mux(int input0, int input1, int select) {
	if (select == 0) {
     	//temp = bin_dec(imm);   // If select is 0, output input0
    	return input0 ; 
	} else if(select ==1){
	return input1 ; 	}
	else {printf("invalid select");return 0;}
        //temp=ALU_r;  // If select is 1, output input1}
}
	
//--------------Decoder D0D1
void D10(char D1,char D0,int Mux_r){
if(D1=='0' && D0=='0'){
                RA=Mux_r;
                 
        }else if(D1=='0' && D0=='1'){
         RB=Mux_r ; 

        }else if(D1=='1' && D0=='0'){
        R0=RA;   }
else if(D1 == '1' && D0 == '1'){
        printf("Error: Invalid combination of D1 and D0\n");  }
        printf("D1[%d]: %c, D0[%d]: %c\n", PC, D1, PC, D0);


}







//-------------Machine to assembly
char*  Mc_asm(char *byte){
static char asm_line[20];
char imm[4];
strncpy(imm, byte + 5, 3);
    imm[3]='\0';
int imm_dec = bin_dec(imm);

if (strncmp(byte, "00000000",8) == 0) {
        strcpy(asm_line, "RA=RA+RB");
    }else if (strncmp(byte, "00010000",8) == 0) {
        strcpy(asm_line, "RB=RA+RB");

    }else if (strncmp(byte, "00000100",8) == 0) {
        strcpy(asm_line, "RA=RA-RB");

    }else if (strncmp(byte, "00010100",8) == 0) {
        strcpy(asm_line, "RB=RA-RB");

    }else if (strncmp(byte, "00100000",8) == 0) {
        strcpy(asm_line, "RO=RA");

    }else if( strncmp(byte,"00001",5) ==0 ){         //with imm
        sprintf(asm_line, "RA=%d",imm_dec);

    }else if( strncmp(byte,"00011",5) ==0 ){
        sprintf(asm_line, "RB=%d",imm_dec);

    }else if( strncmp(byte,"01110",5) ==0 ){
        sprintf(asm_line, "JC=%d",imm_dec);

    }else if( strncmp(byte,"10110",5) ==0 ){
        sprintf(asm_line, "J=%d",imm_dec);
    }else {
    printf("Warning: Unrecognized instruction %s\n", byte);}



return asm_line;}
//------------------------fetch
char* fetch(char Memory[][10], int PC) {
    
	
if (PC >= 0 && PC < ins_num) {
    return Memory[PC];
} else {
    printf("Fetch Error: PC out of bounds.\n");
    exit(1);}  
}


// ------------------Run in step-by-step mode
void run_sbs() {
    printf("\nStarting Simulator in step-by-step mode...\n");

    for (int i = 0; i < ins_num; i++) {
        char *byte = lines[i];
        printf("\nInstruction %d: %s", i, Mc_asm(byte));
        printf(" [Press Enter to continue]");
        getchar();
    }
}

//------------------ Run in continuous mode
void run_con() {
    printf("\nStarting Simulator in continuous mode...");
    printf("\nExecution (Register RO output):\n");
 	int mux_result=0; int imm_dec ;int alu_result=0;
    while (PC < ins_num) {
        if (PC < 0 || PC >= ins_num) {
            printf("Error: PC out of bounds.\n");
            exit(1);
        }
	    
	   char *ins = fetch(lines,PC);
	printf("instruction %d: %s\n",PC,ins);
	
	decoder(PC);
	 strncpy(imm, lines[PC] + 5, 3);
        imm[3] = '\0';
         imm_dec = bin_dec(imm);

	
	alu_result= ALU(RA,RB,s[PC]);
               mux_result=mux(alu_result,imm_dec,s_reg[PC]-'0');

       	D10(D1[PC], D0[PC],mux_result);

        printf("\nimm=%d  ", imm_dec);

	// if (strncmp(Mc_asm(ins), "RO=RA", 5) == 0) {
          //  printf("R0=%d\n", R0);}
	  

        printf("Mux=%d  ", mux_result);
	printf("ALU Result= %d  ",alu_result);
	printf("RA=%d  ", RA);
	printf("RB=%d  ", RB);
        printf("R0=%d  \n", R0);
	
	
	sleep(1);
        PC = Procount(PC, carry);
    }
}





//----------binary to decimal
int bin_dec(char *bin){
int dec=0;

for (int i = 0; i < 3; i++) {
dec = (dec << 1) | (bin[i] - '0');}

return dec;}

