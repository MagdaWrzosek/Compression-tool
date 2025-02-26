#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>



int main() {
    std::cout << "Hello, World!" << std::endl;

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

    Node *buildHuffmanTree(const std::unordered_map<char, int> &frequencies) {

        std::priority_queue<Node*, std::vector<Node *>, Compare> pq;

        for (const auto &pair: frequencies) {
            pq.push(new Node(pair.first, pair.second));
        }

        while (pq.size() > 1) {
            // two smallest frequencies are taken from priority queue
            Node *left = pq.top();
            pq.pop();
            Node *right = pq.top();
            pq.pop();

            Node *parent = new Node(left->frequency + right->frequncy, left, right);
            pq.push(parent);
        }

        return pq.top();
    }



    //generating Huffman codes


    return 0;
}
