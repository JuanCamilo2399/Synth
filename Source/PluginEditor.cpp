/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NunisSynthAudioProcessorEditor::NunisSynthAudioProcessorEditor (NunisSynthAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , audioProcessor (p)
    ,osc(audioProcessor.apvts, "OSC1WAVETYPE", "FMFREQ","FMDEPTH")
    ,adsr("Amp Envelope",audioProcessor.apvts,"ATTACK","DECAY","SUSTAIN","RELEASE")
    ,Filter(audioProcessor.apvts, "FILTERTYPE","FILTERCUTOFF","FILTERRES")
    ,ModAdsr("Mod Envelope",audioProcessor.apvts, "MODATTACK", "MODDECAY", "MODSUSTAIN", "MODRELEASE")
{
 
    setSize (620, 500);
    //make adsr visible
    addAndMakeVisible(adsr);
    //make osc visible
    addAndMakeVisible(osc);
    //make filter visible
    addAndMakeVisible(Filter);
    //make adsr modulator
    addAndMakeVisible(ModAdsr);
    
} 

NunisSynthAudioProcessorEditor::~NunisSynthAudioProcessorEditor()
{
}

//==============================================================================
void NunisSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black);
    
}

void NunisSynthAudioProcessorEditor::resized()
{
    const auto paddingX = 5;
    const auto paddingY = 35;
    const auto paddingY2 = 235;
    const auto width = 300;
    const auto height = 200;

    //OSC Bounds
    osc.setBounds(paddingX, paddingY, width, height);
    //ADSR Bounds
    adsr.setBounds(osc.getRight(), paddingY, width,height);
    //Filter Bounds
    Filter.setBounds(paddingX,paddingY2,width,height);
    //ADSR Mod Bounds
    ModAdsr.setBounds(Filter.getRight(), paddingY2, width, height);
}


