/*
  ==============================================================================

    SliderArea.h
    Created: 16 Mar 2020 5:10:36pm
    Author:  Michael Castanieto
    Description: This component contains any sliders

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SliderLookAndFeel.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class SliderArea    : public Component,
public Slider::Listener
{
public:
    SliderArea(Guiplugin2AudioProcessor&);
    ~SliderArea();

    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;

private:
    Guiplugin2AudioProcessor& processor;
    
    SliderLookAndFeel *sliderLookAndFeel;
    Slider volumeSlider;
    Label volumeLabel;
    Slider pitchSlider;
    Label pitchLabel;
    Image sliderKnobStrip;
    Image sliderBackground;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderArea)
};
