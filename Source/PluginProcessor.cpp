/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthSound.h"
#include "SynthVoice.h"


//==============================================================================
NunisSynthAudioProcessor::NunisSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this,nullptr,"Parameters",CreateParameters())
                        
#endif
{
    Synth.addSound(new synthSound());
    Synth.addVoice(new SynthVoice());
}

NunisSynthAudioProcessor::~NunisSynthAudioProcessor()
{
}

//==============================================================================
const juce::String NunisSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NunisSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NunisSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NunisSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NunisSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NunisSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NunisSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NunisSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NunisSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void NunisSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NunisSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    Synth.setCurrentPlaybackSampleRate(sampleRate);
    
    for (int i = 0; i < Synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(Synth.getVoice(i)))
        {
            voice->prepareToplay(sampleRate, samplesPerBlock, 2);
        }
    }
    
}

void NunisSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NunisSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NunisSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for (int i = 0 ; i<Synth.getNumVoices(); ++i) //Check if Voice its a SynthesiserVoice
    {
        if (auto voice = dynamic_cast<SynthVoice*>(Synth.getVoice(i))) //check if is a synthesisterVoice
        {
            //Osc Controls
            //ADSR
            //LFO
            //This parameters will be updated by the value tree state

            //Oscillator
            auto& oscWave = *apvts.getRawParameterValue("OSC1WAVETYPE");
            auto& fmDepth = *apvts.getRawParameterValue("FMDEPTH");
            auto& fmFrequecy = *apvts.getRawParameterValue("FMFREQ");

            //Amp Adsr
            auto& attack  = *apvts.getRawParameterValue("ATTACK");
            auto& decay   = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            //Filter
            auto& filterType = *apvts.getRawParameterValue("FILTERTYPE");
            auto& cutoff = *apvts.getRawParameterValue("FILTERCUTOFF");
            auto& resonance = *apvts.getRawParameterValue("FILTERRES");

            //Mod Adsr
            auto& modattack = *apvts.getRawParameterValue("MODATTACK");
            auto& moddecay = *apvts.getRawParameterValue("MODDECAY");
            auto& modsustain = *apvts.getRawParameterValue("MODSUSTAIN");
            auto& modrelease = *apvts.getRawParameterValue("MODRELEASE");

           
            voice->updateAdsr(attack.load(),decay.load(), sustain.load(), release.load());
            voice->getOscillator().setFmParams(fmDepth, fmFrequecy);
            voice->getOscillator().SetWaveType(oscWave);
            voice->updateFilter(filterType.load(), cutoff.load(), resonance.load());
            voice->updateModAdsr(modattack.load(), moddecay.load(), modsustain.load(), modrelease.load());
        }
    }

    Synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());


}

//==============================================================================
bool NunisSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NunisSynthAudioProcessor::createEditor()
{
    return new NunisSynthAudioProcessorEditor (*this);
}

//==============================================================================
void NunisSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NunisSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NunisSynthAudioProcessor();
}
//Value Tree
juce::AudioProcessorValueTreeState::ParameterLayout NunisSynthAudioProcessor::CreateParameters()
{
    // Combobox: switch between Oscillator
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;
    //List of range audio parameter
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID{"OSC", 1}, "Oscillator", juce::StringArray{ "Sine","Saw","Square" }, 0)); //Combobox Inicialitation
    //FM
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"FMFREQ", 1}, "FM frequency", juce::NormalisableRange<float>{0.0f, 1000.0f, 0.01f,0.3f }, 0.0f));
    
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"FMDEPTH", 1}, "FM Depth", juce::NormalisableRange<float>{0.0f, 1000.0f,0.01f,0.3f }, 0.0f));
    // Attack - float
    // Decay - float
    // Release - float
    // Sustain - float
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"ATTACK", 1}, "Attack", juce::NormalisableRange<float>{0.1f, 1.0f, }, 0.1f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"DECAY", 1}, "Decay", juce::NormalisableRange<float>{0.1f, 1.0f, }, 0.1f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"SUSTAIN", 1}, "Sustain", juce::NormalisableRange<float>{0.1f, 1.0f, }, 1.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"RELEASE", 1}, "Release", juce::NormalisableRange<float>{0.1f, 3.0f, }, 0.0f));
    
    //Filter ADSR
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"MODATTACK", 1}, "Mod Attack", juce::NormalisableRange<float>{0.1f, 1.0f, }, 0.1f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"MODDECAY", 1}, " Mod Decay", juce::NormalisableRange<float>{0.1f, 1.0f, }, 0.1f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"MODSUSTAIN", 1}, " Mod Sustain", juce::NormalisableRange<float>{0.1f, 1.0f, }, 1.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"MODRELEASE", 1}, " Mod Release", juce::NormalisableRange<float>{0.1f, 3.0f, }, 0.0f));


    parameters.push_back(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID{"OSC1WAVETYPE", 1}, "osc 1 Wave Type", juce::StringArray{ "Sine","Saw","Square" }, 0, ""));
    //Filter

    parameters.push_back(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID{"FILTERTYPE", 1}, "Filter Type", juce::StringArray{ "Low-Pass","Band-Pass","High-pass" }, 0));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"FILTERCUTOFF", 1}, "Filter Cutoff", juce::NormalisableRange<float>{20.0f, 20000.0f, 0.1f, 0.6f }, 200.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"FILTERRES", 1}, "Filter Resonance", juce::NormalisableRange<float>{1.0f, 10.0f, 0.1f}, 1.0f));
    
    return { parameters.begin(), parameters.end() };
}
