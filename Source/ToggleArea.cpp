/*
  ==============================================================================

    ToggleArea.cpp
    Created: 16 Mar 2020 5:12:34pm
    Author:  Michael Castanieto

  ==============================================================================
*/

#include "ToggleArea.h"

//==============================================================================
ToggleArea::ToggleArea(Guiplugin2AudioProcessor& p) :
toggleStrip(ImageFileFormat::loadFrom(BinaryData::toggle_strip_png, (size_t)BinaryData::toggle_strip_pngSize)), processor(p)
{
    // set the look and feel of the toggle button
    toggleLookAndFeel = new ToggleLookAndFeel(&toggleStrip);
    
    // initialize the toggle button parameters
    toggleButton.setLookAndFeel(toggleLookAndFeel);
    toggleButton.setComponentID("toggle");
    toggleButton.setToggleState(true, dontSendNotification);
    toggleButton.addListener(this);
    addAndMakeVisible(toggleButton);
    
    // initiailse toggle button label parameters
    toggleLabel.setText("Toggle On/Off", dontSendNotification);
    toggleLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(toggleLabel);
}

ToggleArea::~ToggleArea()
{
    toggleButton.setLookAndFeel(nullptr);
    delete toggleLookAndFeel;
}

void ToggleArea::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
}

void ToggleArea::resized()
{
    // define the button and button label's boundaries within the toggle area
    auto area = getLocalBounds();
    auto buttonArea = area.removeFromBottom(area.getHeight()*3/4);
    auto textArea = area;
    buttonArea.reduce(40, 20);
    toggleButton.setBounds(buttonArea);
    toggleLabel.setBounds(textArea);
}

void ToggleArea::buttonClicked(Button *button)
{
    const String componentID = button->getComponentID();
    // pass the toggle state value to the AudioProcessor
    if (componentID == "toggle")
    {
        *processor.isOn = button->getToggleState();
    }
}
