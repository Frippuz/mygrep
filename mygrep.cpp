#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
//#include <stdio.h>

using namespace std;

int main(int argc, char* argv[])
{

	cout << argc << " " << argv << endl;

	for(int i = 0 ; i < sizeof(*argv); i++)
	{
		cout << "argument " << i << ": " << argv[i] << endl;
	}

	return 0;

	// declaring variables
	string bigStr, subStr;
	int found_index;
	
	// ask string and substring
	cout << "Give a string from which to search for: ";
	getline(cin, bigStr);


	cout << "Give search string: ";
	getline(cin, subStr);

	// find match and give value to found_index.
	found_index = bigStr.find(subStr);
	
	// Printing output
	if (found_index != string::npos)
	{
		cout << "\"" <<subStr << "\" found in \"" << bigStr << "\" in position " << found_index << endl;
	}
	else
	{
		cout <<"\"" << subStr << "\" NOT found in \"" << bigStr << "\"" << endl;
	}
	
	return EXIT_SUCCESS;
	


# if 0
	// These may be needed later.
	
	// Converting strings to C-style const char*
	const char* bigStr_C = bigStr.c_str();
	const char* subStr_C = subStr.c_str();

	const char* result = strstr(bigStr_C, subStr_C);
	cout << result << endl;
#endif
}
