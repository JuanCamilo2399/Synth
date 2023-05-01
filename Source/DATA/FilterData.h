/*
  ==============================================================================

    Filter.h
    Created: 6 Jan 2023 3:28:48pm
    Author:  Usuario

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class FilterData
{
public:
    void preparetoplay(double samplerate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters(const int filtertype, const float frequency, const float resonance, const float modulator = 1.0f);
    void reset();
    
private:
    juce::dsp::StateVariableTPTFilter<float> filter;
    bool isPrepared {false};

};