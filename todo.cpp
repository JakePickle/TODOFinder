//File: todo.cpp
//Programmer: Jake Pickle
//Date: 08/20/2016
//Purpose: To easily find and catalog TODO lines in code

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

//FROM STACK OVERFLOW///////////////////////////////////////////////
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
///////////////////////////////////////////////////////////////////

//ALSO FROM STACK OVERFLOW
#include <dirent.h>

using namespace std;

int main(int argc, char const *argv[])
{
    int lineNum;
    vector<string> extensions;
    string input;
    ifstream inputFile;
    ofstream outputFile("TODO.txt");

    inputFile.open("extension.txt");
    lineNum = 0;
    while(getline(inputFile,input))
    {
        lineNum++;
        extensions.push_back(input);
    }
    inputFile.close();

    vector<string> files;
    //MOSTLY FROM STACK OVERFLOW
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("../TODOFinder")) != NULL) {
      while ((ent = readdir (dir)) != NULL) {
        files.push_back(ent->d_name);
      }
      closedir (dir);
    } else {
      /* could not open directory */
      perror ("");//Not sure what this does so lets hope it doesn't happen
      return EXIT_FAILURE;
    }
    ///////////////////////

    for (int i = 2; i < files.size(); ++i)
    {
        if(find(extensions.begin(), extensions.end(), files[i].substr(files[i].length()-3)) != extensions.end())//If file extention is on extensions list
        {
            lineNum = 0;

            input = files[i];

            inputFile.open(input.c_str());

            while(getline(inputFile,input))
            {
                lineNum++;
                if(input.find("TODO") != string::npos)
                {
                    outputFile << "Line " << lineNum << " in file " << files[i] << + "\n\t" + trim(input) << endl << endl;
                }
            }
            inputFile.close();
        }
    }

    outputFile.close();

    return 0;
}