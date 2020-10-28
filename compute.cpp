#include "Kernel/c++/head/init.h"
#include "Kernel/c++/head/compute.h"

/*
Programme to compute an Memory in a Model from a config file.
Arg0 - path to config file
Arg1 - level in Model
*/

int main(int argc, char **argv) {
	if (argc < 3) {
		std::cout << "No enougth args\n";
		std::exit(0);
	}
	std::cout << "Loading from " << argv[1] << "\n";
	Model<double> mdl = load_model<double>(argv[1]);
	ptr_mdl(&mdl);
	std::cout << "Compute level " << std::stoi(argv[2]) << "\n";
	compute<double>(&(mdl.levels[std::stoi(argv[2])]), 0, false);
	ptr_mdl(&mdl);
	return 0;
};
