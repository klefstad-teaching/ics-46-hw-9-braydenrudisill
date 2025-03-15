#include "ladder.h"

int main() {
    cout << edit_distance_within("cat", "scat", 1) << endl;
    cout << edit_distance_within("scat", "sat", 1) << endl;
    cout << is_adjacent("scat", "sat") << endl;
    cout << is_adjacent("cat", "scat") << endl;

    set<string> words = {
        "cat",
        "car",
        "cab",
        "dab",
        "scat",
        "sat",
        "sag",
        "nag",
        "nog",
        "dog",
        "cog",
        "cot",
    };
    for (const string& s : generate_word_ladder("cat", "dog", words))
        cout << s << ' ';
    cout << endl;
    return 0;
}