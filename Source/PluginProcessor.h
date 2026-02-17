/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class SimpleEQAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SimpleEQAudioProcessor();
    ~SimpleEQAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    /*
     * APVTS expects a list of all parameters to be provided when it is created
     * This function will provide a list of parameters in the form of a APVTS ParameterLayout
     * Made static as it does not use any member variables
     */
    /*
     * Static Member Functions have the following properties:
     * They can be called without creating an object
     * Only has access to static data members or other static functions
     */
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    // Create object which will sync parameters with the GUI elements used to control the Audio DSP
    juce::AudioProcessorValueTreeState apvts{ *this, nullptr, "Parameters", createParameterLayout() };

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleEQAudioProcessor)
};
