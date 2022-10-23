/*
  ==============================================================================

    ComponentSizeConstraints.h

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

//==============================================================================
// Useful cosntants
const float PHI = 1.618033988749;
//==============================================================================
// Sliders and their labels
const int MIN_SLIDER_LABEL_HEIGHT = 25;

const int MIN_ROTARY_WIDTH = 75;
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