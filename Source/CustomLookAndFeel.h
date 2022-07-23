/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 18 Jul 2022 8:36:11pm
    Author:  butch

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel();
    virtual ~CustomLookAndFeel();

    juce::Font getManropeLightFont();
    juce::Font getManropeExtraBoldFont();

private:
    //==============================================================================
    // Sliders
    virtual void drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height,
                                  float sliderPosProportional, float rotaryStartAngle,
                                  float rotaryEndAngle, juce::Slider &slider) override;

    //==============================================================================
    // Fonts
    juce::Typeface::Ptr manropeExtraBold;
    juce::Typeface::Ptr manropeLight;

    virtual juce::Font getLabelFont(juce::Label &l) override;
};