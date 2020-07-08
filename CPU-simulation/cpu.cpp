#include <iostream>
#include <string>
#include <sstream> // stringstream for string split
#include "cpu.h"

using namespace std;

void CPU::fetch() { // read commands from keyboard
	getline(cin, this->instruction);

	if (this->instruction == "")
		throw HardwareException("fetch", "no command line");
}

void CPU::decode() { // determine what the command code is
	const char* command[] = { "ADD", "SUB", "MUL", "DIV" };
	stringstream split(this->instruction);
	string oper1, oper2;
	bool isExist = false;

	split >> this->cmd >> oper1 >> oper2;

	for (int i = 0; i < 4; i++)
		if (!this->cmd.compare(*(command + i)))
			isExist = true;

	if (!isExist)
		throw HardwareException("decode", "invalid command exception");
	if (oper2 == "")
		throw HardwareException("decode", "operand exception");

	try {
		this->op1 = this->stringToInt(oper1);
		this->op2 = this->stringToInt(oper2);
	}
	catch (HardwareException& exception) { // for incorrect operand
		exception.what();
	}
}

void CPU::execute() { // execute commands according to command code
	int result = 0;

	if (!this->cmd.compare("ADD"))
		result = this->op1 + this->op2;

	else if (!this->cmd.compare("SUB"))
		result = this->op1 - this->op2;

	else if (!this->cmd.compare("MUL"))
		result = this->op1 * this->op2;

	else if (!this->cmd.compare("DIV")) {
		if (this->op2 == 0)
			throw HardwareException("execute", "cannot be devided by zero");
		else
			result = this->op1 / this->op2;
	}

	cout << "\t" << this->instruction << ": \t" << result << endl;
}

int CPU::stringToInt(string x) { // change string to int for operand exception
	if (atoi(x.c_str()) != 0 || x.compare("0") == 0)
		return atoi(x.c_str()); // type changing string -> char* -> int 
	else
		throw HardwareException("decode", "operand type exception");
}

void CPU::run() { // CPU simulation, call fetch -> decode -> execute
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