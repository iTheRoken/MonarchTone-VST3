#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
class MonarchToneAudioProcessorEditor final: public juce::AudioProcessorEditor {
public:
 explicit MonarchToneAudioProcessorEditor(MonarchToneAudioProcessor&);
 void paint(juce::Graphics&) override;
 void resized() override;
private:
 using SliderAttachment=juce::AudioProcessorValueTreeState::SliderAttachment;
 using ComboAttachment=juce::AudioProcessorValueTreeState::ComboBoxAttachment;
 struct Knob {juce::Slider slider;juce::Label label;std::unique_ptr<SliderAttachment> attachment;};
 MonarchToneAudioProcessor& processor;
 std::array<Knob,8> knobs;
 juce::ComboBox selector;
 std::unique_ptr<ComboAttachment> modeAttachment;
 JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonarchToneAudioProcessorEditor)
};
