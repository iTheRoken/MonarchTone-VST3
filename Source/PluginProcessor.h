#pragma once
#include <JuceHeader.h>
#include "VoiceDSP.h"
class MonarchToneAudioProcessor final : public juce::AudioProcessor {
public:
 MonarchToneAudioProcessor();
 void prepareToPlay(double,int) override;
 void releaseResources() override {}
 bool isBusesLayoutSupported(const BusesLayout&) const override;
 void processBlock(juce::AudioBuffer<float>&,juce::MidiBuffer&) override;
 juce::AudioProcessorEditor* createEditor() override;
 bool hasEditor() const override{return true;}
 const juce::String getName() const override{return JucePlugin_Name;}
 bool acceptsMidi() const override{return false;}
 bool producesMidi() const override{return false;}
 bool isMidiEffect() const override{return false;}
 double getTailLengthSeconds() const override{return 1.4;}
 int getNumPrograms() override{return 1;}
 int getCurrentProgram() override{return 0;}
 void setCurrentProgram(int) override{}
 const juce::String getProgramName(int) override{return {};}
 void changeProgramName(int,const juce::String&) override{}
 void getStateInformation(juce::MemoryBlock&) override;
 void setStateInformation(const void*,int) override;
 static juce::AudioProcessorValueTreeState::ParameterLayout makeParams();
 juce::AudioProcessorValueTreeState state;
private:
 std::array<monarch::Channel,2> channels;
 JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonarchToneAudioProcessor)
};
