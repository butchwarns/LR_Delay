/*
  ==============================================================================

    CustomLookAndFeel.cpp

    Copyright (C) 2022 Butch Warns
    contact@butchwarns.de

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

    manropeExtraBold = juce::Typeface::createSystemTypefaceFor(BinaryData::ManropeExtraBold_ttf, BinaryData::ManropeExtraBold_ttfSize);
    manropeLight = juce::Typeface::createSystemTypefaceFor(BinaryData::ManropeLight_ttf, BinaryData::ManropeLight_ttfSize);
    setDefaultSansSerifTypeface(manropeExtraBold);
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

    const int spacing = 0.13 * width;
    const float lineWidth = 0.04 * width;

    juce::PathStrokeType stroke(lineWidth);

    // Set height and width so that the rotary will always be drawn as a circle, and not elliptical
    width = juce::jmin(width, height);
    height = juce::jmin(width, height);

    //==============================================================================
    // Knob outline
    g.setColour(findColour(juce::Slider::rotarySliderOutlineColourId));
    juce::Path outlinePath;
    outlinePath.addEllipse(spacing, spacing, width - 2 * spacing, height - 2 * spacing);
    g.strokePath(outlinePath, stroke);

    //==============================================================================
    // Knob background
    juce::Path circlePath;
    circlePath.addEllipse(spacing, spacing, width - 2 * spacing, height - 2 * spacing);
    g.setColour(findColour(juce::Slider::rotarySliderFillColourId));
    g.fillPath(circlePath);

    //==============================================================================
    // Pointer
    juce::Path pointerPath;
    const int pointerWidth = 0.075 * width;

    // Outline
    pointerPath.addEllipse((width - pointerWidth) * 0.5f, 1.25f * spacing + 0.25 * pointerWidth, pointerWidth, pointerWidth);
    // Rotate to start angle (CCW)
    pointerPath.applyTransform(juce::AffineTransform::rotation(-0.5f * (rotaryEndAngle - rotaryStartAngle), width / 2, height / 2));
    // Apply rotation according to slider value
    pointerPath.applyTransform(juce::AffineTransform::rotation((rotaryEndAngle - rotaryStartAngle) * sliderPosProportional, width / 2, height / 2));

    g.setColour(findColour(juce::Slider::rotarySliderOutlineColourId));
    stroke.setStrokeThickness(lineWidth / 2.0f);
    g.strokePath(pointerPath, stroke);
}

//==============================================================================
juce::Font CustomLookAndFeel::getLabelFont(juce::Label &l)
{
    return getManropeExtraBoldFont().withHeight(16.0f).withExtraKerningFactor(0.03f);
}

juce::Font CustomLookAndFeel::getManropeLightFont()
{
    juce::Font manropeLightFont(manropeLight);
    return manropeLightFont;
}

juce::Font CustomLookAndFeel::getManropeExtraBoldFont()
{
    juce::Font manropeExtraBoldFont(manropeExtraBold);
    return manropeExtraBoldFont;
}
