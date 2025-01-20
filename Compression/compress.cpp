#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <sstream>
#include <iostream>
#include <cstdint>

// ------------------ Token Definition ------------------
enum class TokenType {
    LITERAL,
    MATCH
};

struct Token {
    TokenType type;
    int value;      // literal char OR offset
    int length;     // for match
    int nextChar;   // for match
};

// ------------------ LZ77 Params ------------------
static const int WINDOW_SIZE = 4096;
static const int MIN_MATCH_LENGTH = 3;

// ------------------ LZ77 Compress ------------------
std::vector<Token> lz77_compress(const std::string& input) {
    std::vector<Token> tokens;
    int n = (int)input.size();
    int pos = 0;
    
    while (pos < n) {
        int bestOffset = 0;
        int bestLength = 0;
        int windowStart = std::max(0, pos - WINDOW_SIZE);

        // naive search
        for (int cand = windowStart; cand < pos; ++cand) {
            int length = 0;
            while ((pos + length) < n &&
                   (cand + length) < pos &&
                   input[cand + length] == input[pos + length]) 
            {
                length++;
            }
            if (length > bestLength) {
                bestLength = length;
                bestOffset = pos - cand;
            }
        }

        if (bestLength >= MIN_MATCH_LENGTH) {
            char nextC = (pos + bestLength < n) ? input[pos + bestLength] : '\0';
            Token t;
            t.type = TokenType::MATCH;
            t.value = bestOffset;
            t.length = bestLength;
            t.nextChar = (unsigned char)nextC;
            tokens.push_back(t);

            pos += bestLength + 1;
        } else {
            Token t;
            t.type = TokenType::LITERAL;
            t.value = (unsigned char)input[pos];
            t.length = 0;
            t.nextChar = 0;
            tokens.push_back(t);

            pos += 1;
        }
    }

    return tokens;
}

// ------------------ Token <--> uint32_t ------------------
static inline uint32_t encodeToken(const Token& t) {
    // Example bit layout (adjust for your ranges).
    // [ type(1) | offsetOrVal(12) | length(12) | nextChar(7) ]
    uint32_t code = 0;
    uint32_t typeBit = (t.type == TokenType::MATCH) ? 1u : 0u;
    uint32_t offVal = (t.value & 0x0FFF);  
    uint32_t len    = (t.length & 0x0FFF);
    uint32_t nc     = (t.nextChar & 0x7F);

    code = (typeBit << 31)
         | (offVal << 19)
         | (len << 7)
         | nc;
    return code;
}

static inline Token decodeToken(uint32_t code) {
    Token t;
    uint32_t typeBit = (code >> 31) & 0x01;
    t.type = (typeBit == 1) ? TokenType::MATCH : TokenType::LITERAL;
    t.value = (int)((code >> 19) & 0x0FFF);
    t.length = (int)((code >> 7) & 0x0FFF);
    t.nextChar = (int)(code & 0x7F);
    return t;
}

// ------------------ Huffman Structures ------------------
struct HuffNode {
    uint32_t symbol;
    uint64_t freq;
    HuffNode* left;
    HuffNode* right;
    bool operator>(const HuffNode& other) const {
        return freq > other.freq;
    }
};

HuffNode* buildHuffman(const std::unordered_map<uint32_t, uint64_t>& freqMap) {
    auto cmp = [](HuffNode* a, HuffNode* b){ return a->freq > b->freq; };
    std::priority_queue<HuffNode*, std::vector<HuffNode*>, decltype(cmp)> pq(cmp);

    for (auto & kv : freqMap) {
        auto node = new HuffNode{kv.first, kv.second, nullptr, nullptr};
        pq.push(node);
    }
    
    while (pq.size() > 1) {
        HuffNode* n1 = pq.top(); pq.pop();
        HuffNode* n2 = pq.top(); pq.pop();
        auto parent = new HuffNode{0, n1->freq + n2->freq, n1, n2};
        pq.push(parent);
    }
    
    return pq.empty() ? nullptr : pq.top();
}

void buildCodeTable(HuffNode* root, const std::string& prefix,
                    std::unordered_map<uint32_t, std::string>& table) {
    if (!root) return;
    if (!root->left && !root->right) {
        table[root->symbol] = prefix;
        return;
    }
    buildCodeTable(root->left,  prefix + "0", table);
    buildCodeTable(root->right, prefix + "1", table);
}

// ------------------ Huffman Encode ------------------
std::string huffmanEncode(const std::vector<Token>& tokens) {
    // 1) frequency
    std::unordered_map<uint32_t, uint64_t> freqMap;
    for (auto &t : tokens) {
        uint32_t sym = encodeToken(t);
        freqMap[sym]++;
    }
    // 2) build tree
    HuffNode* root = buildHuffman(freqMap);
    // 3) code table
    std::unordered_map<uint32_t, std::string> codeTable;
    buildCodeTable(root, "", codeTable);
    
    // 4) Output frequency map (text-based, for demo)
    //    Then output the encoded bitstream
    std::ostringstream oss;
    oss << freqMap.size() << "\n";
    for (auto &kv : freqMap) {
        oss << kv.first << " " << kv.second << "\n";
    }
    oss << "===\n";
    
    // bitstream
    for (auto &t : tokens) {
        uint32_t sym = encodeToken(t);
        oss << codeTable[sym];
    }
    return oss.str();
}

// ------------------ Huffman Decode ------------------
HuffNode* rebuildHuffman(std::istream& is) {
    size_t mapSize;
    is >> mapSize;
    std::unordered_map<uint32_t, uint64_t> freqMap;
    for (size_t i = 0; i < mapSize; i++) {
        uint32_t sym;
        uint64_t f;
        is >> sym >> f;
        freqMap[sym] = f;
    }
    // consume delimiter line "==="
    {
        std::string line;
        std::getline(is, line);
        if (line.empty()) {
            std::getline(is, line);
        }
    }
    return buildHuffman(freqMap);
}

void buildDecodeMap(HuffNode* root, const std::string& prefix,
                    std::unordered_map<std::string, uint32_t>& decodeMap) {
    if (!root) return;
    if (!root->left && !root->right) {
        decodeMap[prefix] = root->symbol;
        return;
    }
    buildDecodeMap(root->left,  prefix + "0", decodeMap);
    buildDecodeMap(root->right, prefix + "1", decodeMap);
}

std::vector<Token> huffmanDecode(const std::string& compressed) {
    std::istringstream iss(compressed);
    HuffNode* root = rebuildHuffman(iss);
    if (!root) {
        return {};
    }
    // build decode map
    std::unordered_map<std::string, uint32_t> decodeMap;
    buildDecodeMap(root, "", decodeMap);

    // remainder is the bitstream
    std::string bitstream;
    std::getline(iss, bitstream);
    
    // decode
    std::vector<Token> tokens;
    std::string buffer;
    for (char c : bitstream) {
        buffer.push_back(c);
        if (decodeMap.find(buffer) != decodeMap.end()) {
            uint32_t sym = decodeMap[buffer];
            tokens.push_back(decodeToken(sym));
            buffer.clear();
        }
    }
    return tokens;
}

// ------------------ LZ77 Decompress ------------------
std::string lz77_decompress(const std::vector<Token>& tokens) {
    std::string output;
    output.reserve(tokens.size() * 4);

    for (auto &t : tokens) {
        if (t.type == TokenType::LITERAL) {
            output.push_back((char)t.value);
        } else {
            // offset = t.value, length = t.length
            int start = (int)output.size() - t.value;
            for (int i = 0; i < t.length; i++) {
                output.push_back(output[start + i]);
            }
            if (t.nextChar != 0) {
                output.push_back((char)t.nextChar);
            }
        }
    }
    return output;
}

// ------------------ Final compress/decompress API ------------------
std::string compress(const std::string& source) {
    // LZ77
    auto tokens = lz77_compress(source);
    // Huffman
    auto bitstream = huffmanEncode(tokens);
    return bitstream;
}

std::string decompress(const std::string& source) {
    // Huffman decode
    auto tokens = huffmanDecode(source);
    // LZ77 decode
    auto result = lz77_decompress(tokens);
    return result;
}
