//
// Created by Anamaria Briciu on 05.04.2026.
//
#include <iostream>
#include <fstream>
#include "MorseEncoder.h"
std::map<char, string> MorseEncoder::MorseAlphabet;

bool MorseEncoder::loadMorseAlphabet(const string &filepath) {
    std::ifstream fin(filepath);
    if (!fin.is_open())
        return false;
    while (!fin.eof()) {
        char ch;
        string codeCh;
        fin >> ch >> codeCh;
        MorseAlphabet[ch] = codeCh;
    }
    fin.close();
    return !MorseAlphabet.empty();
}

AcousticWave MorseEncoder::encode(const string &stringToEncode, float unitSeconds, float frequency, float amplitude,
                                  int sampleRate) {
    SineWave dot{frequency, amplitude, sampleRate};
    SineWave dash{frequency, amplitude, sampleRate};

    dot.computeSamples(1 * unitSeconds);
    dash.computeSamples(3 * unitSeconds);

    //between elements of same letter
    Silence gap1{frequency, amplitude, sampleRate};
    //between letters
    Silence gap3{frequency, amplitude, sampleRate};
    //between words
    Silence gap7{frequency, amplitude, sampleRate};

    gap1.computeSamples(1 * unitSeconds);
    gap3.computeSamples(3 * unitSeconds);
    gap7.computeSamples(7 * unitSeconds);
    AcousticWave result{frequency, amplitude, sampleRate};
    for (int i = 0; i < stringToEncode.size(); i++) {
        char crtChar = stringToEncode[i];
        if (crtChar == ' ') {
            result = result + gap7;
        } else {
            //crtChar = letter
            auto it = MorseAlphabet.find(crtChar);
            if (it != MorseAlphabet.end()) {
                const string &morseCodeForLetter = MorseAlphabet[crtChar];
                for (int k = 0; k < morseCodeForLetter.size(); k++) {
                    if (morseCodeForLetter[k] == '.')
                        result = result + dot;
                    else if (morseCodeForLetter[k] == '-')
                        result = result + dash;
                    if (k + 1 != morseCodeForLetter.size())
                        result = result + gap1;
                }
            }
            if (i + 1 != stringToEncode.size() && stringToEncode[i+1]!=' ')
                result = result + gap3;
        }
    }
    return result;
}
