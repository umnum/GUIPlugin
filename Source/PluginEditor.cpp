/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Guiplugin2AudioProcessorEditor::Guiplugin2AudioProcessorEditor (Guiplugin2AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), sliderArea(p), toggleArea(p), oscilliscope(p)
{
    // add all the components to the plugin editor
    addAndMakeVisible(sliderArea);
    addAndMakeVisible(toggleArea);
    addAndMakeVisible(oscilliscope);
    setSize (400, 300);
}

Guiplugin2AudioProcessorEditor::~Guiplugin2AudioProcessorEditor()
{
    
}

//==============================================================================
void Guiplugin2AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

}

void Guiplugin2AudioProcessorEditor::resized()
{
    // set all the component boundaries withtin the plugin editor
    auto area = getLocalBounds();
    sliderArea.setBounds(area.removeFromLeft(area.getWidth()/2));
    toggleArea.setBounds(area.removeFromTop(area.getHeight()/2));
    oscilliscope.setBounds(area);
}
