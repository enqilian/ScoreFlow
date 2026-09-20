/*
  ==============================================================================

    PresentationWindow.cpp

  ==============================================================================
*/

#include "PresentationWindow.h"

PresentationWindow::PresentationWindow()
    : DocumentWindow("Score",
                      juce::Colours::white,
                      DocumentWindow::allButtons)
{
    setUsingNativeTitleBar(true);
    setContentNonOwned(&content, false);
    setResizable(true, true);

    auto displayArea = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea;
    centreWithSize(displayArea.getWidth() * 4 / 5, displayArea.getHeight() * 4 / 5);

    setVisible(true);
}

PresentationWindow::~PresentationWindow()
{
    setContentNonOwned(nullptr, false);
}

void PresentationWindow::setImage(const juce::Image& newImage)
{
    content.setImage(newImage);
}

void PresentationWindow::closeButtonPressed()
{
    setVisible(false);

    if (onCloseButtonPressed)
        onCloseButtonPressed();
}

void PresentationWindow::PresentationContent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::white);

    if (image.isValid())
        g.drawImage(image, getLocalBounds().toFloat(), juce::RectanglePlacement::centred);
}

void PresentationWindow::PresentationContent::setImage(const juce::Image& newImage)
{
    image = newImage;
    repaint();
}
