#include "AVL_Tree.h"
#include <string>
#include <fstream>

class InvalidCommand : public std::exception
{
	std::string mess;
public:
	InvalidCommand(int address) {
		mess = "\nInvalid command at line " + std::to_string(address);
	}
	const char* what() const throw() {
		return mess.c_str();
	}
};

void run(std::string file) {
	std::ifstream ifs;
	ifs.open(file);

	AVL<int>* tree = NULL;
	char command;
	int val;
	int address = 1;

	try
	{
		while (ifs >> command)
		{
			switch (command) {
			case 'a':
				tree = new AVL<int>();
				break;
			case 'i':
				ifs >> val;
				tree->INSERT(val);
				break;
			case 'd':
				tree->display(tree->get_root(), 1);
				break;
			case 'm':
				std::cout << "\nMAX NODE: ";
				std::cout << tree->MAX_NODE();
				break;
			case 'n':
				std::cout << "\nMIN NODE: ";
				std::cout << tree->MIN_NODE();
				break;
			case 's':
				ifs >> val;
				tree->SEARCH(val);
				break;
			case 'p':
				tree->PRINT_LRN();
				break;
			case 'r':
				ifs >> val;
				tree->REMOVE(val);
				break;
			case 'l':
				tree->PRINT_NLR();
				break;
			default:
				throw InvalidCommand(address);
			}
			address++;
		}
	}
	catch (const std::exception& command)
	{
		std::cout << command.what();
	}
	delete tree;
}

int main() {

	std::string filename = "input.txt";
	run(filename);
	system("pause");
	return 0;
}