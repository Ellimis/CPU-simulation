#include "hardware_exception.h"
#include <string>

class CPU {
	string instruction; // user input instruction
	int op1, op2; // operand
	string cmd; // instruction code (ADD SUB MUL DIV)

	void fetch() throw(HardwareException); // read commands from keyboard
	void decode() throw(HardwareException); // determine what the command code is
	void execute() throw(HardwareException); // execute commands according to command code

public:
	static int stringToInt(string x) throw(string); // change string to int for operand exception
	void run(); // CPU simulation, call fetch -> decode -> execute
};