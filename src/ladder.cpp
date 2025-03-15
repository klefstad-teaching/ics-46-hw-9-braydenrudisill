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

bool is_adjacent(string s1, string s2) {
    int n = s1.length();
    int m = s2.length();

    if (n < m) {
        std::swap(s1, s2);
        std::swap(n,m);
    }

    if (n-m > 1)
        return false;

    int edits = 0;
    int i = 0;
    int j = 0;
    while (i < n && j < m) {
        if (s1[i] == s2[j])
            ++j;
        else {
            if (n == m)
                ++j;
            if (edits++ == 1)
                return false;
        }

        ++i;
    }

    if (i < n || j < m)
        ++edits;

    return edits <= 1;
}

vector<string> generate_word_ladder_old(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue {{vector{begin_word}}};
    set visited = {begin_word};

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        for (const string& word : word_list) {
            if (!is_adjacent(word, ladder.back()))
                continue;

            if (visited.contains(word))
                continue;

            visited.insert(word);
            vector<string> new_ladder = ladder;
            new_ladder.push_back(word);

            if (word == end_word)
                return new_ladder;

            ladder_queue.push(new_ladder);
        }
    }
    return {};
}

vector<string> build_path(const string& intersect, unordered_map<string, string>& forward_parents, unordered_map<string, string>& backward_parents) {
    vector<string> path;
    string current = intersect;

    while (!current.empty()) {
        path.push_back(current);
        current = forward_parents[current];
    }

    ranges::reverse(path);
    current = backward_parents[intersect];

    while (!current.empty()) {
        path.push_back(current);
        current = backward_parents[current];
    }

    return path;
}

bool process_level(queue<string>& q, unordered_map<string, string>& parents, const unordered_map<string, string>& other_parents, const set<string>& dict, string& intersect_word) {
    const size_t level_size = q.size();
    for (int i = 0; i < level_size; ++i) {
        const string& current = q.front();
        q.pop();

        for (const string& next_word : dict) {
            if (is_adjacent(current, next_word) && !parents.contains(next_word)) {
                parents[next_word] = current;
                q.push(next_word);
                if (other_parents.contains(next_word)) {
                    intersect_word = next_word;
                    return true;
                }
            }
        }
    }
    return false;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (!word_list.contains(end_word))
        return {};
    if (begin_word == end_word)
        return {end_word};

    unordered_map<string, string> forward_parents, backward_parents;
    queue<string> forward_q, backward_q;
    string intersect_word;

    forward_parents[begin_word] = "";
    forward_q.push(begin_word);

    backward_parents[end_word] = "";
    backward_q.push(end_word);

    while (!forward_q.empty() && !backward_q.empty()) {
        if (process_level(forward_q, forward_parents, backward_parents, word_list, intersect_word))
            return build_path(intersect_word, forward_parents, backward_parents);
        if (process_level(backward_q, backward_parents, forward_parents, word_list, intersect_word))
            return build_path(intersect_word, forward_parents, backward_parents);
    }

    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);

    copy(istream_iterator<string>(file),
         istream_iterator<string>(),
         inserter(word_list, word_list.end()));
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found.\n";
        return;
    }
    cout << "Word ladder found: ";
    for (const string& word : ladder)
        cout << word << ' ';
    cout << endl;
}

void verify_word_ladder() {

}
