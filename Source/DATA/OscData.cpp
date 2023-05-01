/*
  ==============================================================================

    OscData.cpp
    Created: 4 Jan 2023 2:21:55pm
    Author:  Usuario

  ==============================================================================
*/

#include "OscData.h"

void OscData::preparetoplay(juce::dsp::ProcessSpec& spec)
{
	fmosc.prepare(spec);
	prepare(spec);
}

void OscData::SetWaveType(const int choice)
{
	switch (choice)
	{
	case 0: //Sine Wave
		initialise([](float x) {return std::sin(x); });
		break;
	case 1: //Saw Wave
		initialise([](float x) {return x/ juce::MathConstants<float>::pi; });
		break;
	case 2: //Square Wave
		initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f; });
		break; 
	default:
		jassertfalse; // this is how we know that something went wrong
		break;
	}
}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
	setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmMod);
	lastMidiNote = midiNoteNumber;
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
	for (int ch = 0; ch < block.getNumChannels(); ch++)
	{
		for (int s = 0; s<block.getNumSamples(); s++)
		{
			//Value of wave at one given point in time
			fmMod = fmosc.processSample(block.getSample(ch, s)) * fmDepth;
		}
	}

	process(juce::dsp::ProcessContextReplacing<float> (block));
}

void OscData::setFmParams(const float depth, const float frequency)
{
	fmosc.setFrequency(frequency);
	fmDepth = depth;
	auto currentFreq = juce::MidiMessage::getMidiNoteInHertz(lastMidiNote) + fmMod;
	setFrequency(currentFreq >= 0 ? currentFreq : currentFreq * -1.0f);

}
