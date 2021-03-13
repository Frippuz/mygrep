// TODO: proper user guide here
/* 
Running the program:
./mygrep -flags searchword filename.txt 
flags start with -o
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

// Declaring flags as constants 
// TODO: Do these need to be global?
const char* FLAG_OPTIONS_CHAR = "-o";
const char* FLAG_OCCURRENCES_CHAR = "o";
const char* FLAG_LINE_NUMBERS_CHAR = "l";



/*
void output(int found_index, string subStr, string bigStr)
{
	// Printing output
	if (found_index != string::npos)
	{
		cout << "\"" <<subStr << "\" found in \"" << bigStr << "\" in position " << found_index << endl;
	}
	else
	{
		cout <<"\"" << subStr << "\" NOT found in \"" << bigStr << "\"" << endl;
	}
}
*/

void search_from_file(string subStr, string filename, bool show_line_numbers, bool show_occurrences)
{
	// Read lines from file and print them to console.
	fstream searchfile;
	searchfile.open(filename, ios::in);
	
	// declare variables
	int line_number = 0, occurrences = 0;
	string file_line;

	if (!searchfile)
	{
		// TODO: check output 
		cout << "error: Could not open file." << endl;
	}

	else
	{
		while (!searchfile.eof())
		{
			line_number++;
			getline(searchfile, file_line); 

			if (file_line.find(subStr) != string::npos)
			{
				occurrences++;
				
				// if show_line_numbers is true also print line line numbers,
				// if not print only line content.
				if(show_line_numbers)
				{
					cout << line_number << ":" << file_line << endl;
				}
				
				else {cout << file_line << endl;}
			}
		}
	}

	if(show_occurrences)
	{
		cout << "\nOccurrences of lines containing \"" << subStr << "\": " << occurrences << endl;
	}
}


int main(int argc, char* argv[])
{
	// TODO: consider moving these to their approprriate satements.
	int found_index;
	string bigStr, subStr, filename;

	// Declaring option flags as boolean values.
	//bool flag_options = false; // TODO: flag_options may be unneccessary! 
	bool flag_show_occurrences = false;
	bool flag_show_line_numbers = false;
	
	// ask string and substring.
	// Done only when arguments are given.
	if (argc == 1)
	{
		cout << "Give a string from which to search for: ";
		getline(cin, bigStr);


		cout << "Give search string: ";
		getline(cin, subStr);

		
		// find match and assign value to found_index.
		found_index = bigStr.find(subStr);

		// printing output
		if (found_index != string::npos)
		{
			cout << "\"" <<subStr << "\" found in \"" << bigStr << "\" in position " << found_index << endl;
		}
		else
		{
			cout <<"\"" << subStr << "\" NOT found in \"" << bigStr << "\"" << endl;
		}
	}



	// When a file and searchword are given, but no flags.
	else if (argc == 3 and argv[2] != "")
	{
		subStr = argv[1];
		filename = argv[2];
		search_from_file(subStr, filename,flag_show_line_numbers, flag_show_occurrences);
	}




	// TODO: make function call when flags are given.

	// When flags, searchword and filename are given.
	else if (argc == 4 and argv[2] != "")
	{
		subStr = argv[2];
		filename = argv[3];



		// check what flags are given.
		// couts are for testing
		
		// Check that "-o" is first in argv[1].
		if (strstr(argv[1], FLAG_OPTIONS_CHAR) == argv[1])
		{	

			// Remove first two elements ("-" and "o" ) from argv[1] 
			argv[1] = &argv[1][2];
			
			//flag_options = true; // this is may not be necessary


			if (strstr(argv[1], FLAG_OCCURRENCES_CHAR))
			{
				flag_show_occurrences = true;
			}


			if (strstr(argv[1], FLAG_LINE_NUMBERS_CHAR))
			{
				flag_show_line_numbers = true;
			}

			search_from_file(subStr, filename,flag_show_line_numbers, flag_show_occurrences);
		}

		// incorrect flags, give user and error message.
		else 
		{
			cout << "error: Incorrect options." << endl;
		}
	}


	// If no searchword is given. 
	else 
	{
		
		// TODO: give user proper error message!
		
		cout << "error" << endl;
		
		cout << argc << " " << argv << endl;

		for(int i = 0 ; i < sizeof(*argv); i++)
		{
			cout << "argument " << i << ": " << argv[i] << endl;
		}
	}

	return EXIT_SUCCESS;
	

// TODO: delete these
# if 0
	// These may be needed later
	
	// Converting strings to C-style const char*
	const char* bigStr_C = bigStr.c_str();
	const char* subStr_C = subStr.c_str();

	const char* result = strstr(bigStr_C, subStr_C);
	cout << result << endl;
#endif
}
