#include "PluginProcessor.h"
#include "PluginEditor.h"
MonarchToneAudioProcessor::MonarchToneAudioProcessor()
: AudioProcessor(BusesProperties().withInput("Input",juce::AudioChannelSet::stereo(),true).withOutput("Output",juce::AudioChannelSet::stereo(),true)),state(*this,nullptr,"PARAMETERS",makeParams()){}
juce::AudioProcessorValueTreeState::ParameterLayout MonarchToneAudioProcessor::makeParams(){
 using APF=juce::AudioParameterFloat;
 std::vector<std::unique_ptr<juce::RangedAudioParameter>> p;
 p.push_back(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID{"style",1},"Voice Character",juce::StringArray{"Warm Narrator","Pixel Dialogue","Ethereal Room"},1));
 auto add=[&](const char* id,const char* name,float defaultValue){p.push_back(std::make_unique<APF>(juce::ParameterID{id,1},name,juce::NormalisableRange<float>(0.f,100.f,1.f),defaultValue));};
 add("age","Digital Age",24.f);add("body","Voice Body",48.f);add("texture","Texture",8.f);
 add("space","Room",18.f);add("echo","Echo",5.f);add("wobble","Flutter",5.f);add("mix","Dry Wet",100.f);
 p.push_back(std::make_unique<APF>(juce::ParameterID{"output",1},"Output dB",juce::NormalisableRange<float>(-18.f,12.f,.1f),0.f));
 return {p.begin(),p.end()};
}
void MonarchToneAudioProcessor::prepareToPlay(double sr,int){for(auto& c:channels)c.prepare(sr);}
bool MonarchToneAudioProcessor::isBusesLayoutSupported(const BusesLayout& b) const {return b.getMainInputChannelSet()==b.getMainOutputChannelSet()&&(b.getMainInputChannelSet()==juce::AudioChannelSet::mono()||b.getMainInputChannelSet()==juce::AudioChannelSet::stereo());}
void MonarchToneAudioProcessor::processBlock(juce::AudioBuffer<float>& b,juce::MidiBuffer&){
 juce::ScopedNoDenormals noDenormals;
 monarch::Controls s;
 s.style=static_cast<int>(state.getRawParameterValue("style")->load());
 s.age=state.getRawParameterValue("age")->load()*.01f;s.body=state.getRawParameterValue("body")->load()*.01f;
 s.texture=state.getRawParameterValue("texture")->load()*.01f;s.space=state.getRawParameterValue("space")->load()*.01f;
 s.echo=state.getRawParameterValue("echo")->load()*.01f;s.wobble=state.getRawParameterValue("wobble")->load()*.01f;
 s.mix=state.getRawParameterValue("mix")->load()*.01f;s.output=juce::Decibels::decibelsToGain(state.getRawParameterValue("output")->load());
 const int used=juce::jmin(2,b.getNumChannels());
 for(int ch=0;ch<used;++ch){auto* d=b.getWritePointer(ch);for(int i=0;i<b.getNumSamples();++i)d[i]=channels[static_cast<size_t>(ch)].process(d[i],s);}
 for(int ch=used;ch<b.getNumChannels();++ch)b.clear(ch,0,b.getNumSamples());
}
juce::AudioProcessorEditor* MonarchToneAudioProcessor::createEditor(){return new MonarchToneAudioProcessorEditor(*this);}
void MonarchToneAudioProcessor::getStateInformation(juce::MemoryBlock& dest){auto xml=state.copyState().createXml();copyXmlToBinary(*xml,dest);}
void MonarchToneAudioProcessor::setStateInformation(const void* data,int size){if(auto xml=getXmlFromBinary(data,size)){auto tree=juce::ValueTree::fromXml(*xml);if(tree.isValid())state.replaceState(tree);}}
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter(){return new MonarchToneAudioProcessor();}
