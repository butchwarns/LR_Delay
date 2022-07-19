/*
  ==============================================================================

    CustomLookAndFeel.cpp
    Created: 18 Jul 2022 8:36:11pm
    Author:  butch

  ==============================================================================
*/

#include "CustomLookAndFeel.h"

//==============================================================================
CustomLookAndFeel::CustomLookAndFeel()
{
    //==============================================================================
    // Colours
    setColour(juce::ResizableWindow::backgroundColourId, juce::Colours::black);

    setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::white);
    setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::white);
    setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::black);

    setColour(juce::TextEditor::outlineColourId, juce::Colours::white);
    setColour(juce::TextEditor::focusedOutlineColourId, juce::Colours::white);

    manrope = juce::Typeface::createSystemTypefaceFor(BinaryData::ManropeExtraBold_ttf, BinaryData::ManropeExtraBold_ttfSize);
    setDefaultSansSerifTypeface(manrope);
}

CustomLookAndFeel::~CustomLookAndFeel() {}

//==============================================================================
// Sliders
void CustomLookAndFeel::drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height,
                                         float sliderPosProportional, float rotaryStartAngle,
                                         float rotaryEndAngle, juce::Slider &slider)
{
    const int centerX = static_cast<int>(width / 2.0f);
    const int centerY = static_cast<int>(height / 2.0f);

    const int spacing = 10;
    const float lineWidth = 2.0f;

    juce::PathStrokeType stroke(lineWidth);

    //==============================================================================
    // Knob background
    juce::Path circlePath;
    circlePath.addEllipse(spacing, spacing, width - 2 * spacing, height - 2 * spacing);
    g.setColour(findColour(juce::Slider::rotarySliderFillColourId));
    g.fillPath(circlePath);

    //==============================================================================
    // Knob outline
    g.setColour(findColour(juce::Slider::rotarySliderOutlineColourId));
    juce::Path outlinePath;
    outlinePath.addEllipse(spacing, spacing, width - 2 * spacing, height - 2 * spacing);
    g.strokePath(outlinePath, stroke);

    //==============================================================================
    // Pointer
    juce::Path pointerPath;
    const int pointerWidth = 10;

    // Outline
    pointerPath.addEllipse((width - pointerWidth) * 0.5f, 1.25f * spacing + 5.0f, pointerWidth, pointerWidth);
    // Rotate to start angle (CCW)
    pointerPath.applyTransform(juce::AffineTransform::rotation(-0.5f * (rotaryEndAngle - rotaryStartAngle), width / 2, height / 2));
    // Apply rotation according to slider value
    pointerPath.applyTransform(juce::AffineTransform::rotation((rotaryEndAngle - rotaryStartAngle) * sliderPosProportional, width / 2, height / 2));

    g.setColour(findColour(juce::Slider::rotarySliderOutlineColourId));
    g.strokePath(pointerPath, stroke);
}

//==============================================================================
juce::Font CustomLookAndFeel::getLabelFont(juce::Label &l)
{
    return juce::Font(manrope).withHeight(20.0f);
}