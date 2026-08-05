//
// Created by Anamaria Briciu on 24.03.2026.
//

#include "AcousticWave.h"

#include <cmath>

AcousticWave &AcousticWave::operator*=(const AcousticWave &other) {
    //per requirement
    unsigned int minNumberOfSamples = std::min(this->getNumberOfSamples(), other.getNumberOfSamples());
    for (unsigned int i = 0; i <= minNumberOfSamples; ++i) {
        this->samples[i] = samples[i] * other.samples[i];
    }
    return *this;
}

AcousticWave AcousticWave::operator*(const AcousticWave &other) {
    AcousticWave newWave(*this);
    newWave *= other;
    return newWave;
}

AcousticWave AcousticWave::operator+(const AcousticWave &other) {
    AcousticWave result(0, 0, sampleRate);
    unsigned int wave1Size = this->getNumberOfSamples();
    unsigned int wave2Size = other.getNumberOfSamples();
    result.samples.resize(wave1Size + wave2Size);
    for (unsigned int i = 0; i < wave1Size; i++) {
        result.samples[i] = this->samples[i];
    }
    for (unsigned int i = 0; i < wave2Size; i++) {
        result.samples[i + wave1Size] = other.samples[i];
    }
    return result;
}

AcousticWave::~AcousticWave() {
    cout << "AcousticWave destructor" << endl;
}

void AcousticWave::computeSamples(float duration) {
    unsigned numberOfSamples = static_cast<unsigned>(duration * static_cast<float>(sampleRate));
    //change the code below to use the modified resize(newSize) function
    //in the DynamicArray class
    samples.resize(numberOfSamples);
    for (unsigned int i = 0; i < numberOfSamples; i++)
        samples[i] = 0.0f;
}

unsigned int AcousticWave::getNumberOfSamples() const {
    return this->samples.size();
}

const DynamicArray &AcousticWave::getSamples() const {
    return this->samples;
}

DynamicArray &AcousticWave::getSamples() {
    return this->samples;
}

float AcousticWave::getFrequency() const {
    return this->frequency;
}

float AcousticWave::getAmplitude() const {
    return this->amplitude;
}

int AcousticWave::getSampleRate() const {
    return this->sampleRate;
}

std::string AcousticWave::getWaveType() const {
    return "Acoustic Wave";
}

//M_PI from math.h
//SineWave
void SineWave::computeSamples(float duration) {
    AcousticWave::computeSamples(duration);
    float t = 1.0f / static_cast<float>(sampleRate);
    float x = 2.0f * M_PI * frequency * t;

    for (unsigned int i = 0; i < getNumberOfSamples(); i++) {
        float value = amplitude * std::sin(x * static_cast<float>(i));
        samples[i] = value;
    }
}

std::string SineWave::getWaveType() const {
    return "Sine Wave";
}

void Silence::computeSamples(float duration) {
    AcousticWave::computeSamples(duration);
}

string Silence::getWaveType() const {
    return "Silence";
}


std::ostream &operator<<(std::ostream &os, const AcousticWave &wave) {
    os << "[" << wave.getWaveType() << "]:\n";
    os << "Frequency = " << wave.frequency << "; ";
    os << "Amplitude = " << wave.amplitude << "; ";
    os << "Sample rate = " << wave.sampleRate << "\n";
    os << "Samples\n";
    //os << wave.samples << "\n";
    return os;
}
