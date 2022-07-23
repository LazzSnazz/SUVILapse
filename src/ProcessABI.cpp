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
    //--- sort the files in the map by time
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
        std::cout << filename << std::endl;
        fs::copy_file(entry, pathout + std::to_string(filenumber) + ".png");
    }
    return 0;
}