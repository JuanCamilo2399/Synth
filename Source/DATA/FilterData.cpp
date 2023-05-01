/*
  ==============================================================================

    Filter.cpp
    Created: 6 Jan 2023 3:28:48pm
    Author:  Usuario

  ==============================================================================
*/

#include "FilterData.h"

void FilterData::preparetoplay(double samplerate, int samplesPerBlock, int numChannels)
{
    filter.reset();

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = samplerate;
    spec.numChannels = numChannels;
    filter.prepare(spec);

    isPrepared = true;
}

void FilterData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    juce::dsp::AudioBlock<float> block {buffer};
    filter.process(juce::dsp::ProcessContextReplacing<float> {block});
}

void FilterData::updateParameters(const int filtertype, const float frequency, const float resonance, const float modulator)
{
    

    switch (filtertype)
    {
    case 0:
        filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
        break;
    case 1:
        filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
        break;
    case 2:
        filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
        break;
    default:

        break;
    }

    float modfreq = frequency * modulator;
    modfreq = std::fmaxf(modfreq, 20.0f);
    modfreq = std::fminf(modfreq, 20000.0f);

    filter.setCutoffFrequency(modfreq);
    filter.setResonance(resonance);

}

void FilterData::reset()
{
    filter.reset();
}
