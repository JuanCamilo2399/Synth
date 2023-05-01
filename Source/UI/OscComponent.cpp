/*
  ==============================================================================

    OscComponent.cpp
    Created: 4 Jan 2023 2:59:13pm
    Author:  Usuario

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String WaveSelectorID, juce::String FmFreqId, juce::String FmdepthId)
{
    juce::StringArray choices{ "Sine" , "Saw", "Square" };
    OscWaveSelector.addItemList(choices, 1);
    addAndMakeVisible(OscWaveSelector);

    OscWaveSelectorAttachement = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, WaveSelectorID, OscWaveSelector);

    waveSelectorLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    waveSelectorLabel.setFont(15.0f);
    waveSelectorLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(waveSelectorLabel);

    setSliderWithLabel(fmfreqSlider, fmFreqLabel, apvts, FmFreqId, fmfreqAttachement);
    setSliderWithLabel(fmdepthSlider, fmDepthLabel, apvts, FmdepthId, fmdepthAttachement);

}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
   
    auto  bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Oscillator", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void OscComponent::resized()
{
    const auto startY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto LabelYOffset = 20;
    const auto LabelHeight = 20;


    OscWaveSelector.setBounds(10, startY + 5, 90, 30);
    waveSelectorLabel.setBounds(10, startY - LabelYOffset, 90, LabelHeight);

    fmfreqSlider.setBounds(OscWaveSelector.getRight(), startY,sliderWidth, sliderHeight);
    fmFreqLabel.setBounds(fmfreqSlider.getX(),fmfreqSlider.getY()- LabelYOffset,fmfreqSlider.getWidth(), LabelHeight);
    
    fmdepthSlider.setBounds(fmfreqSlider.getRight(), startY, sliderWidth, sliderHeight);
    fmDepthLabel.setBounds(fmdepthSlider.getX(), fmdepthSlider.getY() - LabelYOffset, fmdepthSlider.getWidth(), LabelHeight);
}
using Attachement = juce::AudioProcessorValueTreeState::SliderAttachment;
void OscComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& Label, juce::AudioProcessorValueTreeState& apvts, juce::String paramid, std::unique_ptr<Attachement>& attachment)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);

    attachment = std::make_unique< juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramid, slider);

    Label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    Label.setFont(15.0f);
    Label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(Label);
}


