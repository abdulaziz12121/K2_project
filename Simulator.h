#ifndef SIMULATOR_H
#define SIMULATOR_H

#define Max_lines 100 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct{
char J,C,D1,D0,s_reg,s;}flags;



// global variables
extern char lines[Max_lines][10];
extern int R0, PC, ins_num;
extern char imm[4];
extern int ALU_r;
extern flags decoded[Max_lines];




// function prototypes
void loader(const char *filename);
void decoder(int pc);
void run_con();
void run_sbs();
char* Mc_asm(char *byte);
int bin_dec(char *bin);
char* fetch(char Memory[][10], int PC);
//int fetch(char Memory[][10], int PC);
int ALU(int A, int B, char sign,bool *carry);
int mux(int input0, int input1, int select);
void D10(char D1,char D0,bool *enRA,bool *enRB,bool *enR0);
int Procount(int PC,bool carry);

#endif

