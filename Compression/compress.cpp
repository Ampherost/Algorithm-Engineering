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

std::string compress(const std::string& source) {
    std::ostringstream oss;
    int srcSize = static_cast<int>(source.size());
    int pos = 0;   // current position in source
    
    while (pos < srcSize) {
        // 1) Search backward in the "window" for the best match
        //    The window goes from [pos - WINDOW_SIZE, pos) (bounded by 0 on the left)
        int bestOffset = 0;
        int bestLength = 0;
        
        int windowStart = std::max(0, pos - WINDOW_SIZE);
        
        // We'll do a naive search for demonstration (which can be slow for large text!).
        // For each possible start in the window, see how many chars match.
        for (int cand = windowStart; cand < pos; ++cand) {
            int length = 0;
            // compare forward from 'cand' and 'pos'
            while (cand + length < pos && pos + length < srcSize
                   && source[cand + length] == source[pos + length]) {
                ++length;
            }
            
            if (length > bestLength) {
                bestLength = length;
                bestOffset = pos - cand;  // how far back the match starts
            }
        }
        
        // 2) Decide whether to output a match token or a literal token
        if (bestLength >= MIN_MATCH_LENGTH) {
            // We found a good enough match
            // nextChar: the char after the matched substring, if it exists
            char nextChar = (pos + bestLength < srcSize)
                ? source[pos + bestLength]
                : '\0';  // if we reached end, use some placeholder or handle carefully
            
            // Output a match token: M <offset> <length> <nextChar>
            oss << "M " << bestOffset << " " << bestLength << " " << (int)(unsigned char)nextChar << " ";
            
            // Move pos forward by bestLength + 1 for the nextChar
            pos += bestLength + 1;
        } else {
            // Not enough of a match -> literal
            // Output a literal token: L <char>
            oss << "L " << (int)(unsigned char)source[pos] << " ";
            pos += 1;
        }
    }
    
    return oss.str();
}

std::string decompress(const std::string& source) {}