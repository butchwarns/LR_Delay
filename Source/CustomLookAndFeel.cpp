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
    setColour(juce::Slider::thumbColourId, juce::Colours::black);

    setColour(juce::TextEditor::outlineColourId, juce::Colours::white);
    setColour(juce::TextEditor::focusedOutlineColourId, juce::Colours::white);

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

    // Knob background
    juce::Path circlePath;
    circlePath.addEllipse(spacing, spacing, width - 2 * spacing, height - 2 * spacing);
    g.setColour(findColour(juce::Slider::backgroundColourId));
    g.fillPath(circlePath);

    // Knob outline
    g.setColour(juce::Colours::white);
    juce::Path outlinePath;
    outlinePath.addEllipse(spacing, spacing, width - 2 * spacing, height - 2 * spacing);
    g.strokePath(outlinePath, stroke);

    // Pointer
    juce::Path pointerPath;
    const int pointerWidth = 10;
    pointerPath.addEllipse((width - pointerWidth) * 0.5f, 1.25f * spacing + 5.0f, pointerWidth, pointerWidth);
    pointerPath.applyTransform(juce::AffineTransform::rotation(-0.5f * (rotaryEndAngle - rotaryStartAngle), width / 2, height / 2));
    pointerPath.applyTransform(juce::AffineTransform::rotation((rotaryEndAngle - rotaryStartAngle) * sliderPosProportional, width / 2, height / 2));
    // g.fillPath(pointerPath);
    g.setColour(juce::Colours::white);
    g.strokePath(pointerPath, stroke);
}

//==============================================================================
// Fonts
juce::Font CustomLookAndFeel::getLabelFont(juce::Label &l)
{
    return getManropeFont().withHeight(20.0f);
}

const juce::Font &CustomLookAndFeel::getManropeFont()
{
    static juce::Font manrope(juce::Typeface::createSystemTypefaceFor(BinaryData::ManropeBold_ttf,
                                                                      BinaryData::ManropeBold_ttfSize));
    return manrope;
}
