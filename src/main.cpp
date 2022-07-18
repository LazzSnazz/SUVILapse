#include <iostream>
#include <filesystem>
#include "argparse.h"
#include "ProcessSUVI.h"
#include "ProcessABI.h"

using namespace std;
    int main(int argc, char *argv[]){

    //start Argument parser and check to see if it returns any errors. exit if so.
    int parseargs = ArgParse(argc, argv);
    if (parseargs == 1) return 1;
    
    //listing vars
    cout << "input directory is: " << pathin << endl;
        cout << "output direcotry is: " << pathout << endl;
        cout << "mode is: " << mode << endl;
        cout << "channel number is: " << channelnumberstring << endl;
        cout << "xml keyword for channel: " << xmlkeyword << endl; 
int processabi;
     if (mode == "SUVI") ProcessSUVI(pathin, pathout, xmlkeyword);
     if (mode == "ABI") int processabi = ProcessABI();
     if (processabi== 1) return 1;
     cout << "Done!" << endl;
      return 0;
    }