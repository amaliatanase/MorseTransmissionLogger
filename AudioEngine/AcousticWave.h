//
// Created by Anamaria Briciu on 24.03.2026.
//

#ifndef SEMINAR3_1011_ACOUSTICWAVE_H
#define SEMINAR3_1011_ACOUSTICWAVE_H
#include "DynamicArray.h"
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::ostream;

class AcousticWave {
    //protected because we have classes derived from AcousticWave
protected:
    float frequency;
    float amplitude;
    int sampleRate;
    DynamicArray samples;

public:
    AcousticWave(float _freq, float _amplitude, int _sampleRate) : frequency(_freq), amplitude(_amplitude),
                                                                   sampleRate(_sampleRate), samples() {
    };

    AcousticWave &operator*=(const AcousticWave &other);
    AcousticWave operator*(const AcousticWave &other);

    //Method to glue disparate waves together
    //E.g. Wave A, duration 1 sec
    //     Wave B, duration 2 secs
    //     Result = A + B
    //     Result will have exactly 3 secs
    //in the method:
    //      allocate big enough array (numberOfSamples for wave 1 + numberOfSamples for wave 2)
    //      copy samples from Wave A in the beginning
    //      copy samples from Wave B into remaining space
    AcousticWave operator+(const AcousticWave& other);

    virtual void computeSamples(float duration);

    const DynamicArray &getSamples() const;

    DynamicArray &getSamples();

    unsigned int getNumberOfSamples() const;

    float getFrequency() const;

    float getAmplitude() const;

    int getSampleRate() const;

    virtual string getWaveType() const;

    virtual ~AcousticWave();

    friend ostream &operator<<(ostream &os, const AcousticWave &wave);
};


class SineWave : public AcousticWave {
public:
    SineWave(float _freq, float _amplitude, int _sampleRate) : AcousticWave(_freq, _amplitude, _sampleRate) {
    };

    void computeSamples(float duration) override;

    string getWaveType() const override;
};

//TO-DO: Silence class: inherits from AcousticWave
//in computeSamples: fills array with 0.0f
class Silence : public AcousticWave {
public:
    Silence(float _freq, float _amplitude, int _sampleRate) : AcousticWave(_freq, _amplitude, _sampleRate) {
    };

    void computeSamples(float duration) override;

    string getWaveType() const override;
};
#endif //SEMINAR3_1011_ACOUSTICWAVE_H
