#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>


using namespace std;

// Store a joke question and its answer
struct Joke {
    string question;
    string answer;
};

// Load jokes from the text file
vector<Joke> loadJokes(const string& filename) {
    vector<Joke> jokes;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Error: Cannot open joke file!" << endl;
        return jokes;
    }

    while (getline(file, line)) {
        size_t position = line.find('?');

        if (position != string::npos) {
            Joke joke;
            joke.question = line.substr(0, position + 1);
            joke.answer = line.substr(position + 1);

            if (!joke.answer.empty()) {
                jokes.push_back(joke);
            }
        }
    }

    file.close();
    return jokes;
}

int main() {
    vector<Joke> jokes = loadJokes("randomJokes.txt");
    cout << "Total jokes loaded: " << jokes.size() << endl;



    if (jokes.empty()) {
        cout << "No jokes found!" << endl;
        return 1;
    }

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(
        0, static_cast<int>(jokes.size()) - 1
    );

    string choice = "y";

    cout << "Welcome to Alexa Make a Joke!" << endl;

    while (choice == "y" || choice == "Y") {
        int index = distribution(generator);

        cout << "\nAlexa: " << jokes[index].question << endl;

        cout << "Press Enter to see the answer...";
        string input;
        getline(cin, input);

        cout << "Alexa: " << jokes[index].answer << endl;

        cout << "\nAnother joke? (y/n): ";
        getline(cin, choice);
    }

    cout << "\nGoodbye!" << endl;
    return 0;
}
