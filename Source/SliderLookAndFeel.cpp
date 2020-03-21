/*
  ==============================================================================

    SliderLookAndFeel.cpp
    Created: 17 Mar 2020 5:14:00pm
    Author:  Michael Castanieto

  ==============================================================================
*/

#include "SliderLookAndFeel.h"

SliderLookAndFeel::SliderLookAndFeel(Image *_sliderStrip) : sliderStrip(_sliderStrip), frameCount(60)
{
    int width = sliderStrip->getWidth();
    frameSize = width/frameCount;
}

SliderLookAndFeel::~SliderLookAndFeel()
{
    sliderStrip.release();
}

void SliderLookAndFeel::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &slider)
{
    drawFrame(g, x, y, width, height, slider);
}

void SliderLookAndFeel::drawFrame(Graphics &g, int x, int y, int width, int height, Slider &slider)
{
    const double div = slider.getMaximum() / frameCount;
    double pos = (int)(slider.getValue() / div);
    
    if (pos > 0)
        pos = pos - 1;
    
    g.drawImage(*sliderStrip, x-5, y-10, width, height+20, (int)(pos*frameSize), 0, sliderStrip->getWidth()/frameCount, sliderStrip->getHeight());
}
