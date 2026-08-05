//
// Created by Anamaria Briciu on 04.05.2026.
//

#include "Transmission.h"

map<char, string> Transmission::getMorseMap() {
    std::map<char, std::string> morseMap;

    morseMap['A'] = ".-";
    morseMap['B'] = "-...";
    morseMap['C'] = "-.-.";
    morseMap['D'] = "-..";
    morseMap['E'] = ".";
    morseMap['F'] = "..-.";
    morseMap['G'] = "--.";
    morseMap['H'] = "....";
    morseMap['I'] = "..";
    morseMap['J'] = ".---";
    morseMap['K'] = "-.-";
    morseMap['L'] = ".-..";
    morseMap['M'] = "--";
    morseMap['N'] = "-.";
    morseMap['O'] = "---";
    morseMap['P'] = ".--.";
    morseMap['Q'] = "--.-";
    morseMap['R'] = ".-.";
    morseMap['S'] = "...";
    morseMap['T'] = "-";
    morseMap['U'] = "..-";
    morseMap['V'] = "...-";
    morseMap['W'] = ".--";
    morseMap['X'] = "-..-";
    morseMap['Y'] = "-.--";
    morseMap['Z'] = "--..";

    morseMap['0'] = "-----";
    morseMap['1'] = ".----";
    morseMap['2'] = "..---";
    morseMap['3'] = "...--";
    morseMap['4'] = "....-";
    morseMap['5'] = ".....";
    morseMap['6'] = "-....";
    morseMap['7'] = "--...";
    morseMap['8'] = "---..";
    morseMap['9'] = "----.";

    return morseMap;
}

int Transmission::getID() const {
    return id;
}

const string &Transmission::getSender() const {
    return sender;
}

const string &Transmission::getReceiver() const {
    return receiver;
}

const string &Transmission::getContent() const {
    return content;
}

Priority Transmission::getPriority() const {
    return priority;
}

string Transmission::getMorseCode(const string &content) {
    map<char, string> morseMap = getMorseMap();
    //content = SOS
    //we should return is: ... --- ...

    //content: Ana are mere.
    string result = "";
    for (int i = 0; i < content.size(); i++) {
        char currentChar = content[i];
        if (currentChar == ' ') {
            result += " / ";
            continue;
        }
        //convert to uppercase because keys in
        //morseMap are uppercase characters
        char uppercaseChar = std::toupper(currentChar);
        //std::cout<<currentChar<<": "<<uppercaseChar<<std::endl;
        auto it = morseMap.find(uppercaseChar);
        if (it != morseMap.end()) {
            //we found the letter in the Morse dictionary
            result += it->second;
            if (i + 1 < content.size() && content[i + 1] != ' ')
                result += "  ";
        }
    }
    return result;
}
