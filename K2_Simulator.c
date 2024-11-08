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

return 0 ;}
