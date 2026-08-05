//
// Created by Anamaria Briciu on 05.04.2026.
//

#ifndef SEMINAR4_1011_SIGNALPROCESSOR_H
#define SEMINAR4_1011_SIGNALPROCESSOR_H
#include "AcousticWave.h"


class SignalProcessor {
    //simulate acoustic effects: echo, reverb
    //echo = sound repeated after a distinct delay, typically between 0.1 and 1.0 seconds
    //       repetition of the original signal
    //reverb = short echo, with delay usually less than 0.1 seconds
private:
    static float clamp(float x, float low, float high);

public:
    //Compute the number of samples to look back and modify
    //      delaySamples = delaySeconds * sampleRate
    //      for samples from 0 to delaySamples-1: original (scaled/clamped) value
    //      for samples from delaySamples to numberOfSamples:
    //          newSample[i] = currentSample[i] + (currentSample[i-delaySamples] * a),
    //          scale/clamp it
    //      a = attenuation fator, 0 < a < 1, determines how much quieter the reflection is compared to the original
    static void applyEcho(AcousticWave &wave, float delay, float attenuation);

    static void applyReverb(AcousticWave &wave, float delay, float attenuation);
};


#endif //SEMINAR4_1011_SIGNALPROCESSOR_H
