#include <iostream>
#include <filesystem>
using namespace std;
namespace fs = filesystem;

//declare our inputs
     string pathin;
     string pathout;
     string mode;
     int channelnumber;
     string channelnumberstring;
     string xmlkeyword;

int ArgParse(int argc, char *argv[]){

  //make sure all args are present

  if (argc < 4){
    cout << "Useage : ./command [Input directory] [Output directory] [Sorting mode(ABI, SUVI)] [Suvi channel(094, 132, 171, 195, 284. 304)]" << endl;
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
  if(!fs::exists(pathin) || !fs::exists(pathout)){ 
  cout << "Input or output directory does not exsist!" << endl;
  return 1;
}

   //check to see if suvichannel is present and also make sure mode is present also

    //string channelnumberstring;
    //string xmlkeyword;
   if (mode == "ABI"){
      if (argc > 4){
        cout << "Invalid usage!" << endl;
        return 1;
      }
   }else if (mode == "SUVI"){
    if (argc < 5){
        cout << "Please choose channel!" << endl;
        return 1;
    }
    //convert channelnumber to int. catch if not an int
    try{
       channelnumber = stoi(argv[4]);

    //assign xmlkeyword and also set a string that has full channel name just in case needed
       switch (channelnumber){
       case 94:
          channelnumberstring = "Fe094";
          xmlkeyword = "Fe_XVIII_93.9A_long_exposure";
          break;
       case 132:
          channelnumberstring = "Fe132";
          xmlkeyword = "Fe_VIII_131.2A_long_exposure";
          break;
       case 171:
          channelnumberstring = "Fe171";
          xmlkeyword = "Fe_IX_171.1A_long_exposure";
          break;
       case 195:
          channelnumberstring = "Fe195";
          xmlkeyword = "Fe_XII_195.1A_long_exposure";
          break;
       case 284:
          channelnumberstring = "Fe284";
          xmlkeyword = "Fe_XV_284.2A_long_exposure";
          break;
       case 304:
          channelnumberstring = "Fe304";
          xmlkeyword = "He_II_303.8A_long_exposure";
          break;
       default:
          cout << "Invalid channel!" << endl;
          return 1;
   }
       
    }catch (invalid_argument){
       cout << "Invalid channel! Channels: bla bla bla" << endl;
       return 1;
    }
   }else{
        cout << "ERROR. Please select a valid mode!" << endl;
        return 1;
    } 
    

        //cout << "input directory is: " << pathin << endl;
        //cout << "output direcotry is: " << pathout << endl;
        //cout << "mode is: " << mode << endl;
        //cout << "channel number is: " << channelnumberstring << endl;
        //cout << "xml keyword for channel: " << xmlkeyword << endl; 

  return 0;
}
