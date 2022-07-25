#include <iostream>
#include <filesystem>
#include <map>
#include "argparse.h"
#include "TimeHelper.h"

namespace fs = std::filesystem;
int ProcessABI()
{

    int filenumber = 0;
    std::map<time_t, fs::directory_entry> sort_by_time;
    int number = 0;
    std::string Answer = "n";

    std::cout << "Reading Files..." << std::endl;
    for (auto &entry : fs::recursive_directory_iterator(pathin))
    {
        if (entry.is_regular_file()) 
        {
            fs::path f(entry);
            std::string filename = f.filename();
            if(filename.find(".png") != std::string::npos)
            {
                if(filename.find("_RGB135_") != std::string::npos)
                { 
                    auto time = to_time_t(entry.last_write_time());
                    sort_by_time[time] = entry;
                }
            }
        }
    }
    //--- print the files sorted by time
    for (auto const &[time, entry] : sort_by_time) 
    {
        fs::path f(entry);
        std::string filename = f.filename();
        filenumber ++;
        std::string numberedpng = std::to_string(filenumber) + ".png";

        std::cout << filename << std::endl;
        if (fs::exists(pathout + numberedpng))
        {
            if (Answer == "n")
            {
                std::cout << numberedpng << " already present! Overwrite all? (Warning! this will remove all files with .png!) y/n: ";
                std::cin >> Answer;
                if (Answer != "y")
                {
                    std::cout << "exiting!" << std::endl;
                    return 1;
                }
            }
            Answer = "y";
            std::string removeall = "rm " + pathout + "*.png";
            system(removeall.c_str());
        }
        fs::copy_file(entry, pathout + std::to_string(filenumber) + ".png");
    }
    return 0;
}