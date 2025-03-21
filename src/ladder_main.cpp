#include "ladder.h"

int main() {
    cout << edit_distance_within("cat", "scat", 1) << endl;
    cout << edit_distance_within("scat", "sat", 1) << endl;
    cout << is_adjacent("cat", "car") << endl;

    set<string> words;
    load_words(words, "src/words.txt");
    cout << "loaded words" << endl;
    auto ladder = generate_word_ladder("cat", "dog", words);
    print_word_ladder(ladder);
    return 0;
}