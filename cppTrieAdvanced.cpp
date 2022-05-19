#include <iostream>
#include <string>
#include <vector>

const int kAlphabetSize = 26;

class Trie {
 public:
    class Node {
     public:
        std::vector<Node*> children_ = std::vector<Node*>(kAlphabetSize, nullptr);
        char c_;
        bool is_end_of_word_ = false;

        Node(char c) {
            c_ = c;
        }
    };

    Trie() {
        // Constructor: Creates a new node with '\0' char and put it as root of the trie
        root_ = new Node('\0');
    }

    void Destruct(Node* current) {
        if (current != nullptr) {
            for (auto next_node : current->children_) {
                Destruct(next_node);
            }
        }
        delete current;
    }

    ~Trie() {
        // Destructor: Deletes all nodes in the trie.
        Destruct(root_);
    }

    void Insert(std::string key) {
        Node* cur_node = root_;
        for (auto c : key) {
            // In the Node.next we have exactly 26 cells,
            // corresponding to the 0th, 1st ... the 25th c_ of the English alphabet.
            // To address cell of c_,
            // you need to subtract the code of the c_ from the code of the c_ 'a'.
            // Then if we have the c_ 'a', we will address 0 cell,
            // if the c_ 'd', then will address the 3rd cell and so on.
            if (cur_node->children_[c - 'a'] == nullptr) {
                cur_node->children_[c - 'a'] = new Node(c);
            }
            cur_node = cur_node->children_[c - 'a'];
        }
        cur_node->is_end_of_word_ = true;
    }

    bool Search(std::string key) {
        Node* cur_node = root_;
        for (auto c : key) {
            if (cur_node->children_[c - 'a'] == nullptr) {
                return false;
            }
            cur_node = cur_node->children_[c - 'a'];
        }
        return cur_node->is_end_of_word_;
    }

    void PrintSuffixes(Node* cur_node, std::string current_prefix) {
        // If reached the end of the word - print it!
        if (cur_node->is_end_of_word_) {
            std::cout << current_prefix << std::endl;
        }
        // Or there are some suffixes to be added to current_prefix - call PrintSuffixes
        // Example: cur_node = 'e' current_prefix = "ange"
        // There are suffixes "l" and "r" (words angel and anger)
        // We call PrintSuffixes('l', "ange" + "l"), PrintSuffixes('r', "ange" + "r")
        for (auto& next_node: cur_node->children_) {
            if (next_node != nullptr) {
                PrintSuffixes(next_node, current_prefix + std::string(1, next_node->c_));
            }
        }
    }

    void Retrieve(std::string prefix) {
        Node* cur_node = root_;
        for (auto c : prefix) {
            if (cur_node->children_[c - 'a'] == nullptr) {
                return;
            }
            cur_node = cur_node->children_[c - 'a'];
        }
        PrintSuffixes(cur_node, prefix);
    }

 private:
    Node* root_;
};

int main() {
    Trie trie;

    std::vector<std::string> data = {"any", "ant", "anna", "anger", "angelina", "angie", "angry", "angel"};

    for (auto& i: data) {
        trie.Insert(i);
    }

    if (!trie.Search("antalya")) {
        std::cout << "antalya is not in the trie" << std::endl;
    }

    if (trie.Search("angelina")) {
        std::cout << "angelina is in the trie" << std::endl;
    }

    trie.Retrieve("a");

    return 0;
}