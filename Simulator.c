#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N; 
char lines[9][10];
int imm[3];
char J[10];
char C[10];
char D1[10];
char D0[10];
char s_reg[10];
char s[10];
int counter=0;
int ALU_r =0;
 
void loader() {
FILE *file = fopen("fibonacci.bin", "r");  // Open file in text read mode
    if (!file) {
        perror("Error opening file");
        
    }

      
    int index = 0;

 while (fgets(lines[index], sizeof(lines[index]), file) != NULL) {
        // Remove newline character if it's there
        size_t len = strcspn(lines[index], "\n");
        if (lines[index][len] == '\n') {
            lines[index][len] = '\0';  // Replace the newline with null terminator
        }

        // Increment index to store the next line
        index++;

        // Avoid going beyond the array bounds
        if (index >= lines) {
            fprintf(stderr, "Array is full, increase array size if needed.\n");
            break;
        }
    }
 N=index;
 

    fclose(file);


    // Print the contents of the array to verify
    printf("Contents of fibonacci.bin loaded into array:\n");
    for (int i = 0; i < index; i++) {
        printf("%s\n", lines[i]);
    }

    
}

void decoder(){
	
	int i=0;	
    	J[counter] = lines[counter][i];
        C[counter] = lines[counter][i + 1];
        D1[counter] = lines[counter][i + 2];
        D0[counter] = lines[counter][i + 3];
        s_reg[counter] = lines[counter][i + 4];
        s[counter] = lines[counter][i + 5];

        // Print the values
        printf("J[%d]: %c\n", counter, J[counter]);
        printf("c[%d]: %c\n", counter, C[counter]);
        printf("D1[%d]: %c\n", counter, D1[counter]);
        printf("D0[%d]: %c\n", counter, D0[counter]);
        printf("s_reg[%d]: %c\n", counter, s_reg[counter]);

	counter++;


}
#include <stdio.h>


int ALU(int A, int B, char sign) {
    if (sign == '0') {  // Addition
       ALU_r = A+B;
	return ALU_r;
    } else if (sign == '1') {  // Subtraction
          ALU_r = A-B;
	  return ALU_r;
    } else {  // Invalid operation
        printf("Invalid operation\n");
        return 0;
    }
}


// 2-to-1 MUX function
int mux(int input0, int input1, int select) {
    int temp;
	if (select == 0) {
        temp= imm;  // If select is 0, output input0
    } else {
        temp=ALU_r;  // If select is 1, output input1
    }

if((D1=='0' && D0=='0'){
		RA=temp;
		
	}else if(D1=='1' && D0=='0'){
	RB=temp;
	
	}else if(D1=='0' && D0=='1'){
	
	R0=RA;
	}
}


int main() {
    loader();
    decoder();
	   
        printf("%d\n", ALU(2, 2, '0'));
 	printf("%d\n", ALU_r);
   
    return 0;
}

