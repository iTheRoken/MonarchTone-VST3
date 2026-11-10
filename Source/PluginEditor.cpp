#include "PluginEditor.h"
MonarchToneAudioProcessorEditor::MonarchToneAudioProcessorEditor(MonarchToneAudioProcessor& p):AudioProcessorEditor(&p),processor(p){
 const char* ids[]={"age","body","texture","space","echo","wobble","mix","output"};
 const char* names[]={"DIGITAL AGE","BODY","TEXTURE","ROOM","ECHO","FLUTTER","DRY / WET","OUTPUT dB"};
 for(size_t i=0;i<knobs.size();++i){
  auto& k=knobs[i];
  k.slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
  k.slider.setTextBoxStyle(juce::Slider::TextBoxBelow,false,84,22);
  k.slider.setColour(juce::Slider::rotarySliderFillColourId,juce::Colour(0xffc1a1fa));
  k.slider.setColour(juce::Slider::rotarySliderOutlineColourId,juce::Colour(0xff40394d));
  k.slider.setColour(juce::Slider::textBoxTextColourId,juce::Colours::white);
  k.slider.setColour(juce::Slider::textBoxOutlineColourId,juce::Colours::transparentBlack);
  addAndMakeVisible(k.slider);
  k.label.setText(names[i],juce::dontSendNotification);
  k.label.setJustificationType(juce::Justification::centred);
  k.label.setColour(juce::Label::textColourId,juce::Colour(0xffc6b8d2));
  addAndMakeVisible(k.label);
  k.attachment=std::make_unique<SliderAttachment>(processor.state,ids[i],k.slider);
 }
 selector.addItem("Warm Narrator",1); selector.addItem("Pixel Dialogue",2);selector.addItem("Ethereal Room",3);
 selector.setColour(juce::ComboBox::backgroundColourId,juce::Colour(0xff292434));
 selector.setColour(juce::ComboBox::textColourId,juce::Colours::white);
 addAndMakeVisible(selector);
 modeAttachment=std::make_unique<ComboAttachment>(processor.state,"style",selector);
 setSize(720,420);
}
void MonarchToneAudioProcessorEditor::paint(juce::Graphics& g){
 g.fillAll(juce::Colour(0xff15131b));
 g.setColour(juce::Colour(0xff231f2c));g.fillRoundedRectangle(16.f,112.f,688.f,285.f,14.f);
 g.setColour(juce::Colours::white);
 g.setFont(juce::FontOptions(28.f,juce::Font::bold));g.drawText("MONARCH TONE",26,15,420,38,juce::Justification::centredLeft);
 g.setColour(juce::Colour(0xffc1a1fa));g.fillRoundedRectangle(26.f,72.f,665.f,2.f,1.f);
 g.setColour(juce::Colour(0xffaca1b6));g.setFont(juce::FontOptions(13.f));
 g.drawText("Soft digital dialogue & cinematic ambience",26,53,450,19,juce::Justification::centredLeft);
 g.drawText("VOICE STYLE",28,84,150,23,juce::Justification::centredLeft);
 g.drawText("Independent sound design tool",490,24,205,22,juce::Justification::centredRight);
}
void MonarchToneAudioProcessorEditor::resized(){
 selector.setBounds(172,82,225,27);
 for(size_t i=0;i<knobs.size();++i){
  const int col=static_cast<int>(i%4),row=static_cast<int>(i/4);
  const int x=32+col*170,y=129+row*130;
  auto& k=knobs[i]; k.label.setBounds(x,y,146,23);k.slider.setBounds(x+12,y+22,120,100);
 }
}
