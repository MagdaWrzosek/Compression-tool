#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>


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

Node *buildHuffmanTreeFromFile(const std::string file);


std::unordered_map<char, std::string> generateCodes(Node* root, std::string code = "");

std::string encode (std::string source, std::unordered_map<char, std::string> huffmanCodes);

void writeToFile(std::string fileName);

int main() {

    //generating Huffman codes for the contents of txt file

    /*std::unordered_map<char, std::string> exMap = generateCodes(exNode);
    for (std::pair<char, std::string> p: exMap) {
        std::cout << p.first << " : " << p.second << std::endl;
    }
     */
    Node newExample = *buildHuffmanTreeFromFile("mytxtfile.txt");

    //writeToFile("xxx");

    std::ifstream fileStream1("newfile.txt");
    if (!fileStream1) {
        std::cerr << "Cannot open file" << std::endl;
    }
    std::string string1;
    char ch1;
    while (fileStream1.get(ch1)) {
        string1+= ch1;
    }
    fileStream1.close();

    std::cout << string1 << std::endl;



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
Node *buildHuffmanTreeFromFile(const std::string file) {

    std::ifstream fileStream(file);
    if (!fileStream) {
        std::cerr << "Cannot open file" << std::endl;
    }
    std::unordered_map<char, int> exFreqMap;
    char ch;
    while (fileStream.get(ch)) {
        exFreqMap[ch]++;
    }
    fileStream.close();

    Node *exNodeFromFile = buildHuffmanTree(exFreqMap);

    return exNodeFromFile;
}
//codes are generated recursively
std::unordered_map<char, std::string> generateCodes(Node* root,std::string code){     //default arg
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

    //writeToFile("codes");
    //codes need to be written into a file

    return huffmanCodes;
}
std::string encode (std::string source , std::unordered_map<char, std::string> huffmanCodes){
    std::string result;
    for(char ch: source){
        if(huffmanCodes.find(ch) != huffmanCodes.end()){
            result += huffmanCodes.find(ch)->second;
        }
    }
    return result;
}
void writeToFile(std::string fileName){
    std::ofstream file("./" + fileName);
    if (file.is_open()) {

        file << "New text\n";
        file.close();
        std::cout << "Data saved successfully.\n";
    } else {
        std::cout << "File creation error\n";
    }
    std::ifstream file1 ("./" + fileName);

    //std::cout <<  << std::endl;
}