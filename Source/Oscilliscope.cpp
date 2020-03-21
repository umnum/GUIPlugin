/*
  ==============================================================================

    Oscilliscope.cpp
    Created: 19 Mar 2020 5:07:14pm
    Author:  Michael Castanieto

  ==============================================================================
*/

#include "Oscilliscope.h"

Oscilliscope::Oscilliscope(Guiplugin2AudioProcessor& p) 
{
    // thumnail is initialized in the AudioProcessor
    thumbnail = p.getThumbnail();
    // paint() refresh rate is 40 milliseconds
    startTimer(40);
}

Oscilliscope::~Oscilliscope()
{
}

void Oscilliscope::paint (Graphics& g)
{
    // display 10 ms of the audio output
    g.setColour(Colours::yellow);
    if (thumbnail->getTotalLength() > 0.0)
    {
        thumbnail->drawChannels(g, getLocalBounds(), 0.0, 0.01f, 1.0f);
    }
}

void Oscilliscope::resized()
{
    
}

void Oscilliscope::timerCallback()
{
    repaint();
}
