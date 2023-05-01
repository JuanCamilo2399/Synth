/*
  ==============================================================================

    FilterComponent.cpp
    Created: 6 Jan 2023 3:30:01pm
    Author:  Usuario

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String FilterTypeID, juce::String FilterCutoffID, juce::String FilterResID)
{
    juce::StringArray choices{ "Low-Pass" , "Band-Pass", "High-Pass" };
    filterTypeSelector.addItemList(choices, 1);
    addAndMakeVisible(filterTypeSelector);

    FilterTypeAttachement = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, FilterTypeID, filterTypeSelector);

    FilterTypeLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    FilterTypeLabel.setFont(15.0f);
    FilterTypeLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(FilterTypeLabel);

    SetSliderWithLabel(filterCutoffSlider, FilterCutoffLabel, apvts, FilterCutoffID, FilterCutoffAttachnment);
    SetSliderWithLabel(filterResonanceSlider, FilterResonanceLabel, apvts, FilterResID, FilterResonanceAttachnment);
    

}

FilterComponent::~FilterComponent()
{
    
}

void FilterComponent::paint (juce::Graphics& g)
{
    auto  bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Filter", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void FilterComponent::resized()
{
    const auto startY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto LabelYOffset = 20;
    const auto LabelHeight = 20;


    filterTypeSelector.setBounds(10, startY + 5, 90, 30);
    FilterTypeLabel.setBounds(10, startY - LabelYOffset, 90, LabelHeight);

    filterCutoffSlider.setBounds(filterTypeSelector.getRight(), startY, sliderWidth, sliderHeight);
    FilterCutoffLabel.setBounds(filterCutoffSlider.getX(), filterCutoffSlider.getY() - LabelYOffset, filterCutoffSlider.getWidth(), LabelHeight);

    filterResonanceSlider.setBounds(filterCutoffSlider.getRight(), startY, sliderWidth, sliderHeight);
    FilterResonanceLabel.setBounds(filterResonanceSlider.getX(), filterResonanceSlider.getY() - LabelYOffset, filterResonanceSlider.getWidth(), LabelHeight);

}

void FilterComponent::SetSliderWithLabel(juce::Slider& slider, juce::Label& Label, juce::AudioProcessorValueTreeState& apvts, juce::String paramid, std::unique_ptr<Attachement>& attachment)
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
