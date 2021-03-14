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
const char* FLAG_OPTIONS_CHAR = "-o";
const char* FLAG_OCCURRENCES_CHAR = "o";
const char* FLAG_LINE_NUMBERS_CHAR = "l";
const char* FLAG_REVERSE_SEARCH_CHAR = "r";
const char* FLAG_IGNORE_CASE_CHAR = "i";

// Prototypes
void search_from_file(string sub_string, string filename, bool show_line_numbers, bool show_occurrences, bool reverse_search, bool ignore_case);
void to_lower_case(string& str);



void to_lower_case(string& str)
{
	// Convert a string to all lower case
	for(int i = 0; i < str.length(); i++)
	{
		str[i] = tolower(str[i]);
	}
}

void search_from_file(string sub_string, string filename, bool show_line_numbers, bool show_occurrences, bool reverse_search, bool ignore_case)
{
	// Function that handles reading file and searching from file.
	fstream searchfile;
	searchfile.open(filename, ios::in);
	
	// declaring variables
	int line_number = 0, occurrences = 0, not_occurrences = 0;
	string file_line, file_line_temp, sub_string_temp = sub_string;
	bool sub_string_found = false;

	// make sub_string_temp lowercase if ignore_case is true.
	if (ignore_case)
	{
		to_lower_case(sub_string_temp);
	}


	// Check that file could be read correctly.
	if (!searchfile)
	{
		cout << "An exception occurred." << endl;
	}


	// searching for occurrences and countign them.
	else 
	{
		while (!searchfile.eof())
		{
			line_number++;
			getline(searchfile, file_line);
			file_line_temp = file_line;
			
			// if ignore_case is true, convert file_line_temp to lowercase. 
			if (ignore_case)
			{
				
				to_lower_case(file_line_temp);
			} 

			if (file_line_temp.find(sub_string_temp) != string::npos)
			{
				sub_string_found = true;
			}


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
			}

			sub_string_found = false;
		}
	}

	searchfile.close();

	// Printed if show_occurrences is true
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
	int found_index;
	string bigStr, subStr, filename;

	// Declaring option flags as boolean values.
	bool flag_show_occurrences = false;
	bool flag_show_line_numbers = false;
	bool flag_reverse_search = false;
	bool flag_ignore_case = false;
	

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


	else 
	{
		cout << "An exception occurred. No searchword given." << endl;
	}

	return EXIT_SUCCESS;
}
