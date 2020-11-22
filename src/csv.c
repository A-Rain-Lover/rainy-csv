#include <csv.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
	const char *file_path;
	char **data;
	size_t row_count;
	size_t col_count;
} csv_data_t;


csv_t *csv_parse(char *raw_csv, size_t length){
	csv_data_t *out;
	out = (csv_data_t*) malloc(sizeof(csv_data_t));

	out->row_count = 0;
	out->col_count = 0;

	/* This will be mainly used as index in the raw_csv */
	size_t i = 0; 

	/* Quick and maybe dirty way to get the number of columns */
	while(i++ < length){
		if(raw_csv[i] == ',') out->col_count++;
		if(raw_csv[i] == '\n') break;
	}
	++(out->col_count);
	out->data = (char**) malloc(out->col_count * sizeof(char*));
	
	/* Reset i since it was used in the previous loop */
	i = 0; 

	/* We need to make sure buffer is null terminated */
	char buffer[255] = "\0";

	/* This will be the index in buffer */
	size_t j = 0;

	/* This is a temporary variable to place a row */
	/* before adding it to the out struct  */
	char **row;
	row = (char**) malloc(out->col_count * sizeof(char*));
	for(size_t p = 0; p < out->col_count; p++)
		row[p] = (char*) malloc(255);

	/* Index in row */
	size_t k = 0;
	
	/* Will be storing the current character */
	char c;

	/*
	 * Alright, to summerize :
	 *
	 * i	:	index in csv_raw
	 * j	:	index in buffer
	 * k	:	index in row
	 *
	 * */
	
	while(i < length){
		c = raw_csv[i++];
		switch(c){
		case '\n': /* row --> out */
			/* To avoid line duplication problem that occurs when */
			/* having multiple \n in a row	*/
			if(!strcmp(buffer, "\0")) break;

			buffer[j++] = '\0';
			strcpy(row[k++], buffer);
			j = 0;
			
			buffer[0] = '\0';
			csv_append((csv_t)out, row);
			
			k = 0;
			break;
		case ' ' : /* Ignore whitespaces */
		case '\t':
			continue;
		case ',': /* buffer --> row*/
			buffer[j++] = '\0';
			strcpy(row[k++], buffer);
			j = 0;
			buffer[0] = '\0';
			break;
		default: /* c --> buffer*/
			buffer[j++] = c;
		}
	}
	
	out->file_path = "untitled.csv";


	for(size_t p = 0; p < out->col_count; p++)
		free(row[p]);
	free(row);
	
	return (csv_t) out;
}

csv_t	csv_load(const char *path){
	FILE *file;
	file = fopen(path, "r");
	if(!file) return NULL;

	char *csv_raw;
	size_t length;
	
	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);
	
	csv_raw = (char*) malloc(length);

	char c;
	size_t i = 0;
	while((c = fgetc(file)) != EOF)
		csv_raw[i++] = (char) c;
	csv_raw[length] = '\0';

	
		
	csv_t *out = csv_parse(csv_raw, length);
	
	((csv_data_t *) out)->file_path = path;
	
	fclose(file);
	free(csv_raw);

	return (csv_t) out;
}

void	csv_save(csv_t csv){
	csv_data_t *csv_data = (csv_data_t*) csv;
	FILE *file;
	file = fopen(csv_data->file_path, "w");
	if(!file) {
		fprintf(stderr, "Failed to open : %s", csv_data->file_path);
		return;
	}
	for(size_t i = 0; i < csv_data->row_count; i++){
		for(size_t j = 0; j < csv_data->col_count; j++){
			fprintf(file, "%s%s",	csv_get_value(csv, i, j),
									j == csv_data->col_count -1 ? "\n": ",");
		}
	}
	fclose(file);
}

void	csv_destroy(csv_t csv){
	csv_data_t *csv_data = (csv_data_t*) csv;
	size_t length = csv_data->row_count * csv_data->col_count;
	for(size_t i = 0; i < length; i++){
		free(csv_data->data[i]);
	}
	free(csv_data->data);
	free(csv_data);
}

csv_t	csv_init(size_t col_count, char **col_names, const char *file_path){
	csv_data_t *out;
	out = (csv_data_t*) malloc(sizeof(csv_data_t));

	out->row_count = 1;
	out->col_count = col_count;
	
	out->file_path = file_path;
	
	out->data = (char**) malloc(col_count * sizeof(char*));
	
	for(size_t i = 0; i < col_count; i++)
		out->data[i] = col_names[i];
	return (csv_t) out;
}

void	csv_get_row(csv_t csv, size_t row_nbr, char **out){
	csv_data_t *csv_data = (csv_data_t*) csv;
	for(size_t i = 0; i < csv_data->col_count; i++)
		out[i] = csv_data->data[row_nbr * csv_data->col_count + i];
}

char*	csv_get_value(csv_t csv, size_t row_nbr, size_t col_nbr){
	csv_data_t *csv_data = (csv_data_t*) csv;
	return csv_data->data[row_nbr * csv_data->col_count + col_nbr];
}

void	csv_append(csv_t csv, char **row){
	csv_data_t *csv_data = (csv_data_t*) csv;
	size_t n = ++(csv_data->row_count);
	
	csv_data->data = realloc(csv_data->data, n * csv_data->col_count * sizeof(char*));
	--n;
	for(size_t i = 0; i < csv_data->col_count; i++){
		csv_data->data[n * csv_data->col_count + i] = strdup(row[i]);
	}
}

void	csv_add_at(csv_t csv, size_t position, char **row);

void	csv_delete_row(csv_t csv, size_t row_nbr);

void	csv_edit_value(csv_t csv, size_t row_nbr, size_t col_nbr, char *new_value){
	csv_data_t *csv_data = (csv_data_t*) csv;
	size_t index = row_nbr * csv_data->col_count + col_nbr;
	csv_data->data[index] = new_value;
}

inline size_t	csv_count_rows(csv_t csv){
	csv_data_t *csv_data = (csv_data_t*) csv;
	return csv_data->row_count;
}

inline size_t	csv_count_cols(csv_t csv){
	csv_data_t *csv_data = (csv_data_t*) csv;
	return csv_data->col_count;
}

void	csv_print(csv_t csv){
	csv_data_t *csv_data = (csv_data_t*) csv;
	for(size_t i = 0; i < csv_data->row_count; i++){
		for(size_t j = 0; j < csv_data->col_count; j++){
			printf("%s%6s%s", "|"
							, csv_get_value(csv, i, j)
							, ((j+1) % (csv_data->col_count))?"":"|\n");
		}
	}		
}
