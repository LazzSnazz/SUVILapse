#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

//declare our inputs
std::string pathin;
std::string pathout;
std::string mode;

int ArgParse(int argc, char *argv[])
{
    
    //make sure all args are present
    if (argc < 4)
    {
       std::cout << "Useage : ./command [Input directory] [Output directory] [Sorting mode(ABI, SUVI)]" << std::endl;
       return 1;
    }   
    //define our inputs
    pathin = argv[1];
    pathout = argv[2];
    mode = argv[3];

    //just make sure out and in end with a /
    pathin.append("/");
    pathout.append("/");

    //make sure the directorys exsist
    if(!fs::exists(pathin) || !fs::exists(pathout))
    { 
        std::cout << "Input or output directory does not exsist!" << std::endl;
        return 1;
    }

    //check to see if suvichannel is present and also make sure mode is present also

    if (mode == "ABI" || mode == "SUVI")
    {
        if (argc > 4)
        {
            std::cout << "Invalid usage!" << std::endl;
            return 1;
        }
    }
    else
    {
        std::cout << "ERROR. Please select a valid mode!" << std::endl;
        return 1;
    } 

    return 0;
}
