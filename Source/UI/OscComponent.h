/*
  ==============================================================================

    OscComponent.h
    Created: 4 Jan 2023 2:59:13pm
    Author:  Usuario

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String WaveSelectorID, juce::String FmFreqId, juce::String FmdepthId);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::ComboBox OscWaveSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> OscWaveSelectorAttachement;
   
    juce::Slider fmfreqSlider;
    juce::Slider fmdepthSlider;
    using SliderAttachement = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachement> fmfreqAttachement;
    std::unique_ptr<SliderAttachement> fmdepthAttachement;

    juce::Label waveSelectorLabel{ "Wave Type" , "Wave Type" };
    juce::Label fmFreqLabel { "Fm Freq", "Fm freq"};
    juce::Label fmDepthLabel{ "Fm Depth", "Fm Depth" };


    using Attachement = juce::AudioProcessorValueTreeState::SliderAttachment;
    void setSliderWithLabel(juce::Slider& slider, juce::Label& Label, juce::AudioProcessorValueTreeState& apvts, juce::String paramid, std::unique_ptr<Attachement>& attachment);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
