//
// Created by Anamaria Briciu on 23.03.2026.
//

#include "WaveOutput.h"

#include <fstream>

bool WaveOutput::saveSamples(const std::string &csv_path, const AcousticWave &w) {
    std::ofstream file(csv_path);
    DynamicArray samples = w.getSamples();
    for (int i=0; i<samples.size(); i++) {
        file<<std::to_string(samples[i])<<std::endl;
    }
    return true;
}
