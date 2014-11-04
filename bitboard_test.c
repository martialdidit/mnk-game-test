#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "board.h"

/* gcc -std=c99 -I../include -c bitboard_test.c */
/* gcc -std=c99 -o bitboard_test bitboard_test.o board.o */

void
display_result (bool test)
{
  if (test)
    fprintf (stdout, "(passed)\n");
  else
    fprintf (stdout, "(failed!)\n");
}

int
main (void)
{

 int result;
 board_t *board0, *board1;

 /* Checking board_new () */

 board0 = board_new (-1, 1);
 printf ("board_new (-1, 1) == NULL : %p ", board0);
 display_result (board0 == NULL);

 board0 = board_new (1, -1);
 printf ("board_new (1, -1) == NULL : %p ", board0);
 display_result (board0 == NULL);

 board0 = board_new (0, 1);
 printf ("board_new (0, 1)  == NULL : %p ", board0);
 display_result (board0 == NULL);

 board0 = board_new (1, 0);
 printf ("board_new (1, 0)  == NULL : %p ", board0);
 display_result (board0 == NULL);

 board0 = board_new (65, 65);
 printf ("board_new (65, 65)  == NULL : %p ", board0);
 display_result (board0 == NULL);

 board0 = board_new (1, 1);
 printf ("board_new (1, 1)  != NULL : %p ", board0);
 display_result (board0 != NULL);

 board1 = board_new (64, 64);
 printf ("board_new (64, 64)  != NULL : %p ", board1);
 display_result (board1 != NULL);

 /* Checking board_delete() */

 board_delete (NULL);
 printf ("board_delete (NULL) : true ");
 display_result (true);

 board_delete (board0);
 printf ("board_delete (board0) : true ");
 display_result (true);

 board_delete (board1);
 printf ("board_delete (board1) : true ");
 display_result (true);

 /* Checking board_set() */

 board0 = board_new (4, 4);
 printf ("(board0 = board_set (4, 4)) != NULL : %p ", board0);
 display_result (board0 != NULL);

 result = board_set (NULL, 1, 2, 2);
 printf ("board_set (NULL, 1, 2, 2) == -1 : %d ", result);
 display_result (result == -1);

 result = board_set (board0, 0, 2, 2);
 printf ("board_set (board0, 0, 2, 2) == -1 : %d ", result);
 display_result (result == -1);

 result = board_set (board0, 1, 2, -1);
 printf ("board_set (board0, 1, 2, -1) == -1 : %d ", result);
 display_result (result == -1);

 result = board_set (board0, 1, -1, 2);
 printf ("board_set (board0, 1, -1, 2) == -1 : %d ", result);
 display_result (result == -1);

 result = board_set (board0, 1, 2, 5);
 printf ("board_set (board0, 1, 2, 5) == -1 : %d ", result);
 display_result (result == -1);

 result = board_set (board0, 1, 5, 2);
 printf ("board_set (board0, 1, 5, 2) == -1 : %d ", result);
 display_result (result == -1);

 result = board_set (board0, 1, 2, 2);
 printf ("board_set (board0, 1, 2, 2) == 1 : %d ", result);
 display_result (result == 1);

 result = board_set (board0, 1, 2, 2);
 printf ("board_set (board0, 1, 2, 2) == 0 : %d ", result);
 display_result (result == 0);

 result = board_set (board0, 2, 2, 3);
 printf ("board_set (board0, 2, 2, 3) == 1 : %d ", result);
 display_result (result == 1);

 /* Checking board_get() */

 result = board_get (NULL, 2, 2);
 printf ("board_get (NULL, 2, 2) == -1 : %d ", result);
 display_result (result == -1);

 result = board_get (board0, -1, 2);
 printf ("board_get (board0, -1, 2) == -1 : %d ", result);
 display_result (result == -1);

 result = board_get (board0, 2, -1);
 printf ("board_get (board0, 2, -1) == -1 : %d ", result);
 display_result (result == -1);

 result = board_get (board0, 5, 2);
 printf ("board_get (board0, 5, 2) == -1 : %d ", result);
 display_result (result == -1);

 result = board_get (board0, 2, 5);
 printf ("board_get (board0, 2, 5) == -1 : %d ", result);
 display_result (result == -1);

 result = board_get (board0, 1, 1);
 printf ("board_get (board0, 1, 1) == 0 : %d ", result);
 display_result (result == 0);

 result = board_get (board0, 2, 2);
 printf ("board_get (board0, 2, 2) == 1 : %d ", result);
 display_result (result == 1);

 result = board_get (board0, 2, 3);
 printf ("board_get (board0, 2, 3) == 2 : %d ", result);
 display_result (result == 2);

 /* Checking board_copy() */

 board1 = board_copy (NULL);
 printf ("board_copy (NULL) == NULL : %p ", board1);
 display_result (board1 == NULL);

 board1 = board_copy (board0);
 printf ("board_copy (board0) != NULL : %p ", board1);
 display_result (board1 != NULL &&
		 board_get (board1, 1, 1) == 0 &&
		 board_get (board1, 2, 2) == 1 &&
		 board_get (board1, 2, 3) == 2);

 /* Checking board_clear() */

 board_clear (NULL);
 printf ("board_clear (NULL) : true ");
 display_result (true);

 board_clear (board1);
 printf ("board_clear (board1) : true ");
 display_result (board1 != NULL &&
		 board_get (board1, 1, 1) == 0 &&
		 board_get (board1, 2, 2) == 0 &&
		 board_get (board1, 2, 3) == 0);


 /* Checking board_count_empty_cells() */

 result = board_count_empty_cells (NULL);
 printf ("board_count_empty_cells (NULL) == 0 : %d ", result);
 display_result (result == 0);

 result = board_count_empty_cells (board0);
 printf ("board_count_empty_cells (board0) == 14 : %d ", result);
 display_result (result == 14);

 result = board_count_empty_cells (board1);
 printf ("board_count_empty_cells (board1) == 16 : %d ", result);
 display_result (result == 16);

 /* Checking board_win() */

 result = board_win (NULL, 3);
 printf ("board_win (NULL, 3) == -1 : %d ", result);
 display_result (result == -1);

 result = board_win (board0, -1);
 printf ("board_win (board0, -1) == -1 : %d ", result);
 display_result (result == -1);

 result = board_win (board0, 0);
 printf ("board_win (board0, 0) == -1 : %d ", result);
 display_result (result == -1);

 result = board_win (board0, 3);
 printf ("board_win (board0, 3) == 0 : %d ", result);
 display_result (result == 0);

 result = board_win (board0, 1);
 printf ("board_win (board0, 1) == 1 || 2 : %d ", result);
 display_result (result == 1 || result == 2);

 /* Check win with row */
 board1 = board_copy (board0);
 result = board_set (board1, 1, 2, 0);
 result = board_set (board1, 1, 2, 1);
 result = board_win (board1, 3);
 printf ("board_win (board1, 3) = 1 : %d ", result);
 display_result (result == 1);
 board_delete (board1);

 /* Check win with column */
 board1 = board_copy (board0);
 result = board_set (board1, 1, 0, 2);
 result = board_set (board1, 1, 1, 2);
 result = board_win (board1, 3);
 printf ("board_win (board1, 3) = 1 : %d ", result);
 display_result (result == 1);
 board_delete (board1);

 /* Check win with left diagonal */
 board1 = board_copy (board0);
 result = board_set (board1, 1, 0, 0);
 result = board_set (board1, 1, 1, 1);
 result = board_win (board1, 3);
 printf ("board_win (board1, 3) = 1 : %d ", result);
 display_result (result == 1);
 board_delete (board1);

 /* Check win with right diagonal */
 board1 = board_copy (board0);
 result = board_set (board1, 1, 3, 1);
 result = board_set (board1, 1, 1, 3);
 result = board_win (board1, 3);
 printf ("board_win (board1, 3) = 1 : %d ", result);
 display_result (result == 1);
 board_delete (board1);

 /* Check board_display() */
 printf("\n");
 board_display (board0, stdout);
 printf ("board_display (board0, stdout) : true ");
 display_result (true);
 board_delete (board0);

 return EXIT_SUCCESS;
}
