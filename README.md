# Travesty 

/* The main program, function prototypes, and global variables are in the cpp file

program description:
 * an english text is given as input.  the program will read in
 * the text and store in a data structure which is called travesty
 * structure.  it consists of an array of prefix table.  the array
 * is index by a fixed length prefix.  the prefix table has two fields.
 * one is the total number of a particular prefix that appear in the text, while
 * the other field is the array of suffix count which is index by a single
 * character suffix from 'A' to 'Z' and '@'.
 *
 * the first part of the program will fill the travesty structure by reading
 * one (prefix, s) pair at a time from the input english text.
 *
 * the second part of the program will print out the travesty structure based on
 * the frequency of a prefix or suffix that appear in the original text.
 *
 * the third part of the program is to print out the random text.  i use a
 * "line_length" constant to determine the output line length.
 *
 *
 * assumptions:
 * 1. the input text must be in CAPITAL letters and only consists of
 *    'A' to 'Z' and ' '.
 *
 * 2. the file size must be greater than the prefix size
 *
 * 3. all the newline marks are treated as blanks
 *
 * 4. the end of file mark indicates the end of file and it won't be
 *    treated as a character.  Therefore, the last valid character of the file
 *    will be treated as suffix only
 *
 */
