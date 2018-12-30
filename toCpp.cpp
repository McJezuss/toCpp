#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sys/stat.h>

using namespace std;

bool fileExists(const string& file)
{
	struct stat buf;
	return (stat(file.c_str(), &buf) == 0);
}

int main(int argc, char const *argv[])
{
	string fileName = "";
	if (argc < 2)
	{
		bool nameGiven = false;
		while(!nameGiven){
			cout<<"Please enter a filename to convert: ";
			cin>>fileName;
			if(fileName != "") {nameGiven = true;}
		}
	}
	else {fileName = argv[1];}
	//====================================================
	//Code to check if file exists in current context 
	//====================================================
	
	bool fExists = fileExists(fileName);
	
	if (fExists)
	{
		string className = "";
		for (int i = 0; i < fileName.length()-2; ++i)
		{
			className += fileName[i];
		}

		string CN = className + ".cpp";
		ofstream writeFile (CN); //writeFile

		ifstream readFile (fileName); //readFile
		string line;

		if (readFile.is_open())
		{
			if (writeFile.is_open())
			{
				writeFile<<"#include \"" << className << ".h\""<<endl;
				writeFile<<"using namespace std;"<<endl;
				writeFile<<className << "::" << className << "()" << endl <<
				"{" << endl << endl << "}" << endl << endl;
				writeFile<<className << "::~" << className << "()" << endl <<
				"{" << endl << endl << "}" << endl << endl;

				while (getline(readFile, line)){
					//===============================================================
					// Code to check for and find position of "(" , ")" and " "
					//===============================================================
					size_t foundOpenBracket = line.find("(");
					size_t foundClosedBracket = line.find(")");
					size_t foundSpace = line.find(" ");
					bool bFoundOpenBracket = false;
					bool bFoundClosedBracket = false;
					bool bFoundSpace = false;

					if (foundOpenBracket != string::npos) //found (
					{
						bFoundOpenBracket = true;
					}

					if (foundClosedBracket != string::npos) //found )
					{
						bFoundClosedBracket = true;
					}

					if (foundSpace != string::npos) //found space
					{
						bFoundSpace = true;
					}

					if (bFoundOpenBracket && bFoundClosedBracket && bFoundSpace) //function declaration
					{
						string type = line.substr(1, foundSpace);
						string functionName = line.substr(foundSpace+1, line.length()-2);

						writeFile << type << " " << className << "::" << functionName << endl << "{" <<endl << endl << "}" <<endl << endl; 
					}
				}
				writeFile.close();
			}
			else {cout << "File could not be created." <<endl;}
			readFile.close();
		}
		else {cout << "File could not be opened." <<endl;}

	}
	else {cout << "Please provide an existing file name." <<endl;}

	return 0;
}