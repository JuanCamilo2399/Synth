/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 4 Jan 2023 12:56:21pm
    Author:  Usuario

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId)
{
    componentName = name;

    setsliderparams(Attackslider, attackLabel, apvts, attackId, attackAttachement);
    setsliderparams(Decayslider, decayLabel, apvts, decayId, decayAttachement);
    setsliderparams(Sustainslider, sustainLabel, apvts, sustainId, sustainAttachement);
    setsliderparams(Releaseslider, releaseLabel, apvts, releaseId, releaseAttachement);
    
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    auto  bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText(componentName, labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void AdsrComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight() - 45;
    const auto sliderStartX = padding + 5;
    const auto sliderStartY = 55;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    const auto labelStart = sliderStartY - labelYOffset;

    Attackslider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    attackLabel.setBounds(Attackslider.getX(), labelStart, sliderWidth, labelHeight);

    Decayslider.setBounds(Attackslider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    decayLabel.setBounds(Decayslider.getX(), labelStart, sliderWidth, labelHeight);

    Sustainslider.setBounds(Decayslider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainLabel.setBounds(Sustainslider.getX(), labelStart, sliderWidth, labelHeight);

    Releaseslider.setBounds(Sustainslider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseLabel.setBounds(Releaseslider.getX(), labelStart, sliderWidth, labelHeight);
    
}
using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
void AdsrComponent::setsliderparams(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

}
