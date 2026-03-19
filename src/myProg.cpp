#include "tool.h"

int main(int argc, char* argv[]) {
	if (argc != 4) {
		printf("Invalid number of arguments. myProg -b input.csv output.csv");
		return -1;
	}

	Tool tool;
	tool.setup(argv[2]);
	tool.get_max_flow();
}
