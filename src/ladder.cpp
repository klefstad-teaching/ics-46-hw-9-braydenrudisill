#include "ladder.h"

#include <numeric>
#include <ranges>
#include <algorithm>

void error(string word1, string word2, string msg) {
    cerr << "Error (" << word1 << "," << word2 << "): " << msg << endl;
}

bool edit_distance_within(const string& s1, const string& s2, int d) {
    int prev;
    vector<int> current(s2.size() + 1);
    iota(current.begin(), current.end(), 0);

    for (int i = 1; i <= s1.size(); ++i) {
        prev = current[0];
        current[0] = i;

        for (int j = 1; j <= s2.size(); j++) {
            int old_prev = prev;
            prev = current[j];
            if (s1[i - 1] == s2[j - 1])
                current[j] = old_prev;
            else
                current[j] = min(old_prev, min(current[j - 1], current[j])) + 1;
        }
    }
    return current[s2.size()] <= d;
}

bool is_adjacent(const string& s1, const string& s2) {
    return edit_distance_within(s1, s2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    deque<vector<string>> ladder_queue {{vector{begin_word}}};
    set visited = {begin_word};

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop_front();

        for (const string& word : word_list) {
            if (!is_adjacent(word, ladder.back()))
                continue;

            if (visited.contains(word))
                continue;

            if (ranges::any_of(ladder_queue, [word](vector<string> v) { return ranges::find(v, word) != v.end(); }))
                continue;

            visited.insert(word);
            vector<string> new_ladder = ladder;
            new_ladder.push_back(word);

            if (word == end_word)
                return new_ladder;

            ladder_queue.push_back(new_ladder);
        }
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);

    string word;
    while (file >> word)
        word_list.insert(word);
}

void print_word_ladder(const vector<string>& ladder) {
    for (const string& word : ladder)
        cout << word << ' ';
    cout << endl;
}

void verify_word_ladder() {

}
