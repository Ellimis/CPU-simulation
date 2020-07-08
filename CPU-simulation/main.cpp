#include <iostream>
#include <string>
#include <sstream> // stringstream for string split

using namespace std;

class HardwareException {
	string step;
	string msg;
public:
	HardwareException(string step = "", string msg = "") {
		this->step = step;
		this->msg = msg;
	}
	void what() { // print step
		cout << this->step << " step, " << this->msg << endl;
		exit(0);
	}
};

class CPU {
	string instruction; // user input instruction
	int op1, op2; // operand
	string cmd; // instruction code (ADD SUB MUL DIV)
	void fetch() throw(HardwareException); // read commands from keyboard
	void decode() throw(HardwareException); // determine what the command code is
	void execute() throw(HardwareException); // execute commands according to command code
public:
	void run(); // CPU simulation, call fetch -> decode -> execute
	static int stringToInt(string x) throw(string);
};

void CPU::fetch() {
	getline(cin, this->instruction);

	if (this->instruction == "")
		throw HardwareException("fetch", "no command line");
}

void CPU::decode() {
	const char* command[] = { "ADD", "SUB", "MUL", "DIV" };
	stringstream split(this->instruction);
	string oper1, oper2;
	bool isExist = false;

	split >> this->cmd >> oper1 >> oper2;

	for (int i = 0; i < 4; i++) {
		if (!this->cmd.compare(*(command + i))) {
			isExist = true;
		}
	}

	if (!isExist)
		throw HardwareException("decode", "invalid command exception");
	if (oper2 == "")
		throw HardwareException("decode", "operand exception");

	try {
		this->op1 = this->stringToInt(oper1);
		this->op2 = this->stringToInt(oper2);
	}
	catch (HardwareException& exception) {
		exception.what();
	}
}

void CPU::execute() {
	if (!this->cmd.compare("ADD"))
		cout << "\t" << this->instruction << ": \t" << (this->op1 + this->op2) << endl;

	else if (!this->cmd.compare("SUB"))
		cout << "\t" << this->instruction << ": \t" << (this->op1 - this->op2) << endl;

	else if (!this->cmd.compare("MUL"))
		cout << "\t" << this->instruction << ": \t" << (this->op1 * this->op2) << endl;

	else if (!this->cmd.compare("DIV")) {
		if (this->op2 == 0)
			throw HardwareException("execute", "cannot be devided by zero");
		else
			cout << "\t" << this->instruction << ": \t" << (this->op1 / this->op2) << endl;
	}
}

void CPU::run() {
	try {
		while (true) {
			this->fetch();
			this->decode();
			this->execute();
		}
	}
	catch (HardwareException& exception) {
		exception.what();
	}
}

int CPU::stringToInt(string x) {
	if (atoi(x.c_str()) != 0 || x.compare("0") == 0)
		return atoi(x.c_str());
	else
		throw HardwareException("decode", "operand type exception");
}

int main() {
	CPU computer;

	computer.run();

	return 0;
}