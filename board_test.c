#define _GNU_SOURCE
#include "board.h"

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <math.h>
#include <time.h>

#define BUFFER_SIZE 100

/*
* This program is not clearly optmimized
* and he cannot be read or evaluated by Fleury !
* It's a fuc*ing alpha verion ! martialdidit
*/

void board_print_success(FILE* stream, char input[BUFFER_SIZE]) {
	fprintf(stream,"${blue}*Passed*${NC}: check %s\n",input);
	fprintf(stream,"\n");
}

void board_print_error(FILE* stream1,FILE* stream2, char input[BUFFER_SIZE]) {
	
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
	fprintf(stream1,"${red}****FAILED!****:${NC} check %s\n",input);
    fprintf(stream1, "\n");
    fprintf(stream1, "Stderr :\n");
    fprintf(stream1,"\n");
	while ((read = getline(&line, &len, stream2)) != -1) {
       fprintf(stream2,"%s", line);
   	}
   	fprintf(stream1,"\n");
   	if (line)
   		free(line);
}

int play() {

 	FILE * fp_out;
 	FILE * fp;
 	fp = fopen ("file.txt", "w+");
   	fp_out = fopen ("output.txt", "w+");
   	setbuf(fp, NULL);
   	setbuf(fp_out, NULL);

   	int cpt = 0;



	dup2(fileno(fp), STDERR_FILENO);

	   	fprintf(stderr, "33");

	/* ==================  BOARD ================ */

	fprintf(fp_out,"Expected result: SUCCESS\n");
	board_t* b=board_new(1,1);
	if(!b) {
		board_print_error(fp_out,fp,"board_new with 1 1");
	} else {
		board_print_success(fp_out, "board_new with 1 1");
		board_delete(b);
		cpt++;
	}

	fprintf(fp_out,"Expected result: SUCCESS\n");
	b=board_new(64,64);
	if(!b) {
		board_print_error(fp_out,fp,"board_new with 64 64");
	} else {
		board_print_success(fp_out, "board_new with 64 64");
		board_delete(b);
		cpt++;
	}


	fprintf(fp_out,"Expected result: -1\n");
	b=board_new(0,0);
	if(!b) {
		board_print_success(fp_out, "board_new with 0 0");
		board_delete(b);
		cpt++;
	} else {
		board_print_error(fp_out,fp,"board_new with 0 0");
	}

	fprintf(fp_out,"Expected result: -1\n");
	b=board_new(65,65);
	if(!b) {
		board_print_success(fp_out, "board_new with 65 65");
		board_delete(b);
		cpt++;

	} else {
		board_print_error(fp_out,fp,"board_new with 65 65");
	}

    /* ================== LINE ================ */
	b=board_new(3,3);
	board_set(b,1,1,2);
	board_set(b,1,1,1);
	board_set(b,1,1,0);
	fprintf(fp_out,"Expected result: WIN by X in line\n");
	if(board_win(b,3) == 1) {
		board_print_success(fp_out, "WIN by X in line");
		board_delete(b);
		cpt++;
	} else {
		board_print_error(fp_out,fp,"WIN by X in line");
		fprintf(fp_out,"b=board_new(3,3);\n"
			"board_set(b,2,1,2);\n"
			"board_set(b,2,1,1);\n"
			"board_set(b,2,1,0);\n");
	}

	b=board_new(3,3);
	board_set(b,2,1,2);
	board_set(b,2,1,1);
	board_set(b,2,1,0);
	fprintf(fp_out,"Expected result: WIN by O in line\n");
	if(board_win(b,3) == 2) {
		board_print_success(fp_out, "WIN by O in line");
		board_delete(b);
		cpt++;
	} else {
		board_print_error(fp_out,fp,"WIN by O in line");
		fprintf(fp_out,"b=board_new(3,3);\n"
			"board_set(b,2,1,2);\n"
			"board_set(b,2,1,1);\n"
			"board_set(b,2,1,0);\n");	
	}

	/* ================== COLUMN ================ */
	b=board_new(3,3);
	board_set(b,1,2,0);
	board_set(b,1,1,0);
	board_set(b,1,0,0);
	fprintf(fp_out,"Expected result: WIN by X in column\n");
	if(board_win(b,3) == 1) {
		board_print_success(fp_out, "WIN by X in column");
		board_delete(b);
		cpt++;
	} else {
		board_print_error(fp_out,fp,"WIN by X in column");
		fprintf(fp_out,"board_set(b,1,2,0);\n"
			   "board_set(b,1,1,0);\n"
			   "board_set(b,1,0,0);\n");	
	}

	b=board_new(3,3);
	board_set(b,2,2,0);
	board_set(b,2,1,0);
	board_set(b,2,0,0);
	fprintf(fp_out,"Expected result: WIN by O in column\n");
	if(board_win(b,3) == 2) {
		board_print_success(fp_out, "WIN by O in column");
		board_delete(b);
		cpt++;
	} else {
		board_print_error(fp_out,fp,"WIN by O in column");
		fprintf(fp_out,"board_set(b,2,2,0);\n"
			   "board_set(b,2,1,0);\n"
			   "board_set(b,2,0,0);\n");	
	}

	/* ================== DIAG L ================ */
	b=board_new(3,3);
	board_set(b,1,0,0);
	board_set(b,1,1,1);
	board_set(b,1,2,2);
	fprintf(fp_out,"Expected result: WIN by X in diagL\n");
	if(board_win(b,3) == 1) {
		board_print_success(fp_out, "WIN by X in diagL");
		board_delete(b);
		cpt++;
	} else {
		board_print_error(fp_out,fp,"WIN by X in diagL");
		fprintf(fp_out,"board_set(b,1,0,0);\n"
			   "board_set(b,1,1,1);\n"
			   "board_set(b,1,2,2);\n");	
	}

	b=board_new(3,3);
	board_set(b,2,0,0);
	board_set(b,2,1,1);
	board_set(b,2,2,2);
	fprintf(fp_out,"Expected result: WIN by 0 in diagL\n");
	if(board_win(b,3) == 2) {
		board_print_success(fp_out, "WIN by 0 in diagL");
		board_delete(b);
		cpt++;
	} else {
		board_print_error(fp_out,fp,"WIN by 0 in diagL");
		fprintf(fp_out,"board_set(b,1,0,0);\n"
			   "board_set(b,1,1,1);\n"
			   "board_set(b,1,2,2);\n");	
	}

	/* ================== DIAG R ================ */
	b=board_new(3,3);
	board_set(b,1,2,0);
	board_set(b,1,1,1);
	board_set(b,1,0,2);
	fprintf(fp_out,"Expected result: WIN by X in diagR\n");
	if(board_win(b,3) == 1) {
		board_print_success(fp_out, "WIN by X in diagR");
		board_delete(b);
		cpt++;
	} else {
		board_print_error(fp_out,fp,"WIN by X in diagR");
		fprintf(fp_out,"board_set(b,1,2,0);\n"
			   "board_set(b,1,1,1);\n"
			   "board_set(b,1,0,2);\n");	
	}

	b=board_new(3,3);
	board_set(b,2,2,0);
	board_set(b,2,1,1);
	board_set(b,2,0,2);
	fprintf(fp_out,"Expected result: WIN by 0 in diagR\n");
	if(board_win(b,3) == 2) {
		board_print_success(fp_out, "WIN by 0 in diagR");
		board_delete(b);
		cpt++;
	} else {
		board_print_error(fp_out,fp,"WIN by 0 in diagR");
		fprintf(fp_out,"board_set(b,1,2,0);\n"
			   "board_set(b,1,1,1);\n"
			   "board_set(b,1,0,2);\n");	
	}

	/* ================== BOARD EMPTY CELL ================ */
	fprintf(fp_out,"Expected result: -1\n");
	if(board_count_empty_cells(NULL) == -1){
		board_print_success(fp_out, "board empty cell with NULL");
		cpt++;
	} else {
		board_print_error(fp_out,fp,"board empty cell with NULL");	
	}

	/* ================== BOARD COPY ================ */
	fprintf(fp_out,"Expected result: -1\n");
	if(!board_copy(NULL)){
		board_print_success(fp_out, "board copy with NULL");
		cpt++;
	} else {
		board_print_error(fp_out,fp,"board copy with NULL");	
	}

	/* ================== BOARD GET ================ */
	b=board_new(3,3);
	board_set(b,2,2,0);
	fprintf(fp_out,"Expected result: -1\n");
	if(board_get(b,5,5) == -1) {
		board_print_success(fp_out, "board get with wrong value");
		cpt++;
	} else {
		board_print_error(fp_out,fp,"board get with wrong value");	
	}
	fprintf(fp_out,"Expected result: 0\n");
	if(board_get(b,2,2) == 0) {
		board_print_success(fp_out, "board get with not empty stack");
		cpt++;
	} else {
		board_print_error(fp_out,fp,"board get with not empty stack");	
	}
	fprintf(fp_out,"Expected result: 2\n");
	if(board_get(b,2,0) == 2) {
		board_print_success(fp_out, "board get with stack take by player 2");
		cpt++;
	} else {
		board_print_error(fp_out,fp,"board get with stack take by player 2");	
	}
	fprintf(fp_out,"Expected result: 1\n");
	board_set(b,1,1,0);
	if(board_get(b,1,0) == 1) {
		board_print_success(fp_out, "board get with stack take by player 1");
		cpt++;
	} else {
		board_print_error(fp_out,fp,"board get with stack take by player 1");	
	}

	/* ================== BOARD SET ================ */
	fprintf(fp_out,"Expected result: -1\n");
	if(board_set(b,5,0,0) == -1) {
		board_print_success(fp_out, "board set with wrong player");
		cpt++;
	} else {
		board_print_error(fp_out,fp,"board set with wrong player");	
	}
	fprintf(fp_out,"Expected result: 0\n");
	if(board_set(b,1,1,0) == 0) {
		board_print_success(fp_out, "board set with not empty stack");
		cpt++;
	} else {
		board_print_error(fp_out,fp,"board set with not empty stack");	
	}
	fprintf(fp_out,"Expected result: 1\n");
	if(board_set(b,1,0,0) == 1) {
		board_print_success(fp_out, "board set with 0 0");
		cpt++;
	} else {
		board_print_error(fp_out,fp,"board set with 0 0");	
	}

	/* ================== BOARD CLEAR ================ */


    fclose(fp);
    fclose(fp_out);

   	return cpt;
}

int main() {

	int cpt = play();
	printf("%d\n", cpt);

	return 0;
}