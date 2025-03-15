#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << word1 << "  " << word2 << " -- " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int size1 = str1.size();
    int size2 = str2.size();
    int size_diff = abs(size1 - size2);
    int diff = 0;

    if(size_diff == 0) {
        for(int i = 0; i < size1; ++i) {
            if(str1[i] != str2[i]) {
                ++diff;
            }
        }
    }
    else if(size_diff == 1) {
        int i = 0, j = 0;
        while (i < size1 && j < size2) {
            if (str1[i] != str2[j]) {
                if (size1 > size2) ++i;
                else ++j;
                ++diff;
                // if (diff > 1) return false;
            } 
            else {
                i++;
                j++;
            }
        }
    } 
    else if (size_diff > d) return false;

    return diff <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (word_list.count(end_word) == 0) return {};

    if (begin_word == end_word) {
        error(begin_word, end_word, "Same word!!!");
        return {};
    }
    
    queue<vector<string>> ladder_queue;
    vector<string> vec;
    vec.push_back(begin_word);
    ladder_queue.push(vec);

    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> sub_ladder_stack = ladder_queue.front();
        ladder_queue.pop();

        string last_word = sub_ladder_stack.back();

        for (string word: word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.count(word) == 0) {
                    visited.insert(word);
                    vector<string> new_ladder(sub_ladder_stack);
                    new_ladder.push_back(word);
                    if (word == end_word) {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}


void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
     if (!file.is_open()) {
        cout << "Couldn't open file" << endl;
        return;
    }

    string word;

    while(getline(file, word)) 
        word_list.insert(word);

    file.close();

}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found.";
    } else {

    cout << "Word ladder found: ";
    
    for(string word: ladder)
        cout << word << " ";
    }
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;

    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}


