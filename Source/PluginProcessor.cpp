#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <cmath>

FabulousFilterAudioProcessor::FabulousFilterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ), tree(*this, nullptr),
    lp1(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    lp2(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    lp3(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    lp4(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    lp5(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    lp6(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    lp7(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    lp8(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    lp9(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    lp10(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    lp11(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    lp12(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    lp13(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    lp14(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    lp15(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    lp16(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    lp17(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    lp18(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    lp19(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    lp20(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp1(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp2(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp3(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp4(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp5(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp6(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp7(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp8(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp9(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp10(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp11(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp12(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp13(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp14(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp15(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp16(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp17(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp18(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp19(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f)),
    hp20(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100, 20000.0f))
#endif
{
    // dials and combobox ranges
    juce::NormalisableRange<float> l_bound_range(20.0f, 20000.0f, 1.0f, 0.5f);
    juce::NormalisableRange<float> r_bound_range(20.0f, 20000.0f, 1.0f, 0.5f);
    juce::NormalisableRange<float> funcOrderRange(0, 4);
    // tree initialization from dials and combobox
    tree.createAndAddParameter("l_bound", "L Bound", "l_bound", l_bound_range, 250.0f, nullptr, nullptr);
    tree.createAndAddParameter("r_bound", "R Bound", "r_bound", r_bound_range, 2000.0f, nullptr, nullptr);
    tree.createAndAddParameter("order", "Order", "order", funcOrderRange, 4, nullptr, nullptr);
}
FabulousFilterAudioProcessor::~FabulousFilterAudioProcessor()
{
}
const juce::String FabulousFilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}
bool FabulousFilterAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}
bool FabulousFilterAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}
bool FabulousFilterAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}
double FabulousFilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}
int FabulousFilterAudioProcessor::getNumPrograms()
{
    return 1;
}
int FabulousFilterAudioProcessor::getCurrentProgram()
{
    return 0;
}
void FabulousFilterAudioProcessor::setCurrentProgram(int index)
{
}
const juce::String FabulousFilterAudioProcessor::getProgramName(int index)
{
    return {};
}
void FabulousFilterAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}
void FabulousFilterAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;
    // spec process block initialization
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    int order_val = *tree.getRawParameterValue("order");
    // spec prepare
    if (order_val >= 0) {
        lp1.prepare(spec);
        hp1.prepare(spec);
    }
    if (order_val >= 1) {
        lp2.prepare(spec);
        lp3.prepare(spec);
        lp4.prepare(spec);
        lp5.prepare(spec);

        hp2.prepare(spec);
        hp3.prepare(spec);
        hp4.prepare(spec);
        hp5.prepare(spec);
    }
    if (order_val >= 2) {
        lp6.prepare(spec);
        lp7.prepare(spec);
        lp8.prepare(spec);
        lp9.prepare(spec);
        lp10.prepare(spec);

        hp6.prepare(spec);
        hp7.prepare(spec);
        hp8.prepare(spec);
        hp9.prepare(spec);
        hp10.prepare(spec);
    }
    if (order_val >= 3) {
        lp11.prepare(spec);
        lp12.prepare(spec);
        lp13.prepare(spec);
        lp14.prepare(spec);
        lp15.prepare(spec);

        hp11.prepare(spec);
        hp12.prepare(spec);
        hp13.prepare(spec);
        hp14.prepare(spec);
        hp15.prepare(spec);
    }
    if (order_val >= 4) {
        lp16.prepare(spec);
        lp17.prepare(spec);
        lp18.prepare(spec);
        lp19.prepare(spec);
        lp20.prepare(spec);

        hp16.prepare(spec);
        hp17.prepare(spec);
        hp18.prepare(spec);
        hp19.prepare(spec);
        hp20.prepare(spec);
    }
    updateFilter();
    if (order_val >= 0) {
        lp1.reset();

        hp1.reset();
    }
    if (order_val >= 1) {
        lp2.reset();
        lp3.reset();
        lp4.reset();
        lp5.reset();

        hp2.reset();
        hp3.reset();
        hp4.reset();
        hp5.reset();
    }
    if (order_val >= 2) {
        lp6.reset();
        lp7.reset();
        lp8.reset();
        lp9.reset();
        lp10.reset();

        hp6.reset();
        hp7.reset();
        hp8.reset();
        hp9.reset();
        hp10.reset();
    }
    if (order_val >= 3) {
        lp11.reset();
        lp12.reset();
        lp13.reset();
        lp14.reset();
        lp15.reset();

        hp11.reset();
        hp12.reset();
        hp13.reset();
        hp14.reset();
        hp15.reset();
    }
    if (order_val >= 4) {
        lp16.reset();
        lp17.reset();
        lp18.reset();
        lp19.reset();
        lp20.reset();

        hp16.reset();
        hp17.reset();
        hp18.reset();
        hp19.reset();
        hp20.reset();
    }
}
void FabulousFilterAudioProcessor::releaseResources()
{
}
#ifndef JucePlugin_PreferredChannelConfigurations
bool FabulousFilterAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    return true;
#endif
}
#endif
void FabulousFilterAudioProcessor::updateFilter() {
    // getting values from dials and combobox
    float l_bound = *tree.getRawParameterValue("l_bound");
    float r_bound = *tree.getRawParameterValue("r_bound");
    int order_val = *tree.getRawParameterValue("order");
    // min max exception catch
    int lp_freq = std::max(l_bound, r_bound);
    int hp_freq = std::min(l_bound, r_bound);
    // bound correction
    if (lp_freq > 20000.0) {
        lp_freq = 20000.0;
    }
    if (hp_freq < 20.0) {
        hp_freq = 20.0;
    }
    // coefficient array initialization for nth order filters
    if (order_val == 0) {
        lp_array = juce::dsp::FilterDesign<float>::designIIRLowpassHighOrderButterworthMethod(lp_freq, lastSampleRate, 2);

        hp_array = juce::dsp::FilterDesign<float>::designIIRHighpassHighOrderButterworthMethod(hp_freq, lastSampleRate, 2);
    }
    else {
        lp_array = juce::dsp::FilterDesign<float>::designIIRLowpassHighOrderButterworthMethod(lp_freq, lastSampleRate, (order_val * 10));

        hp_array = juce::dsp::FilterDesign<float>::designIIRHighpassHighOrderButterworthMethod(hp_freq, lastSampleRate, (order_val * 10));
    }
    // filter update with correct order coefficients
    if (order_val >= 0) {
        *lp1.state = *lp_array.getObjectPointer(0);

        *hp1.state = *hp_array.getObjectPointer(0);
    }
    if (order_val >= 1) {
        *lp2.state = *lp_array.getObjectPointer(1);
        *lp3.state = *lp_array.getObjectPointer(2);
        *lp4.state = *lp_array.getObjectPointer(3);
        *lp5.state = *lp_array.getObjectPointer(4);

        *hp2.state = *hp_array.getObjectPointer(1);
        *hp3.state = *hp_array.getObjectPointer(2);
        *hp4.state = *hp_array.getObjectPointer(3);
        *hp5.state = *hp_array.getObjectPointer(4);
    }
    if (order_val >= 2) {
        *lp6.state = *lp_array.getObjectPointer(5);
        *lp7.state = *lp_array.getObjectPointer(6);
        *lp8.state = *lp_array.getObjectPointer(7);
        *lp9.state = *lp_array.getObjectPointer(8);
        *lp10.state = *lp_array.getObjectPointer(9);

        *hp6.state = *hp_array.getObjectPointer(5);
        *hp7.state = *hp_array.getObjectPointer(6);
        *hp8.state = *hp_array.getObjectPointer(7);
        *hp9.state = *hp_array.getObjectPointer(8);
        *hp10.state = *hp_array.getObjectPointer(9);
    }
    if (order_val >= 3) {
        *lp11.state = *lp_array.getObjectPointer(10);
        *lp12.state = *lp_array.getObjectPointer(11);
        *lp13.state = *lp_array.getObjectPointer(12);
        *lp14.state = *lp_array.getObjectPointer(13);
        *lp15.state = *lp_array.getObjectPointer(14);

        *hp11.state = *hp_array.getObjectPointer(10);
        *hp12.state = *hp_array.getObjectPointer(11);
        *hp13.state = *hp_array.getObjectPointer(12);
        *hp14.state = *hp_array.getObjectPointer(13);
        *hp15.state = *hp_array.getObjectPointer(14);
    }
    if (order_val >= 4) {
        *lp16.state = *lp_array.getObjectPointer(15);
        *lp17.state = *lp_array.getObjectPointer(16);
        *lp18.state = *lp_array.getObjectPointer(17);
        *lp19.state = *lp_array.getObjectPointer(18);
        *lp20.state = *lp_array.getObjectPointer(19);

        *hp16.state = *hp_array.getObjectPointer(15);
        *hp17.state = *hp_array.getObjectPointer(16);
        *hp18.state = *hp_array.getObjectPointer(17);
        *hp19.state = *hp_array.getObjectPointer(18);
        *hp20.state = *hp_array.getObjectPointer(19);
    }
}

void FabulousFilterAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // initialization
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    int order_val = *tree.getRawParameterValue("order");
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
    // filter processing
    juce::dsp::AudioBlock<float> block(buffer);
    updateFilter();
    if (order_val >= 0) {
        lp1.process(juce::dsp::ProcessContextReplacing<float>(block));

        hp1.process(juce::dsp::ProcessContextReplacing<float>(block));
    }
    if (order_val >= 1) {
        lp2.process(juce::dsp::ProcessContextReplacing<float>(block));
        lp3.process(juce::dsp::ProcessContextReplacing<float>(block));
        lp4.process(juce::dsp::ProcessContextReplacing<float>(block));
        lp5.process(juce::dsp::ProcessContextReplacing<float>(block));

        hp2.process(juce::dsp::ProcessContextReplacing<float>(block));
        hp3.process(juce::dsp::ProcessContextReplacing<float>(block));
        hp4.process(juce::dsp::ProcessContextReplacing<float>(block));
        hp5.process(juce::dsp::ProcessContextReplacing<float>(block));
    }
    if (order_val >= 2) {
        lp6.process(juce::dsp::ProcessContextReplacing<float>(block));
        lp7.process(juce::dsp::ProcessContextReplacing<float>(block));
        lp8.process(juce::dsp::ProcessContextReplacing<float>(block));
        lp9.process(juce::dsp::ProcessContextReplacing<float>(block));
        lp10.process(juce::dsp::ProcessContextReplacing<float>(block));

        hp6.process(juce::dsp::ProcessContextReplacing<float>(block));
        hp7.process(juce::dsp::ProcessContextReplacing<float>(block));
        hp8.process(juce::dsp::ProcessContextReplacing<float>(block));
        hp9.process(juce::dsp::ProcessContextReplacing<float>(block));
        hp10.process(juce::dsp::ProcessContextReplacing<float>(block));
    }
    if (order_val >= 3) {
        lp11.process(juce::dsp::ProcessContextReplacing<float>(block));
        lp12.process(juce::dsp::ProcessContextReplacing<float>(block));
        lp13.process(juce::dsp::ProcessContextReplacing<float>(block));
        lp14.process(juce::dsp::ProcessContextReplacing<float>(block));
        lp15.process(juce::dsp::ProcessContextReplacing<float>(block));

        hp11.process(juce::dsp::ProcessContextReplacing<float>(block));
        hp12.process(juce::dsp::ProcessContextReplacing<float>(block));
        hp13.process(juce::dsp::ProcessContextReplacing<float>(block));
        hp14.process(juce::dsp::ProcessContextReplacing<float>(block));
        hp15.process(juce::dsp::ProcessContextReplacing<float>(block));
    }
    if (order_val >= 4) {
        lp16.process(juce::dsp::ProcessContextReplacing<float>(block));
        lp17.process(juce::dsp::ProcessContextReplacing<float>(block));
        lp18.process(juce::dsp::ProcessContextReplacing<float>(block));
        lp19.process(juce::dsp::ProcessContextReplacing<float>(block));
        lp20.process(juce::dsp::ProcessContextReplacing<float>(block));

        hp16.process(juce::dsp::ProcessContextReplacing<float>(block));
        hp17.process(juce::dsp::ProcessContextReplacing<float>(block));
        hp18.process(juce::dsp::ProcessContextReplacing<float>(block));
        hp19.process(juce::dsp::ProcessContextReplacing<float>(block));
        hp20.process(juce::dsp::ProcessContextReplacing<float>(block));
    }
}
bool FabulousFilterAudioProcessor::hasEditor() const
{
    return true;
}
juce::AudioProcessorEditor* FabulousFilterAudioProcessor::createEditor()
{
    return new FabulousFilterAudioProcessorEditor(*this);
}
void FabulousFilterAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
}
void FabulousFilterAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
}
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FabulousFilterAudioProcessor();
}