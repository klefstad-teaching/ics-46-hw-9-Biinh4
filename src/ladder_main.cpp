#include "ladder.h"

void tolower(string &word);

int main() {
    verify_word_ladder();
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    string word1, word2;
    cout << "Enter your first word : ";
    cin >> word1;
    cout << "Enter your second word: ";
    cin >> word2;
    tolower(word1); tolower(word2);

    vector<string> word_ladder = generate_word_ladder(word1, word2, word_list);
    cout << word_ladder.size() << endl;
    print_word_ladder(word_ladder);

    return 0;
}

void tolower(string &word) {
    int i = 0;
    for(char c: word) 
        word[i++] = tolower(c);
}