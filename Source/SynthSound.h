/*
  ==============================================================================

    SynthSound.h
    Created: 1 Nov 2022 3:30:20pm
    Author:  pc9sb-13

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class synthSound : public juce::SynthesiserSound
{
    public:
        bool appliesToNote(int midiNoteNumber) override { return true; }
        bool appliesToChannel(int midichannel) override { return true; }
};
    
          