/*
  ==============================================================================

    ToggleLookAndFeel.h
    Created: 18 Mar 2020 4:27:07pm
    Author:  Michael Castanieto
    Description: This class describes the look and feel of the toggle button

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class ToggleLookAndFeel : public LookAndFeel_V4
{
public:
    ToggleLookAndFeel(Image* _toggleStrip);
    ~ToggleLookAndFeel();
    void drawToggleButton(Graphics &g, ToggleButton &button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
private:
    std::unique_ptr<Image> toggleStrip;
    int frameCount;
    int frameSize;
};
