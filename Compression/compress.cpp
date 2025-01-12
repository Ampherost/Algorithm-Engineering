#include <string>
#include <vector>
#include <sstream>
#include <algorithm>  
#include <iostream>

static const int WINDOW_SIZE = 4096;    
static const int MIN_MATCH_LENGTH = 3; 

struct Match {
    int offset;
    int length;
};

std::string compress(const std::string& source) {}

std::string decompress(const std::string& source) {}