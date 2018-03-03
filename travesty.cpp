#include <cstdlib> // srand() and rand()
#include <ctime> // time()
#include <iostream>	//cout
#include <fstream> //file
#include <iomanip> //setw

using namespace std;

//********************
// global declarations
//********************

// constants
const unsigned OUTPUT_SIZE = 1000;
const unsigned LINE_LENGTH = 80;
const unsigned PREFIX_SIZE = 1;
const unsigned NUM_TABLE_INDEX = 27;

// travesty structure
char table_index[NUM_TABLE_INDEX] =  {'@',
                                      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                      'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}; //array
unsigned prefix_count[NUM_TABLE_INDEX];  // count for each prefix, array
unsigned suffix_count_wrt_prefix[NUM_TABLE_INDEX][NUM_TABLE_INDEX]; // 2D array of suffix count w.r.t. prefix
unsigned total_prefix_count;   // total number of prefix


//********************
// function prototypes 
//********************
// random returns a number randomly and uniformly between 1 and limit
unsigned random(unsigned);

// results: the travesty-structure is initialized (or created)
void initialize_travesty();

// requires: initial_travesty() is already executed
// results: the pair (prefix , s) is added to travesty-structure
void update_travesty(char prefix, char s);

// requires: update_travesty() is already executed
// results: prefix is chosen with probability equal to its frequency
char choose_prefix();

// results: suffix s is chosen with proability equal to its frequency w.r.t. prefix
char choose_suffix(char prefix);

// results: the frequencies of prefixes and suffixes in the travesty-structure is printed out in a useful way
void print_travesty();


//*************
// main program
//*************
int main() {
	unsigned seed = time(0); // get the system time
	srand(seed); // seed the random number generator

	char ch; //char to be read at read position
	char temp; //store char into temp for prefix so it can be saved when it checks for
	           //next char as a suffix
	fstream file;
	string filename;

	// put your code here
	initialize_travesty(); //initialize the tables

	cout << "enter a file name: ";
	cin >> filename;
	
	//open data file to read in each character one by one
	file.open(filename, ios::in);
	
	if (file) { //check if file exists   
				//assign one char as prefix and one char as suffix
				//so they can be passed as parameters
				
		file.get(ch); //get first character of the file
		
		//read until end of file
		while (file) { 
			//if ch isn't eof then store ch into temp to pass as prefix parameter
			if (ch != file.eof()) {
				//Note: previous suffix was ch so it has to be stored in temp as the new prefix
				//saved the prefix to temp
							temp = ch; 
			}
			
			//get next char as suffix/new suffix
			file.get(ch); //now reading suffix and storing it to ch as suffix parameter
		
			//pass prefix and suffix variables and store the pair in the travesty structure
			update_travesty(temp, ch);  
		}
		file.close(); //close the file when it's done
		print_travesty();

		int count = 0; //count to keep track of max amount of characters
		char prefix = '\0'; 
		char suffix = '\0';
		
		while (count < OUTPUT_SIZE) {
			for (int j = 0; j < LINE_LENGTH && count < OUTPUT_SIZE; j+=2) {
				prefix = choose_prefix(); //store chosen prefix into prefix
				suffix = choose_suffix(prefix); //store chosen suffix into suffix

				//prevent printing double spaces
				if (prefix != ' ' || suffix != ' ') { 
					cout << prefix << suffix;
					count += 2;
				}
			}
			cout << endl;
		
		}	
    } 
	//*********************
// function definitions
//*********************

unsigned random(unsigned limit) {
	return (rand() % limit + 1);
}

void initialize_travesty() {
	//initialize 2 tables
	//one for prefix count and one for suffix count
	//prefix and suffix tables first element is '@' which is blank
	
	//initialize prefix count table
	for(int i=0; i < NUM_TABLE_INDEX; i++) {
		prefix_count[i] = 0;
	}
	//initialize suffix count wrt prefix 2D array table and set all values to 0
	for(int i=0; i < NUM_TABLE_INDEX; i++){
		for(int j=0; j<NUM_TABLE_INDEX;j++){
			suffix_count_wrt_prefix[i][j] = 0;
		}
	}
}

void update_travesty(char prefix, char s) {
	//increment the particular prefix count in prefix table
	//increment suffix count in the suffix table
	int count = 0; //if prefix is found count is incremented and exit the loop
	int index = 0; //save the index of where the prefix was found
	
	//loop through prefix table to find the char
	for (int i=0;i < NUM_TABLE_INDEX; i++) {
		//check for spaces since '@' stands for space
	    //once found break out of loop
		if(prefix == ' ' || prefix == '\n') {
			prefix_count[0] += 1;
			count++; 
			total_prefix_count++;
			break;
		}
		//increment count in the prefix table if found
		if(table_index[i] == prefix) {
			prefix_count[i] += 1;
			total_prefix_count++;
			count++;
			index = i;
			break;
		}
	}
	
	//if prefix is found 
	if (count == 1) {
		//loop through suffix table to find suffix wrt prefix
		//Example prefix is A and suffix is B
		//suffix count is incremented in array[1][2]
		//start at the index where prefix is
		for(int i=index; i < NUM_TABLE_INDEX; i++){
			for(int j=0; j<NUM_TABLE_INDEX;j++){
				//check for '.' and add it to [0][0]
			    //note: '.' equals two spaces which equals to 2 '@'
			    if(s == '.' || s == ' ' || s == '\n') {
			        suffix_count_wrt_prefix[index][0] += 1;
			        break;
	        	}
				
				//increment count when suffix is found and break out of loop
			    if (table_index[j] == s){
				    suffix_count_wrt_prefix[index][j] += 1;
			    	break;
			    }	
		    }
		  break;
		}
	}
	
	
}

void print_travesty(){
	//prefix table and suffix table will be combined into 1 giant table
	
	//count and prefix labels
	cout << setw(5) << "CNT" << setw(5) << "PFX";
	
	for(int i=0; i < NUM_TABLE_INDEX; i++) {
	    //print table index horizontally
		cout << setw(5) << table_index[i] ;
	}
	
	cout << endl;
	
	//print prefix count table and suffix table together
	//1D array and 2D array visually merged into one table 
	//note: remember prefix table indices are rows and not columns
	for(int i=0; i < NUM_TABLE_INDEX; i++) {
	    //prints out the count for each char in the table_index
		//count is displayed on the left for prefix
		cout << setw(5) << prefix_count[i] << setw(5) << table_index[i];
		
		//count of suffixes wrt prefix is arranged to be printed 
		//with prefix table so only 1 table is shown
		for(int j=0; j<NUM_TABLE_INDEX;j++){
		    //prints the suffix count on the right of the table_index column
			cout << setw(5) << suffix_count_wrt_prefix[i][j];
		}
		//go to next line after a row of 27
		cout << endl;
	}
	
	cout << endl;
	
	//print the total prefix count
	cout << "The total prefix count is " << total_prefix_count << endl;
}

char choose_prefix() {
	unsigned r, accum;
	char curr_table_index;

	r = random(total_prefix_count); // pick a number r that is randomly and uniformly distributed between 1 and total_prefix_count

	accum = 0;
	curr_table_index = '@'-1; // the character, '?',  precedes '@'
	while (accum < r) {
	   curr_table_index++;  // the succeed character
	   accum += prefix_count[curr_table_index-'@']; // accumulate the frequency of each prefix
	}

	return ((curr_table_index == '@') ? ' ' : curr_table_index);  // return the actual character
}

char choose_suffix(char prefix){
	//global variables needed: total prefix count, suffix count
	//Ex. if prefix is 'A' choose suffix based on how common the char would follow the prefix 'A'
	//frequency formula = suffix count for 'A'/prefix count for 'A'
	unsigned r, accum;
	char curr_table_index;
	int index = 0;	//index of where prefix is located
	int count = 1; //holds the prefix count of the particular char, default is 1
	
	//find where the prefix is in the table and save the count of that prefix 
	for(int i = 0; i < NUM_TABLE_INDEX; i++){
		//if found then index of prefix is saved
		if (table_index[i] == prefix) {
			index = i;
			//if prefix count is bigger than 1 then update variable for count
			//break out of loop when prefix is found 
			if (prefix_count[i] > 1)
				count = prefix_count[i];
			break;
		}
		
	}

	//smallest r can be is 1
	r = random(count); // pick a number r that is randomly and uniformly distributed between 1 and prefix count
	//random method ex: 78%3 + 1 = 27

	accum = 0;
	curr_table_index = '@'-1; // the character, '?',  precedes '@'

	//if no suffix follows the chose prefix then suffix must be chosen randomly
	int rsuffix = 0; //index of random suffix 

	while (accum < r) {
		curr_table_index++;  // the succeed character
		if (curr_table_index == 'Z' + 1 && accum < r) {
			accum += r;
			rsuffix = random(NUM_TABLE_INDEX)-1;
			curr_table_index = table_index[rsuffix];
			break;
		}
		accum += suffix_count_wrt_prefix[index][curr_table_index-'@']; // accumulate the frequency of each suffix
	}

	return ((curr_table_index == '@') ? ' ' : curr_table_index);  // return the actual character
}
}
