/*
  ==============================================================================

    AdsrComponent.h
    Created: 4 Jan 2023 12:56:21pm
    Author:  Usuario

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrComponent  : public juce::Component
{
public:
    AdsrComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId);
    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    void setsliderparams(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);
    juce::Slider Attackslider;
    juce::Slider Decayslider;
    juce::Slider Sustainslider;
    juce::Slider Releaseslider;
    
   

    using SliderAttachement = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachement> attackAttachement;
    std::unique_ptr<SliderAttachement> decayAttachement;
    std::unique_ptr<SliderAttachement> sustainAttachement;
    std::unique_ptr<SliderAttachement> releaseAttachement;
    
    juce::Label attackLabel{ "Attack", "A"};
    juce::Label decayLabel{ "Decay", "D" };
    juce::Label sustainLabel{ "Sustain", "S" };
    juce::Label releaseLabel{ "Release", "R" };

    juce::String componentName{ "" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
