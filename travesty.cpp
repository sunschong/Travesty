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
}
