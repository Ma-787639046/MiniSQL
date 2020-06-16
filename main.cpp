// 
//	main.cpp
//	Created by MGY on 2020/06/16
//

//	main is the toppest module that directly calls functions of Interpreter

#include <iostream>
#include "Interpreter.h"

BufferManager buffer_manager;

int main(int argc, char* argv[]) {
	std::cout << "====    Welcome to MiniSQL created by MGY & ZZJ!    ====\n";
	std::cout << "Please input your query:\n";
	Interpreter interpreter;
	while (true)
	{
		interpreter.read_in_command();
		interpreter.decode();
	}
	return 0;
}
