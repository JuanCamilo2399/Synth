/*
  ==============================================================================

    AdsrData.cpp
    Created: 4 Jan 2023 12:56:54pm
    Author:  Usuario

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsrparams.attack = attack;
    adsrparams.decay = decay;
    adsrparams.sustain = sustain;
    adsrparams.release = release;

   setParameters(adsrparams);
}