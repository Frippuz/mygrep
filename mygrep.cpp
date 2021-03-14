// TODO: proper user guide here
// TODO: rename subStr to sub_string
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
const char* FLAG_REVERSE_SEARCH_CHAR = "r";
const char* FLAG_IGNORE_CASE_CHAR = "i";

// Prototypes
void search_from_file(string sub_string, string filename, bool show_line_numbers, bool show_occurrences, bool reverse_search, bool ignore_case);
string string_to_lower(string str);



// converts a string to all lowercase.
void to_lower_case(string& str)
{
   for(int i = 0; i < str.length(); i++)
   {
      str[i] = tolower(str[i]);
   }
}


void search_from_file(string sub_string, string filename, bool show_line_numbers, bool show_occurrences, bool reverse_search, bool ignore_case)
{
	fstream searchfile;
	searchfile.open(filename, ios::in);
	
	// declaring variables
	int line_number = 0, occurrences = 0, not_occurrences = 0;
	string file_line, file_line_temp, sub_string_temp = sub_string;
	bool sub_string_found = false;

	
	if (ignore_case)
	{
		to_lower_case(sub_string_temp);
	}

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
			sub_string_found = false;
			getline(searchfile, file_line);

			// if ignore_case is true, convert file_line_temp to lowercase. 
			if (ignore_case)
			{
				file_line_temp = file_line;
				to_lower_case(file_line_temp);

				//testing
				//cout << "sub_string: " << sub_string << "sub_string_temp: " << sub_string_temp << endl;
				//cout << "file_line " << file_line << "file_line_temp: " << file_line_temp << endl;
			} 

			if (file_line_temp.find(sub_string_temp) != string::npos)
			{
				sub_string_found = true;
			}


			// 			if ((file_line_temp.find(sub_string_temp) != string::npos) and !reverse_search)
			if (sub_string_found and !reverse_search)
			{
				occurrences++;
				
				// if show_line_numbers is true also print line line numbers,
				// if not print only line content.
				//TODO: might be able to make this neater
				
				if (show_line_numbers)
				{
					cout << line_number << ":";
				}
				
				cout << file_line << endl;
			}
			
			else if (!sub_string_found and reverse_search)
			{
				not_occurrences++;
				
				if	(show_line_numbers)
				{
					cout << line_number << ":";
				}
				
				cout << file_line << endl;
				
				/*
				if	(show_line_numbers)
				{
					cout << line_number << ":" << file_line << endl;
				}
				else
				{
					cout << file_line << endl;
				}
				*/
			}

			sub_string_found = false;
		}
	}

	// Printing to be done if show occurrences is
	if (show_occurrences and !reverse_search)
	{
		cout << "\nOccurrences of lines containing \"" << sub_string << "\": " << occurrences << endl;
	}

	else if (show_occurrences and reverse_search)
	{
		cout << "\nOccurrences of lines NOT containing \"" << sub_string << "\": " << not_occurrences << endl;
	}
}


int main(int argc, char* argv[])
{
	// TODO: consider moving these to their appropriate satements.
	int found_index;
	string bigStr, subStr, filename;

	// Declaring option flags as boolean values.
	//bool flag_options = false; // TODO: flag_options may be unneccessary! 
	bool flag_show_occurrences = false;
	bool flag_show_line_numbers = false;
	bool flag_reverse_search = false;
	bool flag_ignore_case = false;
	
	// TODO: consider dividing these into functions, should bee quite smooth, also make prototypes

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
		search_from_file(subStr, filename, flag_show_line_numbers, flag_show_occurrences, flag_reverse_search, flag_ignore_case);
	}




	// TODO: make function call when flags are given.

	// When flags, searchword and filename are given.
	else if (argc == 4 and argv[2] != "")
	{
		subStr = argv[2];
		filename = argv[3];
		
		// Check that "-o" is first in argv[1].
		if (strstr(argv[1], FLAG_OPTIONS_CHAR) == argv[1])
		{	

			// Remove first two elements ("-" and "o" ) from argv[1] 
			argv[1] = &argv[1][2];
			
			// look for flag characters in argv[1] and set corresponding flags to true if found.
			if (strstr(argv[1], FLAG_OCCURRENCES_CHAR))
			{
				flag_show_occurrences = true;
			}

			if (strstr(argv[1], FLAG_LINE_NUMBERS_CHAR))
			{
				flag_show_line_numbers = true;
			}

			if (strstr(argv[1], FLAG_REVERSE_SEARCH_CHAR))
			{
				flag_reverse_search = true;
			}

			if (strstr(argv[1], FLAG_IGNORE_CASE_CHAR))
			{
				flag_ignore_case = true;
			}

			search_from_file(subStr, filename,flag_show_line_numbers, flag_show_occurrences, flag_reverse_search, flag_ignore_case);
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
