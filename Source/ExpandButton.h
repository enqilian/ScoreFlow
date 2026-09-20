/*
  ==============================================================================

    ExpandButton.h
    A small square icon button (diagonal double-arrow) used to toggle the
    independent presentation window. Styled to match the rest of the app:
    the same dark button colour as Play/Pause/etc, with the app's pink
    accent as an outline.

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ExpandButton : public juce::Button
{
public:
    ExpandButton() : juce::Button("Expand") {}

    void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        auto bounds = getLocalBounds().toFloat().reduced(0.5f);
        float cornerSize = 6.0f;

        // 跟 Play/Pause 等其它按钮同一个背景色，保持风格统一
        auto backgroundColour = findColour(juce::TextButton::buttonColourId);
        if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
            backgroundColour = backgroundColour.contrasting(shouldDrawButtonAsDown ? 0.2f : 0.05f);

        g.setColour(backgroundColour);
        g.fillRoundedRectangle(bounds, cornerSize);

        // 用软件里统一的粉色描边，跟 PDF 框的边框呼应
        g.setColour(juce::Colours::pink);
        g.drawRoundedRectangle(bounds, cornerSize, 1.5f);

        auto inset = bounds.reduced(bounds.getWidth() * 0.3f);
        float thickness = juce::jmax(1.5f, bounds.getWidth() * 0.09f);
        float headWidth = thickness * 2.6f;
        float headLength = thickness * 2.2f;

        // 未打开放大窗口时箭头指向外(展开)，已打开时指向内(收起)
        juce::Point<float> topRight(inset.getRight(), inset.getY());
        juce::Point<float> bottomLeft(inset.getX(), inset.getBottom());
        juce::Point<float> centre = inset.getCentre();

        juce::Path arrows;
        if (getToggleState())
        {
            arrows.addArrow(juce::Line<float>(topRight, centre), thickness, headWidth, headLength);
            arrows.addArrow(juce::Line<float>(bottomLeft, centre), thickness, headWidth, headLength);
        }
        else
        {
            arrows.addArrow(juce::Line<float>(centre, topRight), thickness, headWidth, headLength);
            arrows.addArrow(juce::Line<float>(centre, bottomLeft), thickness, headWidth, headLength);
        }

        g.setColour(juce::Colours::white);
        g.fillPath(arrows);
    }
};
