#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <bitset>
#include <memory>

using namespace std;

struct Node {
    char character;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) : character(c), freq(f), left(nullptr), right(nullptr) {}
    Node(int f) : character('\0'), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void generateCodes(Node* root, string code, unordered_map<char, string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) {
        codes[root->character] = code;
        return;
    }
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

void serializeTree(Node* root, vector<bool>& bits) {
    if (!root) return;
    if (!root->left && !root->right) {
        bits.push_back(true);
        for (int i = 7; i >= 0; --i) {
            bits.push_back((root->character >> i) & 1);
        }
    } else {
        bits.push_back(false);
        serializeTree(root->left, bits);
        serializeTree(root->right, bits);
    }
}

Node* deserializeTree(const vector<bool>& bits, size_t& pos) {
    if (pos >= bits.size()) return nullptr;
    bool isLeaf = bits[pos++];
    if (isLeaf) {
        char c = 0;
        for (int i = 0; i < 8; ++i) {
            if (pos >= bits.size()) return nullptr;
            c = (c << 1) | bits[pos++];
        }
        return new Node(c, 0);
    } else {
        Node* node = new Node(0);
        node->left = deserializeTree(bits, pos);
        node->right = deserializeTree(bits, pos);
        return node;
    }
}

string compress(const string& source) {
    if (source.empty()) return "";

    unordered_map<char, int> freq;
    for (char c : source) freq[c]++;

    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (const auto& pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    if (pq.empty()) return "";

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* internal = new Node(left->freq + right->freq);
        internal->left = left;
        internal->right = right;
        pq.push(internal);
    }

    Node* root = pq.top();

    unordered_map<char, string> codes;
    generateCodes(root, "", codes);

    vector<bool> treeBits;
    serializeTree(root, treeBits);

    vector<bool> dataBits;
    for (char c : source) {
        string code = codes[c];
        for (char bit : code) {
            dataBits.push_back(bit == '1');
        }
    }

    vector<bool> allBits = treeBits;

    uint32_t dataBitCount = dataBits.size();
    for (int i = 31; i >= 0; --i) {
        allBits.push_back((dataBitCount >> i) & 1);
    }

    allBits.insert(allBits.end(), dataBits.begin(), dataBits.end());

    string compressed;
    compressed.reserve((allBits.size() + 7) / 8);
    unsigned char byte = 0;
    int bitCount = 0;
    for (bool bit : allBits) {
        byte = (byte << 1) | bit;
        if (++bitCount == 8) {
            compressed.push_back(byte);
            byte = 0;
            bitCount = 0;
        }
    }
    if (bitCount > 0) {
        byte <<= (8 - bitCount);
        compressed.push_back(byte);
    }

    delete root;
    return compressed;
}

string decompress(const string& source) {
    if (source.empty()) return "";

    vector<bool> bitstream;
    for (unsigned char c : source) {
        for (int i = 7; i >= 0; --i) {
            bitstream.push_back((c >> i) & 1);
        }
    }

    size_t pos = 0;
    Node* root = deserializeTree(bitstream, pos);
    if (!root) return "";

    if (pos + 32 > bitstream.size()) {
        delete root;
        return "";
    }

    uint32_t dataBitCount = 0;
    for (int i = 0; i < 32; ++i) {
        dataBitCount = (dataBitCount << 1) | bitstream[pos++];
    }

    vector<bool> dataBits;
    while (pos < bitstream.size() && dataBits.size() < dataBitCount) {
        dataBits.push_back(bitstream[pos++]);
    }

    string result;
    Node* current = root;
    for (bool bit : dataBits) {
        current = bit ? current->right : current->left;
        if (!current) break;
        if (!current->left && !current->right) {
            result += current->character;
            current = root;
        }
    }

    delete root;
    return result;
}
