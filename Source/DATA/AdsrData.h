/*
  ==============================================================================

    AdsrData.h
    Created: 4 Jan 2023 12:56:54pm
    Author:  Usuario

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>
class AdsrData : public juce::ADSR
{
public:
    void updateADSR(const float attack, const float decay, const float sustain, const float release);
    
private:
    juce::ADSR::Parameters adsrparams;
};