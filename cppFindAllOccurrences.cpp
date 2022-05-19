#include <iostream>
#include <string>
#include <vector>

class ZFinder {
    int cur_occurrence_ = -1; // position of the next occurrence
    int occurrence_index_ = -1;
    std::vector<int> occurrences_;

    // This is trivial Z-function calculation(in O(n^2)) in case you don't get O(n) version below (ComputeZ)
    std::vector<int> ComputeZTrivial(std::string s) {
        std::vector<int> z(s.size());
        for (int i = 1; i < s.size(); ++i) {
            while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) {
                ++z[i];
            }
        }
        return z;
    }

    std::vector<int> ComputeZ(const std::string& s) {
        std::vector<int> z(s.size(), 0);
        int l = 0, r = 0;
        for (int i = 1; i < s.size(); i++) {
            if (i <= r) {
                z[i] = std::min(r - i + 1, z[i - l]);
            }
            while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) {
                ++z[i];
            }
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        return z;
    }

    std::vector<int> FindAllOccurrences(const std::string& text, const std::string& pattern) {
        std::string joined = pattern + "#" + text;
        std::vector<int> z = ComputeZ(joined);
        std::vector<int> occurrences;
        for (int i = 0; i < text.size(); ++i) {
            if (z[i + pattern.size() + 1] == pattern.size()) {
                occurrences.push_back(i);
            }
        }
        return occurrences;
    }

public:
    ZFinder(const std::string& text, const std::string& pattern) {
        occurrences_ = FindAllOccurrences(text, pattern);
        occurrences_.push_back(-1);
        cur_occurrence_ = occurrences_[0];
        occurrence_index_ = 0;
    }

    int Find() {
        int current_occurrence = cur_occurrence_;
        ++occurrence_index_;
        if (occurrence_index_ >= occurrences_.size()) {
            return -1;
        }
        cur_occurrence_ = occurrences_[occurrence_index_];
        return current_occurrence;
    }

    int Freq() {
        return static_cast<int>(occurrences_.size()) - 1;
    }
};

int main() {
    std::string text = "If a dog chews shoes, whose shoes does he choose?";

    std::string pattern = "oes";

    ZFinder z_finder(text, pattern);

    std::cout << "Number of ocurrences: " << z_finder.Freq() << std::endl;

    int pos = z_finder.Find();

    while (pos != -1) {
        std::cout << pos << std::endl; // 17 30 35
        pos = z_finder.Find();
    }

    return 0;
}