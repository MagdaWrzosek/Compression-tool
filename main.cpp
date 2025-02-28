#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

struct Node {
    char symbol;
    int frequency;
    Node *left;
    Node *right;

    Node(char s, int freq) : symbol(s), frequency(freq), left(nullptr), right(nullptr) {}

    //for an internal node
    Node(int freq, Node *l, Node *r) : symbol('\0'), frequency(freq), left(l), right(r) {}



};
struct Compare {
    bool operator()(Node *a, Node *b) {
        return a->frequency > b->frequency; // Kolejka o najmniejszej wartości na szczycie
    }
};

Node *buildHuffmanTree(const std::unordered_map<char, int> &frequencies);

std::unordered_map<char, std::string> generateCodes(Node* root);


int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string example = "aaaaabbbcccc";
    std::unordered_map<char,int> exFreqMap;
    for (char ch : example) {
        std::cout << ch << std::endl;
        exFreqMap[ch]++;
    }

    Node *exNode = buildHuffmanTree(exFreqMap);

    //{a:5, b:3, c:4}

    //generating Huffman codes




    return 0;
}
Node *buildHuffmanTree(const std::unordered_map<char, int> &frequencies) {

    std::priority_queue<Node *, std::vector<Node *>, Compare> pq;

    for (const auto &pair: frequencies) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        // two smallest frequencies are taken from priority queue
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();

        Node *parent = new Node(left->frequency + right->frequency, left, right);
        pq.push(parent);
    }

    return pq.top();
}
//codes are generated recursively
std::unordered_map<char, std::string> generateCodes(Node* root, std::string code = ""){     //default arg
    std::unordered_map<char, std::string> huffmanCodes;
    if (root->symbol != '\0') {             //not a leaf
        huffmanCodes [root->symbol] = code;
        return huffmanCodes;
    }
    //recursive function calls itself. This ensures all the nodes on left and right side are serviced
    std::unordered_map<char, std::string> leftMap = generateCodes(root->left, code + "0");
    std::unordered_map<char, std::string> rightMap = generateCodes(root->right, code + "1");

    huffmanCodes.insert(leftMap.begin(),leftMap.end());
    huffmanCodes.insert(rightMap.begin(), rightMap.end());


    return huffmanCodes;
}