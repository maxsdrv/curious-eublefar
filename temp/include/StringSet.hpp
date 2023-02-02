#include <vector>
#include <string>
#include <deque>
#include <set>


class StringSet {
public:
    void add(const std::string& s, int priority) {
        data.push_back(s);
        sorted_data.insert(StringItem{s, priority});    
    }
    const std::string& find_last() const {
        return data.back();
    }
    const std::string& find_best() const {
        return std::prev(sorted_data.end())->s;
    } 
private:
    std::vector<std::string> data;

    struct StringItem {
        std::string s;
        int priority;
        bool operator<(const StringItem& other) const {
            return priority < other.priority;
        }
    };
    
    std::set<StringItem> sorted_data;
};
