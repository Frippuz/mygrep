#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;


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

void from_file_no_flags(string subStr, string filename)
{
	// TODO: only prints word and line number, not whole line.
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
		while (searchfile >> file_line)
		{
			line_number++;
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
// for testing argc and argv remove later
#if 0
	
	cout << argc << " " << argv << endl;

	for(int i = 0 ; i < sizeof(*argv); i++)
	{
		cout << "argument " << i << ": " << argv[i] << endl;
	}
#endif

	// declaring variables
	


	// needed only without arguments?
	int found_index;
	string bigStr, subStr, filename;

	// ask string and substring.
	// Done only if no arguments are given.
	// TODO: consider making this it's own function.
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


	else if (argc == 3 and argv[2] != "")
	{
		filename = argv[2];
		subStr = argv[1];
		from_file_no_flags(subStr, filename);
	}

	else 
	{
		cout << "error" << endl;
		
		cout << argc << " " << argv << endl;

		for(int i = 0 ; i < sizeof(*argv); i++)
		{
			cout << "argument " << i << ": " << argv[i] << endl;
		}
	}


	




	return EXIT_SUCCESS;
	


# if 0
	// These may be needed later.klngh
	
	// Converting strings to C-style const char*
	const char* bigStr_C = bigStr.c_str();
	const char* subStr_C = subStr.c_str();

	const char* result = strstr(bigStr_C, subStr_C);
	cout << result << endl;
#endif
}
