/*
  ==============================================================================

    ToggleLookAndFeel.cpp
    Created: 18 Mar 2020 4:27:07pm
    Author:  Michael Castanieto

  ==============================================================================
*/

#include "ToggleLookAndFeel.h"

ToggleLookAndFeel::ToggleLookAndFeel(Image *_toggleStrip) : toggleStrip(_toggleStrip), frameCount(4)
{
    frameSize = toggleStrip->getWidth()/frameCount;
}

ToggleLookAndFeel::~ToggleLookAndFeel()
{
    toggleStrip.release();
}

void ToggleLookAndFeel::drawToggleButton(Graphics &g, ToggleButton &button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    // locate the position of the toggle image within the image strip depending on the button's toggle state
    int pos;
    if (button.getToggleState())
    {
        if (button.isDown())
        {
            pos = 1;
        }
        else
        {
            pos = 0;
        }
    }
    else
    {
        if (button.isDown())
        {
            pos = 3;
        }
        else
        {
            pos = 2;
        }
    }
    // display the toggle button's image 
    g.drawImage(*toggleStrip, 0, 0, button.getWidth(), button.getHeight(), pos*frameSize, 0, toggleStrip->getWidth()/frameCount, toggleStrip->getHeight());
}
