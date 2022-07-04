#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class FabulousFilterAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    FabulousFilterAudioProcessorEditor(FabulousFilterAudioProcessor&);
    ~FabulousFilterAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;
private:
    juce::LookAndFeel_V4 look;

    juce::Label title;
    juce::Label left;
    juce::Label right;
    juce::Label order;

    juce::Slider l_bound_dial;
    juce::Slider r_bound_dial;
    juce::ComboBox funcOrder;

    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> l_bound_value;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> r_bound_value;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::ComboBoxAttachment> funcOrderValue;

    FabulousFilterAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FabulousFilterAudioProcessorEditor)
};
