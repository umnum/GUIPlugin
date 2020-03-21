/*
  ==============================================================================

    SliderLookAndFeel.h
    Created: 17 Mar 2020 5:14:00pm
    Author:  Michael Castanieto
    Description: This class describes the look and feel of the sliders

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class SliderLookAndFeel : public LookAndFeel_V4
{
public:
    SliderLookAndFeel(Image* _sliderStrip);
    ~SliderLookAndFeel();
    void drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &slider) override;
    // draw the correct slider frame according to the slider's value
    void drawFrame (Graphics &g, int x, int y, int width, int height, Slider &slider);
private:
    std::unique_ptr<Image> sliderStrip;
    int frameCount;
    int frameSize;
};
