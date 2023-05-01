/*
  ==============================================================================

    OscData.h
    Created: 4 Jan 2023 2:21:55pm
    Author:  Usuario

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class OscData : public juce::dsp::Oscillator<float>
{
public:
    void preparetoplay(juce::dsp::ProcessSpec& spec);
    void SetWaveType(const int choice);
    void setWaveFrequency(const int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void setFmParams(const float depth, const float frequency);
private:
    juce::dsp::Oscillator<float> fmosc{ [](float x) {return std::sin(x); } };
    float fmMod{ 0.0f };
    float fmDepth{ 0.0f };
    int lastMidiNote;
};