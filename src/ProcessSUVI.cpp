#include <iterator>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "TimeHelper.h"
#include "rapidxml.hpp"

rapidxml::xml_document<> doc;
rapidxml::xml_node<> *root_node = NULL;

using namespace cv;
namespace fs = std::filesystem;

int ProcessSUVI(std::string path, std::string outpath)
{ 
    int filenumber = 0;
    std::string DATE;
    std::string Answer = "n";
    int file_line = 0;
    float static_min;
    float static_max;
    float min;
    float max;
    std::string sci_obj;
    std::string WaveLnth;
    

    std::map<time_t, fs::directory_entry> sort_by_time;
    std::cout << "Reading Files..." << std::endl;

    //sort the files in the map by time
    for (auto &entry : fs::directory_iterator(path))
    {
        if (entry.is_regular_file()) 
        {
            fs::path f(entry);
            std::string filename = f.filename();
            if (filename.find(".xml") != std::string::npos)
            {
                auto time = to_time_t(entry.last_write_time());
                sort_by_time[time] = entry;
            }
        }
    } 

    

    //print the files sorted by time
    for (auto const &[time, entry] : sort_by_time) 
    {
        fs::path f(entry);
        std::string Filenamenoext = f.stem();
        std::string Filenamexml = f.filename();
        std::string Filenamepng = std::string(f.stem()) + ".png";

        //start reading xmls looking for all the values we need (Thanks Aang for the help!)
        std::ifstream xml_ifs(entry.path());
        std::string xml_content((std::istreambuf_iterator<char>(xml_ifs)),(std::istreambuf_iterator<char>()));
        doc.parse<0>((char *)xml_content.c_str());
        root_node = doc.first_node("netcdf");
        for (rapidxml::xml_node<> *sat_node = root_node->first_node("variable"); sat_node; sat_node = sat_node->next_sibling())
        {
            if(sat_node->first_attribute("name") != NULL)
            {
                if (std::string(sat_node->first_attribute("name")->value()) == "IMG_MAX")
                    for (rapidxml::xml_node<> *tle_node = sat_node->first_node("attribute"); 
                tle_node; 
                tle_node = tle_node->next_sibling())
                if (tle_node->first_attribute("name") != NULL)
                    if (std::string(tle_node->first_attribute("name")->value()) == "valid_range")
                        sscanf(tle_node->first_attribute("value")->value(), "%f %f", &min, &max);
                if (filenumber == 0) static_min = min;
                
                if (std::string(sat_node->first_attribute("name")->value()) == "date_created")
                    DATE = std::string(sat_node->first_attribute("value")->value());

                if (std::string(sat_node->first_attribute("name")->value()) == "SCI_OBJ")
                    sci_obj = std::string(sat_node->first_node("values")->value());
                        
                if (std::string(sat_node->first_attribute("name")->value()) == "WAVELNTH")
                    WaveLnth = "Fe" + std::string(sat_node->first_node("values")->value());
                if (filenumber == 0)
                {
                    if (WaveLnth == "Fe284") static_max = max - 60;
                    if (WaveLnth == "Fe171") static_max = max - 15;
                    if (WaveLnth == "Fe195") static_max = max - 30;
                    if (WaveLnth == "Fe304") static_max = max - 160;
                    if (WaveLnth == "Fe094") static_max = max;
                    if (WaveLnth == "Fe132") static_max = max;

                }
            }
        }
        if (sci_obj.find("long_exposure") == std::string::npos)
            {
                std::cout << Filenamexml << " not True!" << std::endl;
                continue;
            }
        
        


        std::cout << (Filenamexml) << " is true!" << std::endl;
        filenumber ++;
        std::string numberedpng = std::to_string(filenumber) + ".png";

        std::string fullin = path + "/" + Filenamepng;
        
        //I feel like this is a bad way to check but it works
        
        if (fs::exists(outpath + numberedpng))
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
            std::string removeall = "rm " + outpath + "*.png";
            system(removeall.c_str());
        }
        fs::copy_file(fullin, outpath + numberedpng);
        

        //start solving radiance
        Mat readf = imread(outpath + numberedpng, IMREAD_UNCHANGED);
        for (int i=0; i < readf.rows; ++i)
        {
            for (int j=0; j < readf.cols; ++j)
            {
                double radiance = min + (readf.at<ushort>(i,j) / 65535.0) * (max - min);
                double new_pixel = ((radiance - static_min) / (static_max - static_min)) *  65535.0;
                if(new_pixel < 0)
                new_pixel=0;
                if(new_pixel > 65535.0)
                new_pixel=65535.0;
                readf.at<ushort>(i,j) = new_pixel;
            }
        }

        flip(readf, readf, 0);
        putText(readf, DATE, Point(0, 1250), FONT_HERSHEY_DUPLEX, 1.0, 0xffff);
        putText(readf, WaveLnth, Point(1170, 1250), FONT_HERSHEY_DUPLEX, 1.0, 0xffff);
        putText(readf, "LazzSnazz", Point(1100, 50), FONT_HERSHEY_DUPLEX, 1.0, 0xffff);

        imwrite(outpath + numberedpng, readf);
         
        //break;
    
  }
    std::cout << filenumber << " files moved..." << std::endl;
    return 0;
}