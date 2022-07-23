#include <iostream>
#include <filesystem>
#include "argparse.h"
#include "ProcessSUVI.h"
#include "ProcessABI.h"

int main(int argc, char *argv[])
{
    //start Argument parser and check to see if it returns any errors. exit if so.
    int parseargs = ArgParse(argc, argv);
    if (parseargs == 1) return 1;
    
    //listing vars
    std::cout << "input directory is: " << pathin << std::endl;
    std::cout << "output direcotry is: " << pathout << std::endl;
    std::cout << "mode is: " << mode << std::endl;

    int processsuvi;
    if (mode == "SUVI") processsuvi = ProcessSUVI(pathin, pathout);
    if (mode == "ABI") int processabi = ProcessABI();
    if (processsuvi == 1) return 1;
    std::cout << "Done!" << std::endl;

    return 0;
}