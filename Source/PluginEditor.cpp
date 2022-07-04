#include "PluginProcessor.h"
#include "PluginEditor.h"

FabulousFilterAudioProcessorEditor::FabulousFilterAudioProcessorEditor(FabulousFilterAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    // app size setup
    setSize(250, 325);
    // look and feel initialization
    look.setColour(juce::Slider::thumbColourId, juce::Colour(240, 235, 227));
    look.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(87, 111, 114));
    look.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(125, 157, 156));
    look.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(125, 157, 156));
    look.setColour(juce::Slider::textBoxTextColourId, juce::Colour(240, 235, 227));
    look.setColour(juce::Slider::textBoxOutlineColourId, juce::Colour(240, 235, 227));
    // title initialization
    title.setFont(juce::Font(22.0f, juce::Font::italic));
    title.setText("Fabulous Filter", juce::dontSendNotification);
    title.setColour(juce::Label::textColourId, juce::Colour(87, 111, 114));
    title.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&title);
    left.setFont(juce::Font(18.0f));
    left.setText("L Cutoff", juce::dontSendNotification);
    left.setColour(juce::Label::textColourId, juce::Colour(87, 111, 114));
    left.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&left);
    right.setFont(juce::Font(18.0f));
    right.setText("R Cutoff", juce::dontSendNotification);
    right.setColour(juce::Label::textColourId, juce::Colour(87, 111, 114));
    right.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&right);
    order.setFont(juce::Font(18.0f));
    order.setText("Filter Order", juce::dontSendNotification);
    order.setColour(juce::Label::textColourId, juce::Colour(87, 111, 114));
    order.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&order);
    // slider initialization 
    l_bound_dial.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    l_bound_dial.setRange(20.0f, 20000.0f);
    l_bound_dial.setValue(200.0f);
    l_bound_dial.setTextValueSuffix(" Hz");
    l_bound_dial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 70, 30);
    l_bound_dial.setPopupDisplayEnabled(false, false, this);
    l_bound_dial.setLookAndFeel(&look);
    addAndMakeVisible(&l_bound_dial);
    r_bound_dial.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    r_bound_dial.setRange(20.0f, 20000.0f);
    r_bound_dial.setValue(2000.0f);
    r_bound_dial.setTextValueSuffix(" Hz");
    r_bound_dial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 70, 30);
    r_bound_dial.setPopupDisplayEnabled(false, false, this);
    r_bound_dial.setLookAndFeel(&look);
    addAndMakeVisible(&r_bound_dial);
    funcOrder.setJustificationType(juce::Justification::centred);
    funcOrder.addItem("1", 1);
    funcOrder.addItem("5", 2);
    funcOrder.addItem("10", 3);
    funcOrder.addItem("15", 4);
    funcOrder.addItem("20", 5);
    funcOrder.setColour(juce::ComboBox::textColourId, juce::Colour(240, 235, 227));
    funcOrder.setColour(juce::ComboBox::backgroundColourId, juce::Colour(125, 157, 156));
    funcOrder.setColour(juce::ComboBox::arrowColourId, juce::Colour(240, 235, 227));
    funcOrder.setColour(juce::ComboBox::outlineColourId, juce::Colour(125, 157, 156));
    addAndMakeVisible(&funcOrder);
    // adding slider values to tree
    l_bound_value = new juce::AudioProcessorValueTreeState::SliderAttachment(processor.tree, "l_bound", l_bound_dial);
    r_bound_value = new juce::AudioProcessorValueTreeState::SliderAttachment(processor.tree, "r_bound", r_bound_dial);
    funcOrderValue = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "order", funcOrder);
}
FabulousFilterAudioProcessorEditor::~FabulousFilterAudioProcessorEditor()
{
}
void FabulousFilterAudioProcessorEditor::paint(juce::Graphics& g)
{
    // general window color
    g.fillAll(juce::Colour(240, 235, 227));
    g.setColour(juce::Colour(228, 220, 207));
    g.fillRoundedRectangle(juce::Rectangle<float>(25, 50, 200, 250), 25.0f);
}
void FabulousFilterAudioProcessorEditor::resized()
{
    // bounds initialization
    title.setBounds(25, 0, 200, 50);
    left.setBounds(31, 50, 100, 50);
    right.setBounds(115, 50, 100, 50);
    order.setBounds(25, 210, 200, 50);
    l_bound_dial.setBounds(20, 85, 125, 125);
    r_bound_dial.setBounds(105, 85, 125, 125);
    funcOrder.setBounds(75, 255, 100, 25);
}