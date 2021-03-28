/**
 *	@file csv.h
 * */

#ifndef _CSV_H_
#define _CSV_H_

#include <stddef.h>

typedef void *csv_t;

/**
 * @brief Parses a csv string to a csv_t
 *
 * @param raw_csv the raw csv string
 * @param length length of the string
 * @note The default filename will be untitled.csv
 * so consider changing the filename when saving
 * 
 * @return the resulting csv_t instance
 */
csv_t *csv_parse(char *raw_csv, size_t length);

/**
 * @brief Loads a .csv file
 *
 * @param path Path to the csv file to load
 * @note No need to a close function since the file descriptor is
 * closed automatically after loading, and reopened when needed
 * (eg. when saving)
 *
 * @return csv_t instance representing the .csv file
 */
csv_t	csv_load(const char *path);

/**
 * @brief Saves changes to the actual file
 *
 * @param csv The csv_t instance to save (obviously)
 */
void	csv_save(csv_t csv);

/**
 * @brief Destroys a csv_t instance
 *
 * @param csv The csv to destroy (obviously)
 */
void	csv_destroy(csv_t csv);

/**
 * @brief Initializes an empty csv_t instance
 *
 * @param col_count Number of columns
 * @param col_names Columns' titles
 * @param file_path Path to the file, used when saving
 *
 * @return A new initialized csv_t instance
 * 
 * @note For some reason, the fact that parameter names are of equal
 * length made me so happy lol :D
 *
 */
csv_t	csv_init(size_t col_count, char **col_names, const char *file_path);

/**
 * @brief Fetches one row
 *
 * @param csv The csv_t instance to fetch from
 * @param row_nbr The number of the row to get 
 * @param[out] out Where to put it
 * 
 */
void	csv_get_row(csv_t csv, size_t row_nbr, char **out);

/**
 * @brief fetches one value
 *
 * @param csv The csv_t instance to fetch from
 * @param row_nbr The number of the row 
 * @param col_nbr The number of the column
 * 
 * @return the value as a char*
 */
char*	csv_get_value(csv_t csv, size_t row_nbr, size_t col_nbr);

/**
 * @brief Appends a whole row to the end of the csv
 *
 * @param csv The csv_t instance to append to
 * @param row The row to append 
 * 
 */
void	csv_append(csv_t csv, char **row);

/**
 * @brief Adds a whole row in the given position
 *
 * @warning Not implemented yet
 * @param csv The csv_t instance to add to
 * @param position The index where the new row should be
 * @param row The row to add 
 * 
 */
void	csv_add_at(csv_t csv, size_t position, char **row);

/**
 * @brief Deletes a whole row from the csv
 *
 * @warning Not implemented yet
 * @param csv The csv_t instance to delete from
 * @param row_nbr The row number to delete 
 * 
 */
void	csv_delete_row(csv_t csv, size_t row_nbr);

/**
 * @brief Edits a value
 *
 * @param csv The csv_t instance to edit
 * @param row_nbr The value's row number 
 * @param col_nbr The value's column number
 * @param value The new value
 * 
 */
void	csv_edit_value(csv_t csv, size_t row_nbr, size_t col_nbr, char *new_value);

/**
 * @brief Returns the number of rows
 *
 * @param csv The csv_t instance
 * 
 */
size_t	csv_count_rows(csv_t csv);

/**
 * @brief Returns the number of columns
 *
 * @param csv The csv_t instance
 * 
 */
size_t	csv_count_cols(csv_t csv);

/**
 * @brief Prints the formatted csv in the stdout
 *
 * @param csv The csv_t instance
 *
 * @warning This will print nightmares if the csv is long
 * or if the cells have long values 
 */
void	csv_print(csv_t csv);

#endif

/*!
 *
 * \mainpage Rainy CSV
 * An open source CSV manipulating library
 * <br />
 * \note This is still work in progress
 * 
 * <a href="https://www.github.com/computer-spectre/rainy-csv">Visit the GitHub repo</a>
 * 
 * \section gs Getting started
 * I found it somehow weired to make it compile to a `.a` file with only one file,
 * so just compile `csv.c` in your project and that's it.
 * <br />
 * <a href="csv_8h.html">This</a> is all you need in order to work with RainyCSV
 * \section l Licence
 * MIT License
 * 
 * Copyright (c) 2020 computer-spectre (Yuun)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * */

