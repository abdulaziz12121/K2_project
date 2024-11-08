#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Simulator.h"

int N; 
char lines[Max_lines][10];  
int ins_num = 0;
char imm[4];

int counter=0;

int PC = 0;  
bool carry;
flags decoded[Max_lines];


//-------------loader 
void loader(const char *filename) {
FILE *file = fopen(filename, "r"); 
    if (!file) {
        perror("Error opening file");
     	 exit(EXIT_FAILURE);}


      

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
 

    fclose(file);


    
   // printf("Contents of fibonacci.bin loaded into array:\n");
     printf("Loaded %d instructions from %s\n", ins_num, filename);

    
}
//----------------Decoder
void decoder(int pc){
if (pc < 0 || pc >= ins_num) {
    printf("Error: PC out of bounds.\n");
    exit(1);}
  

    decoded[pc].J = lines[pc][0];
    decoded[pc].C = lines[pc][1];
    decoded[pc].D1 = lines[pc][2];
    decoded[pc].D0 = lines[pc][3];
    decoded[pc].s_reg = lines[pc][4];
    decoded[pc].s = lines[pc][5];	
       


	printf("Decoded line %d: J=%c, C=%c, D1=%c, D0=%c, s_reg=%c, s=%c\n",
           pc, decoded[pc].J, decoded[pc].C,
           decoded[pc].D1, decoded[pc].D0,
           decoded[pc].s_reg, decoded[pc].s);

    }
//----------------------------- program counter
int Procount(int PC, bool carry){



if ((     ( (decoded[PC].C == '1') ? true : false)  && carry )||( decoded[PC].J=='1')  ){

strncpy(imm, lines[PC] + 5,3 );
imm[3]='\0';
int imm_dec = bin_dec(imm);

 if (imm_dec < 0 || imm_dec >= ins_num) {
            printf("Error: Invalid jump address %d\n", imm_dec);
            exit(1);}


return imm_dec;
}


return PC+1;}







//--------------ALU
int ALU(int A, int B, char sign,bool *carry) {
    *carry=false;int Alu_out=0;
	if (sign == '0') {  // Addition
       Alu_out = A+B;
       if(Alu_out > 15){
       *carry =true;
       Alu_out= Alu_out & 15;}

	return Alu_out;

    } else if (sign == '1') {  // Subtraction
          Alu_out = A-B;
	if(Alu_out<0){
	*carry=true;
	Alu_out = (Alu_out + 16) & 15;
	}
	  return Alu_out;

    } else { 
        printf("Invalid operation\n");
        return Alu_out;}
}


// 2-to-1 MUX function
int mux(int input0, int input1, int select) {
	if (select == 0) {
    	return input0 ; 
	} else if(select ==1){
	return input1 ; 	}
	else {printf("invalid select");return 0;}
}
	
//--------------Decoder D0D1
void D10(char D1,char D0,bool *enRA,bool *enRB,bool *enR0){
*enRA=false;*enRB=false;*enR0=false;
	
if(D1=='0' && D0=='0'){
                //RA=Mux_r;
                 *enRA=true;
        }else if(D1=='0' && D0=='1'){
         //RB=Mux_r ; 
	*enRB=true;
        }else if(D1=='1' && D0=='0'){
        //R0=RA;  
       *enR0=true;	}
else if(D1 == '1' && D0 == '1'){}
//printf("Error: Invalid combination of D1 and D0 (D1=1 D0=1)\n");  
        printf("D1: %c, D0: %c\n",D1, D0);}








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
 	int mux_result=0; int imm_dec ;int alu_result=0;bool carry = false ;
int R0=0,RA=0,RB=0;  
     bool enRA = false, enRB = false, enR0 = false;
bool carry_temp=false;
	while (PC < ins_num) {
        if (PC < 0 || PC >= ins_num) {
            printf("Error: PC out of bounds.\n");
            exit(1);
        }
	    
	   char *ins = fetch(lines,PC);
	printf("\ninstruction %d: %s\n",PC,ins);
	
	decoder(PC);
	 strncpy(imm, lines[PC] + 5, 3);
        imm[3] = '\0';
         imm_dec = bin_dec(imm);

	
	alu_result= ALU(RA,RB,decoded[PC].s,&carry);
        mux_result=mux(alu_result,imm_dec,decoded[PC].s_reg -'0');
	
D10(decoded[PC].D1, decoded[PC].D0, &enRA, &enRB, &enR0);
	
if (enRA) {
    RA=mux_result;
}if (enRB) {
    RB=mux_result;
}if (enR0) {
    R0=RA;
//printf("R0=%d  \n", R0);
}
/
	
        printf("imm=%d  ", imm_dec);
i

        printf("Mux=%d  ", mux_result);
	printf("ALU Result= %d  ",alu_result);
	printf("RA=%d  ", RA);
	printf("RB=%d  ", RB);
        printf("R0=%d  ", R0);
	printf("Carry: %d\n", carry_temp);
	
	sleep(1);
	
        PC = Procount(PC, carry_temp);
	carry_temp = carry ;  
    }
}





//----------binary to decimal
int bin_dec(char *bin){
int dec=0;

for (int i = 0; i < 3; i++) {
dec = (dec << 1) | (bin[i] - '0');}

return dec;}

