/*
  ==============================================================================

    SynthVoice.h
    Created: 1 Nov 2022 3:30:05pm
    Author:  pc9sb-13

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/AdsrData.h"
#include "Data/OscData.h"
#include "Data/FilterData.h"
class SynthVoice : public juce::SynthesiserVoice
{
    public:
        bool canPlaySound(juce::SynthesiserSound* sound) override;
        void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
        void stopNote(float velocity, bool allowTailOff) override;
        void controllerMoved(int controllerNumber, int newControllerValue) override;
        void pitchWheelMoved(int newPitchWheelValue) override;
        void prepareToplay(double samplerate, int samplesperblock , int outputchannels);
        void updateAdsr(const float attack, const float decay, const float sustain, const float release);
        void renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;
        void updateFilter(const int filterType, const float cutoff, const float resonance);
        void updateModAdsr(const float attack, const float decay, const float sustain, const float release);
        
        OscData& getOscillator() { return osc; } //One line functions
    private:
        OscData osc;
        AdsrData adsr;
        FilterData filter;
        AdsrData modAdsr;
        juce::AudioBuffer<float> synthBuffer; //Clip fix 
        
        

        juce::dsp::Gain<float> gain;
        bool isPrepared { false };

        
        
};