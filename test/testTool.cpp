#include "tool.h"

int main(int argc, char* argv[]) {
    if (argc < 2) return -1;

    Tool tool;
    tool.setup(argv[1]);
    tool.get_max_flow();

    tool.risk_analysis();
    tool.get_missing_output();
	tool.print_output();
}
