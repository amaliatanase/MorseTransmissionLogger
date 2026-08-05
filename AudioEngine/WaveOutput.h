//
// Created by Anamaria Briciu on 23.03.2026.
//

#ifndef SEMINAR3_MINE_WAVEOUTPUT_H
#define SEMINAR3_MINE_WAVEOUTPUT_H
#include <string>

#include "AcousticWave.h"
class WaveOutput {
public:
    static bool saveSamples(const std::string &csv_path, const AcousticWave &w);
};


#endif //SEMINAR3_MINE_WAVEOUTPUT_H