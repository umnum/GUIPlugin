/*
  ==============================================================================

    ToggleArea.h
    Created: 16 Mar 2020 5:12:34pm
    Author:  Michael Castanieto
    Description: This component contains any toggle switches

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ToggleLookAndFeel.h"
#include "PluginProcessor.h"
#include "Oscilliscope.h"

//==============================================================================
/*
*/
class ToggleArea    : public Component,
public Button::Listener
{
public:
    ToggleArea(Guiplugin2AudioProcessor&);
    ~ToggleArea();

    void paint (Graphics&) override;
    void resized() override;
    void buttonClicked(Button* button) override;

private:
    Guiplugin2AudioProcessor& processor;
    
    ToggleLookAndFeel *toggleLookAndFeel;
    ToggleButton toggleButton;
    Label toggleLabel;
    Image toggleStrip;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToggleArea)
};
