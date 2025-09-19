#include <vector>
#include <string>
#include <map>
#include <queue>
#include <utility>
#include <iostream>
#include <functional>


class Huffman {
public:
    Huffman(const std::vector<std::pair<char, double>>& freq) {
        // строим дерево
        buildTree(freq);
        // потом по нему делаем таблицу кодов
        buildCodes();
    }

    std::string code(const std::string& text) {
        std::string encoded;
        for (int i = 0; i < text.size(); i++) {
            encoded += codes[text[i]];
        }
        return encoded;
    }

    std::string decode(const std::string& text) {
        std::string decoded;
        Node* current = root;
        for (int i = 0; i < text.size(); i++) {
            if (text[i] == '0') current = current->left;
            else current = current->right;

            if (current->isLeaf()) {  // значит дошли до конца кода буквы
                decoded += current->ch;
                current = root;
            }
        }
        return decoded;
    }

private:
    struct Node {
        char ch;
        double freq;
        Node* left;
        Node* right;

        // просто вершина
        Node(char c, double f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
        // для создания родительской вершинки, частоты складываются
        Node(Node* l, Node* r) : ch('0'), freq(l->freq + r->freq), left(l), right(r) {}

        bool isLeaf() const {
            return (left == nullptr) && (right == nullptr);
        }
    };

    Node* root = nullptr;
    std::map<char, std::string> codes;

    
    void buildTree(const std::vector<std::pair<char, double>>& freq) {
        // делаем лямбда функцию для сравнения
        auto cmp = [](Node* a, Node* b) {return a->freq > b->freq;};
        // и на ее основе очередь с приоритетом
        std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> p_queque(cmp);

        for (int i = 0; i < freq.size(); i++) {
            p_queque.push(new Node(freq[i].first, freq[i].second));
        }

        while (p_queque.size() > 1) {
            // два подходящих по частоте элемента подвешиваем к новой вершинке
            Node* left = p_queque.top();
            p_queque.pop();

            Node* right = p_queque.top();
            p_queque.pop();

            p_queque.push(new Node(left, right));
        }

        root = p_queque.top();
    }

    void buildCodes() {
        if (root != nullptr) {
            generateCodes(root, "");
        }
    }
    
    void generateCodes(Node* node, const std::string& prefix) {
        if (node->isLeaf()) {
            codes[node->ch] = prefix;
            return;
        }
        generateCodes(node->left, prefix + "0");
        generateCodes(node->right, prefix + "1");
    }
};



int main() {
    std::vector<std::pair<char, double>> frequencies = {
        {'H', 0.1},
        {'e', 0.3},
        {'l', 0.2},
        {'o', 0.2},
        {' ', 0.1},
        {'W', 0.04},
        {'r', 0.04},
        {'d', 0.02}
    };

    Huffman huffman(frequencies);

    std::string originalText = "Hello World";
    std::string encodedText = huffman.code(originalText);
    std::string decodedText = huffman.decode(encodedText);
    
    std::cout << "Исходный текст: " << originalText << std::endl;
    std::cout << "Закодированный: " << encodedText << std::endl;
    std::cout << "Раскодированный: " << decodedText << std::endl;
    return 0;
}
