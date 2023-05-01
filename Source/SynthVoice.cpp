/*
  ==============================================================================

    SynthVoice.cpp
    Created: 1 Nov 2022 3:30:05pm
    Author:  pc9sb-13

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    
    return dynamic_cast<juce::SynthesiserSound*> (sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    osc.setWaveFrequency(midiNoteNumber);
    adsr.noteOn();
    modAdsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
    modAdsr.noteOff();
    if (!allowTailOff || !adsr.isActive())
    {
        clearCurrentNote();
    }

}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void SynthVoice::prepareToplay(double samplerate, int samplesperblock, int outputchannels)
{
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesperblock;
    spec.sampleRate = samplerate;
    spec.numChannels = outputchannels;

    osc.preparetoplay(spec);
    adsr.setSampleRate(samplerate);
    filter.preparetoplay(samplerate, samplesperblock, outputchannels);
    modAdsr.setSampleRate(samplerate);

    gain.prepare(spec);
    gain.setGainLinear(0.01f);

    isPrepared = true; //Make sure all samplerates are set before rendering Voice
}

void SynthVoice::updateAdsr(const float attack, const float decay, const float sustain, const float release)
{
    adsr.updateADSR(attack, decay, sustain, release);

}



void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);

    if (!isVoiceActive())
        return;

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    modAdsr.applyEnvelopeToBuffer(synthBuffer, 0, numSamples);
    synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
    osc.getNextAudioBlock(audioBlock);
    filter.process(synthBuffer);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    
    for (int channel = 0; channel<outputBuffer.getNumChannels(); channel++)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

        if (! adsr.isActive())
        {
            clearCurrentNote();
        }
    }
    modAdsr.getNextSample();
    


}

void SynthVoice::updateFilter(const int filterType, const float cutoff, const float resonance)
{
    float modulator = modAdsr.getNextSample();
    filter.updateParameters(filterType, cutoff, resonance, modulator);
}

void SynthVoice::updateModAdsr(const float attack, const float decay, const float sustain, const float release)
{
    modAdsr.updateADSR(attack, decay, sustain, release);

}



void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
   
}
