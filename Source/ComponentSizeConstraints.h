/*
  ==============================================================================

    ComponentSizeConstraints.h
    Created: 20 Jul 2022 4:44:16pm
    Author:  butch

  ==============================================================================
*/

#pragma once

//==============================================================================
// Useful cosntants
const float PHI = 1.618033988749;
//==============================================================================
// Sliders and their labels
const int MIN_SLIDER_LABEL_HEIGHT = 25;

// const int MIN_ROTARY_WIDTH = 80;
const int MIN_ROTARY_WIDTH = 100;
const int MIN_ROTARY_HEIGHT = MIN_ROTARY_WIDTH;

const int MIN_SLIDER_TEXTBOX_HEIGHT = 25;

const int MIN_SLIDER_HEIGHT = MIN_ROTARY_HEIGHT + MIN_SLIDER_TEXTBOX_HEIGHT;
const int MIN_SLIDER_WITH_LABEL_HEIGHT = MIN_SLIDER_HEIGHT + MIN_SLIDER_LABEL_HEIGHT;
//==============================================================================
// Header / footer
const int MIN_HEADER_HEIGHT = 25;
const int MIN_FOOTER_HEIGHT = 25;

//==============================================================================
// Utility area
const int MIN_UTIL_WIDTH = MIN_ROTARY_WIDTH;
const int MIN_UTIL_HEIGHT = 3 * MIN_SLIDER_WITH_LABEL_HEIGHT;

//==============================================================================
// Main LR area
const int MIN_LR_WIDTH = 2 * MIN_ROTARY_WIDTH;
const int MIN_LR_HEIGHT = 5 * MIN_SLIDER_WITH_LABEL_HEIGHT;