//
// Created by Anamaria Briciu on 05.04.2026.
//

#ifndef SEMINAR4_1011_MORSEENCODER_H
#define SEMINAR4_1011_MORSEENCODER_H
#include <map>

#include "AcousticWave.h"


class MorseEncoder {
private:
    //keep Morse alphabet in static field
    static std::map<char  , string >MorseAlphabet;

public:
    //static map<char, string>
    //static method to load the alphabet from file (morse.txt)
    static bool loadMorseAlphabet(const string& filepath);
    //static method to encode a message
    //dit: SineWave with duration of exactly 1 time unit
    //dah: SineWave with duration of exactly 3 time units
    //gap between dits/dahs of same letter: Silence, 1 time unit
    //gap between letters: Silence, 3 time units
    //gap between words: Silence, 7 time units
    static AcousticWave encode(const string &stringToEncode,
                               float unitSeconds = 0.10f,
                               float frequency = 700.0f,
                               float amplitude = 0.8f,
                               int sampleRate = 44100);
};


#endif //SEMINAR4_1011_MORSEENCODER_H
