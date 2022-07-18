#include <iterator>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <map>
#include "TimeHelper.h"

using namespace cv;
namespace fs = std::filesystem;
using namespace std;

int ProcessSUVI(string path, string outpath, string xmlkeyword){
 
 int filenumber = 0;
 string DATE;
 string Answer = "n";

  map<time_t, fs::directory_entry> sort_by_time;
 cout << "Reading Files..." << endl;
  //sort the files in the map by time
  for (auto &entry : fs::directory_iterator(path)){
    if (entry.is_regular_file()) {
      fs::path f(entry);
      string filename = f.filename();
      if (filename.find(".xml") != std::string::npos){
      auto time = to_time_t(entry.last_write_time());
      sort_by_time[time] = entry;
      }
    }
  }
  //print the files sorted by time
  for (auto const &[time, entry] : sort_by_time) {
    fs::path f(entry);
    string Filenamenoext = f.stem();
      string Filenamexml = f.filename();
      string Filenamepng = string(f.stem()) + ".png";

//start searching file for keyword
             bool islong = false;
             ifstream input;
		     size_t pos;
              string line;

		input.open(entry.path());    
		if(input.is_open()){
//look for keyword
			while(getline(input,line)){
			 
             pos = line.find(xmlkeyword);
			  if(pos!=string::npos){

            islong = true;
        }
        	 //look for creation date
          string srch = "date_created";
          if (line.find(srch) != std::string::npos){
             DATE = line.substr(41,22);
             break;
          }     
			}
		}
    
        //check and see if keyword is true if not cout that its not
        if (islong == true) {
        cout << (Filenamexml) << " is true!" << endl;
        filenumber ++;
        string numberedpng = to_string(filenumber) + ".png";

        string fullin = path + "/" + Filenamepng;
        
        //I feel like this is a bad way to check but it works
        if (Answer == "n"){
        if (fs::exists(outpath + numberedpng)){
          cout << numberedpng << " already present! Overwrite all? (Warning! this will remove all files with .png!) y/n: ";
  
          cin >> Answer;
          if (Answer != "y"){
            cout << "exiting!" << endl;
            return 1;
            }
          }
          Answer = "y";
          string removeall = "rm " + outpath + "*.png";
          system(removeall.c_str());
        }

        fs::copy_file(fullin, outpath + numberedpng, fs::copy_options::overwrite_existing);

         string what = "convert " + outpath + numberedpng + " -channel rgb -contrast-stretch 0.4%x0.4% " + outpath + numberedpng;
         
         system(what.c_str());

         Mat readf = imread(outpath + numberedpng);       

         Mat flipp;

         flip(readf, flipp, 0);
         //test
         putText(flipp, DATE, Point(0, 1250), FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(255, 255, 255));
         //endtest
         imwrite(outpath + numberedpng, flipp);
         
        }else{
            cout << (Filenamexml) << " is not True!" << endl;
        }

     //break;
    
  }
  cout << filenumber << " files moved..." << endl;
   return 0;
}