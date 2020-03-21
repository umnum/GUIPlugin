/*
  ==============================================================================

    SliderArea.cpp
    Created: 16 Mar 2020 5:10:36pm
    Author:  Michael Castanieto

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SliderArea.h"


//==============================================================================
SliderArea::SliderArea(Guiplugin2AudioProcessor& p) : sliderKnobStrip(ImageFileFormat::loadFrom(BinaryData::slider_knob_strip_png, (size_t)BinaryData::slider_knob_strip_pngSize)),
    sliderBackground(ImageFileFormat::loadFrom(BinaryData::slider_strip_background_png, (size_t)BinaryData::slider_strip_background_pngSize)), processor(p)
{
    // set the look and feel of sliders
    sliderLookAndFeel = new SliderLookAndFeel(&sliderKnobStrip);
    
    // initialize the volume slider's parameters
    volumeSlider.setLookAndFeel(sliderLookAndFeel);
    volumeSlider.setSliderStyle(Slider::LinearVertical);
    volumeSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    volumeSlider.setComponentID("volume");
    volumeSlider.setRange(0.0f, 1.0f);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);
    
    // initialize the volume label's parameters
    volumeLabel.setText("Volume", dontSendNotification);
    volumeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(volumeLabel);
    
    // initialize the pitch slider's parameters
    pitchSlider.setLookAndFeel(sliderLookAndFeel);
    pitchSlider.setSliderStyle(Slider::LinearVertical);
    pitchSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    pitchSlider.setComponentID("pitch");
    pitchSlider.setRange(20.0f, 1000.0f);
    pitchSlider.setValue(440.0f);
    pitchSlider.addListener(this);
    addAndMakeVisible(pitchSlider);
    
    // initialize the pitch label's parameters
    pitchLabel.setText("Pitch", dontSendNotification);
    pitchLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(pitchLabel);

}

SliderArea::~SliderArea()
{
    volumeSlider.setLookAndFeel(nullptr);
    pitchSlider.setLookAndFeel(nullptr);
    delete sliderLookAndFeel;
}

void SliderArea::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
    
    // draw the slider panels within the slider area
    auto area = getLocalBounds().toFloat();
    auto background = area.removeFromBottom(area.getHeight()*7.0/8.0);
    g.drawImage(sliderBackground, background.removeFromLeft(background.getWidth()/2.0));
    g.drawImage(sliderBackground, background);
}

void SliderArea::resized()
{
    // define the volume and pitch slider's boundaries within the slider area
    auto area = getLocalBounds();
    auto sliders = area.removeFromBottom(area.getHeight()*7.0/8.0);
    auto sliderLeft = sliders.removeFromLeft(sliders.getWidth()/2.0);
    auto sliderRight = sliders;
    sliderLeft.reduce(30,0);
    sliderRight.reduce(30,0);
    volumeSlider.setBounds(sliderLeft);
    pitchSlider.setBounds(sliderRight);
    auto labels = area;
    volumeLabel.setBounds(labels.removeFromLeft(labels.getWidth()/2.0));
    pitchLabel.setBounds(labels);

}

void SliderArea::sliderValueChanged(Slider *slider)
{
    const String componentID = slider->getComponentID();
    if (componentID == "volume")
    {
        // pass the volume slider's value to the AudioProcessor
        *processor.volume = (float) slider->getValue();
    }
    else if (componentID == "pitch")
    {
        // pass the pitch slider's value to the AudioProcessor
        *processor.pitch = (float) slider->getValue();
        // update the sine wave angle's rate of change
        processor.updateAngleDelta();
    }
}
