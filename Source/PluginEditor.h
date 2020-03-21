/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SliderArea.h"
#include "ToggleArea.h"
#include "Oscilliscope.h"

//==============================================================================
/**
*/
class Guiplugin2AudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Guiplugin2AudioProcessorEditor (Guiplugin2AudioProcessor&);
    ~Guiplugin2AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Guiplugin2AudioProcessor& processor;
    
    SliderArea sliderArea;
    ToggleArea toggleArea;
    Oscilliscope oscilliscope;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Guiplugin2AudioProcessorEditor)
};
