//Daniel Fialkovsky

// fileReader is a Handy interface for ifstreams
// It makes getlines easy for emitting strings, it also automatically gets rid of 
// '\r' which can be a major pain to read in *nix environments


#ifndef _fileReader_HPP_
#define _fileReader_HPP_

#include <fstream>
#include <string>
#include <iostream>


class fileReader 
{
public:
    fileReader();
    fileReader(const std::string & fileName);
    ~fileReader();
public:
    // opens the file
    void openFile(const std::string & fileName);
    
    void closeFile();
    //clears and resets the file
    inline void clearFile();
    // skips a line in the file. of course, This wont work if the file pointer is at its end
    void skipLine();
    // Iterates through the next line in the file.
    // returns of the string taken
    std::string getLine();
    // does exactly what std::ifstream::good() does,
    // checks if there are no error flags set internally
     bool good();
    // checks if the file pointer has hit the end of the file
     bool eof();
private:
    std::ifstream file_;
private:
    // in case the text file is tainted with return carrages, we need to 
    // remove them lest they screw up our std::getline calls in *NIX
    inline void removeReturnCarraige(std::string & subjectedString);
    // in case the text file is tainted with a specific chartype, we need to 
    // remove them lest they screw up our std::getline calls in *NIX
    inline void removeSpecificChar(std::string & subjectedString, char type);
    // brute force method for removing all none general ascii numbers. every string that isnt:
    //"abcdefghijklmnopqrstuvwxyz-ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789?!$"
    // will be removed from the string
    inline void removeNonStandardLetters(std::string & subjectedString);
    
};


#endif // fileREader