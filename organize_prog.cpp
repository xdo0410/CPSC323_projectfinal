#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include <cctype>
#include <algorithm>
using namespace std;

/*--------------------------PART ONE-------------------------*/

/*---------------Helper Functions for Part One---------------*/
// string trim for easy identifying a blank line.
inline std::string trim(const std::string &s)
{
	auto wsfront = std::find_if_not(s.begin(), s.end(), [](int c) {return std::isspace(c); });
	auto wsback = std::find_if_not(s.rbegin(), s.rend(), [](int c) {return std::isspace(c); }).base();
	return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
}

//return true if there are 2 consecutive spaces
bool bothAreSpaces(char lhs, char rhs)
{
	return ((lhs == rhs) && ((lhs == ' ') || (lhs == '\t')))
		|| ((lhs == '\t') && (rhs == ' '))
		|| ((lhs == ' ') && (rhs == '\t'));
}

string removeComments(const string& str)
{
	int n = str.length();
	string res;	// result string

				// Flags to indicate that comments have started or not.
	bool comment = false;

	//char prevChar = '\n';
	for (int i = 0; i < n-1; i++) //(n-1) to prevent from going beyond the length of the string hence illegal memory reference.
	{
		// If comment is on, then check for end of it
		if (comment == true && str[i] == '*' && str[i + 1] == ')')
		{
			comment = false;
			i++;
		}
		// If this character is in a comment, ignore it
		else if (comment)
			continue;

		// Check for beginning of comments and set the approproate flags
		else if (str[i] == '(' && str[i + 1] == '*')
		{
			comment = true;
			i++;
		}

		// If current character is a non-comment character, append it to result string
		else {
			// Only write one new line to prevent a blank line condition.
			//if (prevChar != '\n' || (prevChar == '\n' && str[i] != '\n'))
			res += str[i];
			//prevChar = str[i];
		} // else
	}
	return res;
}

string removeExtraSpaces(string &str)
{
	int n = str.length();
	string res;	// result string
	for (int i = 0; i < n; i++) {
		if (str[i] != ' ' && str[i] != '\t')
			res += str[i];
		else if ((str[i] == ' ' || str[i] == '\t')
				&& (i > 0 && (str[i - 1] != ' ' && str[i - 1] != '\t' && str[i - 1] != '\n'))
			)
			res += str[i];
	} // for
	return res;
}
string removeBlankLines(string &str)
{
	int n = str.length();
	string res;	// result string
	for (int i = 0; i < n; i++) {
		if (str[i] != '\n')
			res += str[i];
		else if (i > 0 && str[i] == '\n'  && str[i-1] != '\n')
			res += str[i];
	} // for
	return res;
}


bool isOperand(char & a)
{
	return (isalnum(a) || a == '_');
}

// Add space before and after each token
void addSpaceToken(string & str)
{
	int i = 1;
	while (i < str.length())
	{
		// if we found an operator, excluding '.' since 
		// "END." does not have space in between
		if (!isOperand(str[i]) && str[i] != '.')
		{
			// we insert space before and after it
			str.insert(i, " ");
			str.insert(i + 2, " ");
			i += 2;
		}
		++i;
	}
}

/*-------------------Function for Part One-------------------*/
void partOne()
{
	ifstream infile;
	ofstream outfile;

	string filename = "final1.txt";
	string outFilename = "final2.txt";

	string str, tempStr1, tempStr2;

	infile.open(filename.c_str());
	if (infile.fail()) {
		cout << "\nInvaild file name.\n";
		return;
	}
	//outfile.open(tempFilename.c_str());
	outfile.open(outFilename.c_str());

	if (infile.is_open())
	{
		while (getline(infile, str))
		{
			// copy content of file to tempStr1 line by line
			tempStr1 += str;
			// add a new line at the end of each line
			tempStr1 += "\n";
		}
		// remove comments from tempStr1 and put the rest into tempStr2
		
		tempStr2 = removeBlankLines(removeExtraSpaces(removeComments(tempStr1)));

		
		// write tempStr2 into a temporary file
		outfile << tempStr2;
		// close the original input file
		infile.close();
	}
	outfile.close();

	
}

/*------------------------END PART ONE-----------------------*/

int main()
{
	partOne();
	//TODO: partTwo();
	//TODO: partThree();

	//system("Pause");
	return 0;
}
