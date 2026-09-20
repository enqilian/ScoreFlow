/*
  ==============================================================================

    PresentationWindow.h
    An independent, resizable top-level window that shows the current PDF
    page enlarged for an audience/performer display, separate from the
    main control window.

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PresentationWindow : public juce::DocumentWindow
{
public:
    PresentationWindow();
    ~PresentationWindow() override;

    void setImage(const juce::Image& newImage);

    // Called when the user closes the window via its native close button,
    // so the owner can update its own UI state (e.g. the toggle button text).
    std::function<void()> onCloseButtonPressed;

    void closeButtonPressed() override;

private:
    class PresentationContent : public juce::Component
    {
    public:
        void paint(juce::Graphics& g) override;
        void setImage(const juce::Image& newImage);

    private:
        juce::Image image;
    };

    PresentationContent content;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresentationWindow)
};
