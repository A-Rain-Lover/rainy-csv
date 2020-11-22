#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <csv.h>



int main(int argc, char **argv){
	(void) argc;
	(void) argv;
	
	/* Load the csv file */
	csv_t csv = csv_load("./test.csv");

	/* Add a row */
	char *row[] = {"5","Emilia", "20"};
	csv_append(csv, row);
	
	/* Show the result */
	csv_print(csv);
	
	/* Save changes */
	csv_save(csv);

	/* Free the memory */
	csv_destroy(csv);
	
	return 0;
}
