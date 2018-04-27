#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stack>

using namespace std;

const int ROW = 23;
const int COL = 30;

string table[ROW][COL] = { " " };


int main() {
	//vector<string> program;

	fstream ProgramFileInput;
	ProgramFileInput.open("final2.txt", ios_base::in);
	if (!ProgramFileInput) {
		cout << "Fail to open program file." << endl;
		return 0;
	}

	bool check[5] = { false };

	// Dummy variable storing the word read from the program file, then it is pushed into the program vector
	string dummyVar = "";
	string input = "";
	while (ProgramFileInput >> dummyVar) {
		if (dummyVar == "PROGRAM") {
			dummyVar = "p";
			check[0] = true;
		}
		else if (dummyVar == "BEGIN") {
			dummyVar = "b";
			check[1] = true;
		}
		else if (dummyVar == "INTEGER") {
			dummyVar = "i";
			check[2] = true;
		}
		else if (dummyVar == "PRINT") {
			dummyVar = "c";
			check[3] = true;
		}
		else if (dummyVar == "END.") {
			dummyVar = "$";
			check[4] = true;
		}
		input += dummyVar;
		//program.push_back(dummyVar);
	}

	if (check[0] == false) {
		cout << "PROGRAM is either missing or spelled incorrectly!" << endl;
		return 0;
	}

	if (check[1] == false) {
		cout << "BEGIN is either missing or spelled incorrectly!" << endl;
		system("pause");
		return 0;
	}

	if (check[2] == false) {
		cout << "INTEGER is either missing or spelled incorrectly!" << endl;
		system("pause");
		return 0;
	}

	if (check[3] == false) {
		cout << "PRINT is either missing or spelled incorrectly!" << endl;
		system("pause");
		return 0;
	}

	if (check[4] == false) {
		cout << "END. is either missing or spelled incorrectly!" << endl;
		system("pause");
		return 0;
	}

	//string dummyVar = "";
	

	//while (ProgramFileInput >> dummyVar) {
	//	if (dummyVar == "PROGRAM") {
	//		dummyVar = "p";
	//	}
	//	else if (dummyVar == "BEGIN") {
	//		dummyVar = "b";
	//	}
	//	else if (dummyVar == "INTEGER") {
	//		dummyVar = "i";
	//	}
	//	else if (dummyVar == "PRINT") {
	//		dummyVar = "c";
	//	}
	//	else if (dummyVar == "END.") {
	//		dummyVar = "$";
	//	}
	//	input += dummyVar;
	//}

	fstream TableFileInput;
	TableFileInput.open("parsing_table.txt", ios_base::in);
	if (!TableFileInput) {
		cout << "Fail to open file" << endl;
		return 0;
	}
	
	string s;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			TableFileInput >> s;
			table[i][j] = s;

		}
	}
	cout << "Input: " << input << endl;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			cout << setw(5) << table[i][j];
		}
		cout << endl;
	}

	// DECLARE VARIABLES //

	stack<string> MyStack;
	int word_index = 0;
	string stack_front_value;
	string input_char;
	string value_in_table;

	// PROCESS INPUT //

	// Push starting symbol into the stack
	MyStack.push(table[1][0]);

	// Get the first word  
	input_char = input[0];

	while (word_index < input.length()) {
		cout << "INPUT CHAR: " << input_char << endl;
		stack_front_value = MyStack.top();
		MyStack.pop();

		// When there is a match, we move on to the next word in the program
		if (stack_front_value == input_char) {
			word_index++;
			input_char = dummyVar[word_index];
		}
		else {
			// Indexes to find the value in the table
			int a;
			int b;
			// Look for [stack_front_value, input_char] in the table

			// Look for the index of stack_front_value
			for (int i = 0; i < ROW; i++) {
				if (table[i][0] == stack_front_value) {
					a = i;
					break;
				}
				else {
					a = -1;
				}
			}

			// Look for the index of input_char
			for (int i = 0; i < COL; i++) {
				if (table[0][i] == input_char) {
					b = i;
					break;
				}
				else {
					b = -1;
				}
			}

			// Indexes found
			if (a > -1 && b > -1) {
				value_in_table = table[a][b];
				cout << "Value in table: " << value_in_table << endl;
			}
			else { // Or not
				cout << "Cannot find a value in table" << endl;
			}

			// If the cell in the table is a lamda, then pop the next character in the stack
			if (value_in_table == "&") {
				continue;
			}
			// If the tracing ends up at one of the empty cell in the parsing table (labeled ! in this program), then the expression is not a word
			if (value_in_table == "!") {
				break;
			}
			// Push the string onto the stack in reverse order
			for (int i = value_in_table.length() - 1; i > -1; i--) {
				MyStack.push(string(1, value_in_table[i]));
			}
		}
	}

	if (MyStack.size() == 0) {
		cout << "Accept" << endl;
	}
	else {
		cout << "Reject" << endl;
	}
	cout << "DONE" << endl;
	system("pause");
	return 0;
}