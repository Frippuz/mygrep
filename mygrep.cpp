// TODO: proper user guide here
/* 
Running the program:
./mygrep -options searchword filename.txt 
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

void search_from_file(string subStr, string filename)
{
	// Read lines from file and print them to console.
	fstream searchfile;
	searchfile.open(filename, ios::in);
	
	int line_number;
	string file_line;

	if (!searchfile)
	{
		// TODO: check output 
		cout << "Could not open file." << endl;
	}

	else
	{
		while (!searchfile.eof())
		{
			line_number++;
			getline(searchfile, file_line); 

			if (file_line.find(subStr) != string::npos)
			{
				// TODO: incorrect formatting!!!
				cout << "line " << line_number  << ":  " << file_line << endl;
			}
		}
	}
}

int main(int argc, char* argv[])
{


// TODO: for testing argc and argv remove later
#if 0
	
	cout << argc << " " << argv << endl;

	for(int i = 0 ; i < sizeof(*argv); i++)
	{
		cout << "argv[" << i << "]: " << argv[i] << endl;
	}
#endif

	// Declaring variables
	int found_index;
	string bigStr, subStr, filename;

	// Declaring option flags boolean values
	bool flag_options = false;
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


	// TODO: does not currently support flags? fix this first or make another function call.

	// when a file and searchword are given, but no flags.
	else if (argc == 3 and argv[2] != "")
	{

		// This will need changes
		// Make one function to handle all flags?..... YES!
		filename = argv[2];
		subStr = argv[1];
		search_from_file(subStr, filename);
	}




	// TODo: make function call when flags are given.
	else if (argc == 4 and argv[2] != "")
	{
		// check what flags are given.
		// couts are for testing
		if (strstr(argv[1], FLAG_OPTIONS_CHAR)) // TODO: this method works, do this for rest of 
		{	
			//TODO: remove couts
			cout << "found at: " << *strstr(argv[1], FLAG_OPTIONS_CHAR) << endl;
			flag_options = true;
			cout << "flag options set to true\n";
		}
		if (strstr(argv[1], FLAG_OCCURRENCES_CHAR)) 
		{
			cout << "found at: " << *strstr(argv[1], FLAG_OCCURRENCES_CHAR) << endl;
			// TODO: this will cause a bug, since "o" is already found in "-o"
			// so this statement will trigger everytime an option is used. fix this!
			// "o" can not be in  second position of argv[1]
			flag_show_occurrences = true;
			cout << "flag show occurences set to true\n";
		}
		if (strstr(argv[1], FLAG_LINE_NUMBERS_CHAR))
		{
			cout << "found at: " << *strstr(argv[1], FLAG_LINE_NUMBERS_CHAR) << endl;
			flag_show_line_numbers = true;
			cout << "flag show line numbers set to true\n";
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
