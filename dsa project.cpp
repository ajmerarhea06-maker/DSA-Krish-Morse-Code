#include <iostream>
#include <map>
#include <string>
#include <cctype>

using namespace std;

struct Node {
    char data;
    Node *dot;
    Node *dash;
    Node(char c = '\0') : data(c), dot(NULL), dash(NULL) {}
};

Node* createNode(char c = '\0') {
    Node* newNode = new Node(c);
    return newNode;
}

map<char, string> buildMorseMap() {
    map<char, string> morse;
    morse['A'] = ".-";    morse['B'] = "-...";  morse['C'] = "-.-.";  morse['D'] = "-..";
    morse['E'] = ".";     morse['F'] = "..-.";  morse['G'] = "--.";   morse['H'] = "....";
    morse['I'] = "..";    morse['J'] = ".---";  morse['K'] = "-.-";   morse['L'] = ".-..";
    morse['M'] = "--";    morse['N'] = "-.";    morse['O'] = "---";   morse['P'] = ".--.";
    morse['Q'] = "--.-";  morse['R'] = ".-.";   morse['S'] = "...";   morse['T'] = "-";
    morse['U'] = "..-";   morse['V'] = "...-";  morse['W'] = ".--";   morse['X'] = "-..-";
    morse['Y'] = "-.--";  morse['Z'] = "--..";
    morse['1'] = ".----"; morse['2'] = "..---"; morse['3'] = "...--"; morse['4'] = "....-";
    morse['5'] = "....."; morse['6'] = "-...."; morse['7'] = "--..."; morse['8'] = "---..";
    morse['9'] = "----."; morse['0'] = "-----";
    return morse;
}

Node* buildTree(map<char, string>& morseMap) {
    Node* root = createNode();
    map<char, string>::iterator it;
    for (it = morseMap.begin(); it != morseMap.end(); ++it) {
        char ch = it->first;
        string code = it->second;
        Node* curr = root;
        for (size_t i = 0; i < code.length(); i++) {
            if (code[i] == '.') {
                if (!curr->dot) curr->dot = createNode();
                curr = curr->dot;
            } else if (code[i] == '-') {
                if (!curr->dash) curr->dash = createNode();
                curr = curr->dash;
            }
        }
        curr->data = ch;
    }
    return root;
}

char decodeSymbol(Node* root, string code) {
    Node* curr = root;
    for (size_t i = 0; i < code.length(); i++) {
        if (code[i] == '.') curr = curr->dot;
        else if (code[i] == '-') curr = curr->dash;
        if (!curr) return '#';
    }
    if (curr && curr->data != '\0') return curr->data;
    return '#';
}

string decodeMorse(Node* root, string morse) {
    string result = "";
    string symbol = "";
    for (size_t i = 0; i < morse.length(); i++) {
        if (morse[i] != ' ') symbol += morse[i];
        else {
            if (!symbol.empty()) {
                result += decodeSymbol(root, symbol);
                symbol = "";
            } else result += " ";
        }
    }
    if (!symbol.empty()) result += decodeSymbol(root, symbol);
    return result;
}

string encodeText(map<char, string>& morseMap, string text) {
    string encoded = "";
    for (size_t i = 0; i < text.length(); i++) {
        char c = toupper(text[i]);
        if (c == ' ') encoded += "  ";
        else if (morseMap.find(c) != morseMap.end())
            encoded += morseMap[c] + " ";
    }
    return encoded;
}

int main() {
    map<char, string> morseMap = buildMorseMap();
    Node* root = buildTree(morseMap);

    string input;
    int choice;

    do {
        cout << "\n--- MORSE CODE TRANSLATOR ---\n";
        cout << "1. Encode Text to Morse\n";
        cout << "2. Decode Morse to Text\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Enter text: ";
            getline(cin, input);
            cout << "Morse Code: " << encodeText(morseMap, input) << endl;
        } else if (choice == 2) {
            cout << "Enter Morse code (space separated): ";
            getline(cin, input);
            cout << "Decoded Text: " << decodeMorse(root, input) << endl;
        } else if (choice == 3) {
            cout << "Exiting...\n";
        } else {
            cout << "Invalid choice.\n";
        }
    } while (choice != 3);

    return 0;
}
