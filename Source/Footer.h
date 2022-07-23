/*
  ==============================================================================

    Footer.h
    Created: 19 Jul 2022 8:18:10pm
    Author:  butch

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ComponentSizeConstraints.h"

//==============================================================================
/*
*/
class Footer  : public juce::Component
{
public:
    Footer();
    ~Footer() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Label coprLabel; // Copyright
    juce::Label websiteLabel; // Website address

    //==============================================================================
    // Flexbox constraints
    const int MAX_HEIGHT = 50.0f;

    const int MIN_LABEL_HEIGHT = 25.0f;
    const int MIN_LABEL_WIDTH = 150.0f;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Footer)
};
