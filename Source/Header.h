#pragma once

#include <JuceHeader.h>
#include "ComponentSizeConstraints.h"

//==============================================================================
/*
*/
class Header  : public juce::Component
{
public:
    Header();
    ~Header() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Label titleLabel;
    juce::Label versionLabel;

    //==============================================================================
    // Flexbox constraints
    const int MAX_HEIGHT = 50.0f;

    const int MIN_LABEL_HEIGHT = 25.0f;
    const int MIN_LABEL_WIDTH = 150.0f;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Header)
};
