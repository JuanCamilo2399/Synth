/*
  ==============================================================================

    FilterComponent.h
    Created: 6 Jan 2023 3:30:01pm
    Author:  Usuario

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String FilterTypeID, juce::String FilterCutoffID, juce::String FilterResID);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox filterTypeSelector{ "Filter Type" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> FilterTypeAttachement;

    juce::Slider filterCutoffSlider;
    juce::Slider filterResonanceSlider;
    
    using SliderAttachement = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachement> FilterCutoffAttachnment;
    std::unique_ptr<SliderAttachement> FilterResonanceAttachnment;

    juce::Label FilterTypeLabel{ "Filter Type" , "Filter Type" };
    juce::Label FilterCutoffLabel{ "Filter Freq", "Filter Freq" };
    juce::Label FilterResonanceLabel { "Filter Resonance", "Filter Resonance" };

    using Attachement = juce::AudioProcessorValueTreeState::SliderAttachment;
    void SetSliderWithLabel(juce::Slider& slider, juce::Label& Label, juce::AudioProcessorValueTreeState& apvts, juce::String paramid, std::unique_ptr<Attachement>& attachment);
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
