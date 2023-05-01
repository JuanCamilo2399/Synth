/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"
#include "UI/OscComponent.h"
#include "UI/FilterComponent.h"

//==============================================================================
/**
*/
class NunisSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    NunisSynthAudioProcessorEditor (NunisSynthAudioProcessor&);
    ~NunisSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    

private:
    NunisSynthAudioProcessor& audioProcessor;
    OscComponent osc;
    AdsrComponent adsr;
    FilterComponent Filter;
    AdsrComponent ModAdsr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NunisSynthAudioProcessorEditor)
};
