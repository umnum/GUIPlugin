/*
  ==============================================================================

    Oscilliscope.h
    Created: 19 Mar 2020 5:07:14pm
    Author:  Michael Castanieto
    Description: This is a component class for displaying the AudioProcessor's output
                 in real time.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class Oscilliscope : public Component, private Timer
{
public:
    Oscilliscope(Guiplugin2AudioProcessor&);
    ~Oscilliscope();
    
    void paint (Graphics&) override;
    void resized() override;
    
private:
    void timerCallback() override;
    
    // displays the stored audio content
    AudioThumbnail *thumbnail;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscilliscope)
};
