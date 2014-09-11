#include "fileReader.hpp"

fileReader::fileReader()
{

}


fileReader::fileReader(const std::string& fileName)
{
    openFile(fileName);
}


std::string fileReader::getLine()
{
    std::string output;
    std::getline(file_, output);
    removeReturnCarraige(output);
    return output;
}

void fileReader::openFile(const std::string & fileName)
{
    
    file_.open(fileName.c_str());
    // add fail condition
    if (!file_)
	std::cerr << "FATAL ERROR: File : " << fileName << " CANNOT BE OPENED\n";
    
}

void fileReader::skipLine()
{
    std::string temp;
    if (file_.is_open())
	std::getline(file_, temp);
}



// closes the file, but keeps the file pointer intact
void fileReader::closeFile()
{
    file_.close();
    
}
// closes the file, and resets the file pointer
void fileReader::clearFile()
{
    file_.close();
    file_.clear();
    file_.seekg(0, std::ios::beg);
}



void fileReader::removeReturnCarraige(std::string& subjectedString)
{
    std::size_t loc;
    while ( (loc = subjectedString.find('\r') ) != std::string::npos)
    {
	subjectedString.erase(loc,1);
    }
}

void fileReader::removeSpecificChar(std::string& subjectedString, char type)
{
    std::size_t loc;
    while ( (loc = subjectedString.find(type) ) != std::string::npos)
    {
	subjectedString.erase(loc,1);
    }
}

void fileReader::removeNonStandardLetters(std::string& subjectedString)
{
    std::string goodLetters = "abcdefghijklmnopqrstuvwxyz-ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789?!$";
    std::size_t loc(0);
    while ( (loc = subjectedString.find_first_not_of(goodLetters) ) != std::string::npos)
    {
	subjectedString.erase(loc);
    }
}



bool fileReader::eof()
{
    return file_.eof();
}


bool fileReader::good()
{
    return file_.good();
}


fileReader::~fileReader()
{
    clearFile();
}

