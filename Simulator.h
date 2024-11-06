#ifndef SIMULATOR_H
#define SIMULATOR_H

#define Max_lines 100 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// global variables
extern char lines[Max_lines][10];
extern int R0, PC, ins_num;
extern char imm[4];
extern char J[10], C[10], D1[10], D0[10], s_reg[10], s[10];
extern int ALU_r;


// function prototypes
void loader(const char *filename);
void decoder(int pc);
void run_con();
void run_sbs();
char* Mc_asm(char *byte);
int bin_dec(char *bin);
char* fetch(char Memory[][10], int PC);
//int fetch(char Memory[][10], int PC);
int ALU(int A, int B, char sign);
int mux(int input0, int input1, int select);

#endif

