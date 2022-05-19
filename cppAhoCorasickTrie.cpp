#include <cctype>
#include <iostream>
#include <map>
#include <queue>
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
            delete current;
        }
    }

    ~Trie() {
        // Destructor: Deletes all nodes in the trie.
        Destruct(root_);
    }

    Node* Insert(const std::string& key) {
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
        return cur_node;
    }

protected:
    Node* root_;
};

class AhoCorasickTrie : public Trie {
public:
    AhoCorasickTrie(const std::vector<std::string>& patterns) {
        BuildTrie(patterns);
        BuildLinks();
    }

    void Find(const std::string& text) {
        Node* cur_node = root_;
        for (int i = 0; i < text.size(); ++i) {
            char c = text[i];
            if (std::isalpha(c)) {
                c = std::tolower(c);
            } else {
                cur_node = root_;
                continue;
            }
            while (cur_node->children_[c - 'a'] == nullptr && cur_node != root_) {
                cur_node = suffix_links_[cur_node];
            }
            if (cur_node->children_[c - 'a'] == nullptr && cur_node == root_) {
                continue;
            }
            cur_node = cur_node->children_[c - 'a'];
            if (cur_node->is_end_of_word_) {
                std::cout << i + 1 - patterns_[cur_node].size() << ' ' << patterns_[cur_node] << std::endl;
            }
            Node* temp_node = output_links_[cur_node];
            while (temp_node != nullptr) {
                std::cout << i + 1 - patterns_[temp_node].size() << ' ' << patterns_[temp_node] << std::endl;
                temp_node = output_links_[temp_node];
            }
        }
    }

private:
    Node* GetSufLink(Node* parent, Node* cur_node) {
        Node* x = suffix_links_[parent];
        while (x != nullptr && x->children_[cur_node->c_ - 'a'] == nullptr) {
            x = suffix_links_[x];
        }
        if (x == nullptr) {
            return root_;
        } else {
            return x->children_[cur_node->c_ - 'a'];
        }
    }

    Node* GetOutLink(Node* cur_node) {
        Node* suf_node = suffix_links_[cur_node];
        if (suf_node != nullptr && suf_node->is_end_of_word_) {
            return suf_node;
        }
        // существует аут ссылка для суф_нод (для вершины, в которую ведёт суф ссылка)
        if (output_links_.find(suf_node) != output_links_.end()) {
            return output_links_[suf_node];
        }
        return nullptr;
    }

    void BuildTrie(const std::vector<std::string>& patterns) {
        for (const auto& pattern : patterns) {
            Node* end_node = Insert(pattern);
            patterns_[end_node] = pattern;
        }
    }

    void BuildLinks() {
        std::queue<Node*> nodes;
        suffix_links_[root_] = nullptr;
        output_links_[root_] = nullptr;
        for (auto next : root_->children_) {
            if (next != nullptr) {
                suffix_links_[next] = root_;
                output_links_[next] = nullptr;
                nodes.push(next);
            }
        }
        while (!nodes.empty()) {
            Node* cur_node = nodes.front();
            nodes.pop();
            for (auto next : cur_node->children_) {
                if (next != nullptr) {
                    suffix_links_[next] = GetSufLink(cur_node, next);
                    output_links_[next] = GetOutLink(next);
                    nodes.push(next);
                }
            }
        }
    }

    std::map<Node*, std::string> patterns_;
    std::map<Node*, Node*> suffix_links_;
    std::map<Node*, Node*> output_links_;
};

int main() {
    std::vector<std::string> patterns = {"you",
                                         "i",
                                         "do",
                                         "it",
                                         "itm",
                                         "dodo",
                                         "le",
                                         "ind",
                                         "ireallywanttofindthisstring"};
    AhoCorasickTrie trie(patterns);
    std::string text_line;
    std::cout << "=======================\n";
    while (std::getline(std::cin, text_line)) {
        trie.Find(text_line);
        std::cout << "=======================\n";
    }
    return 0;
}