#include "Tui.h"
#include "tool.h"

int main(int argc, char* argv[]) {
	if (argc == 4) {
		Tool tool;	
		tool.setup(argv[2]);	
		tool.get_max_flow();
		tool.get_missing_output();
		tool.risk_analysis();
		tool.save_to_file(argv[3]);
		return 0;
	}
	
	while (true) {
		Tui tui;
		tui.menuHandler();
	}

	return 0;
}
