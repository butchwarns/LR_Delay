/*
  ==============================================================================

    Header.h

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
