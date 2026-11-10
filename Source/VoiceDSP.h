#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <vector>

namespace monarch {
inline float clamp(float v,float a,float b){return std::max(a,std::min(b,v));}
struct Controls {
 int style=1; // 0 Warm, 1 Pixel, 2 Ethereal
 float age=.24f, body=.48f, texture=.08f, space=.18f, echo=.05f, wobble=.05f, mix=1.f, output=1.f;
};
class Channel {
public:
 void prepare(double sampleRate){sr=std::max(8000.0,sampleRate); const auto n=static_cast<size_t>(sr*1.4)+2; delay.assign(n,0); roomA.assign(static_cast<size_t>(sr*.031)+2,0);roomB.assign(static_cast<size_t>(sr*.043)+2,0);roomC.assign(static_cast<size_t>(sr*.059)+2,0);reset();}
 void reset(){hpIn=hpOut=low=bright=hold=phase=last=0; delayIdx=aIdx=bIdx=cIdx=0; std::fill(delay.begin(),delay.end(),0);std::fill(roomA.begin(),roomA.end(),0);std::fill(roomB.begin(),roomB.end(),0);std::fill(roomC.begin(),roomC.end(),0);}
 float process(float raw, const Controls& ctrl){
  const auto dry=clamp(raw,-4.f,4.f);
  float age=clamp(ctrl.age,0.f,1.f), body=clamp(ctrl.body,0.f,1.f), texture=clamp(ctrl.texture,0.f,1.f);
  float space=clamp(ctrl.space,0.f,1.f), echo=clamp(ctrl.echo,0.f,1.f), wobble=clamp(ctrl.wobble,0.f,1.f);
  if(ctrl.style==1){age=clamp(age+.13f,0.f,1.f);body=clamp(body+.13f,0.f,1.f);}
  if(ctrl.style==2){space=clamp(space+.28f,0.f,1.f);echo=clamp(echo+.13f,0.f,1.f);}
  // Remove subsonic rumble without removing fundamental voice pitch.
  const float hpCut=55.f+65.f*age;
  const float alpha=std::exp(-6.2831853f*hpCut/static_cast<float>(sr));
  hpOut=alpha*(hpOut+dry-hpIn);hpIn=dry;
  float v=hpOut;
  // Gently darken the high frequencies. The sample's dialogue stays understandable.
  const float lpHz=std::min(static_cast<float>(sr*.43), 11000.f-6300.f*age-900.f*body);
  const float coeff=1.f-std::exp(-6.2831853f*lpHz/static_cast<float>(sr));
  low += coeff*(v-low);
  v=low;
  // Broad low-mid body with soft saturation. This does not change the identity or pitch of a voice.
  bright += (1.f-std::exp(-6.2831853f*260.f/static_cast<float>(sr)))*(v-bright);
  v+=body*.27f*bright;
  const float drive=1.0f+texture*4.6f;
  v=std::tanh(v*drive)/std::tanh(drive);
  // Subtle vintage digital texture: fractional sample hold blended with original.
  const float virtualHz=static_cast<float>(sr)-(static_cast<float>(sr)-7600.f)*age;
  phase+=virtualHz/static_cast<float>(sr);
  if(phase>=1.f){phase-=1.f;hold=v;}
  v=v*(1.f-.48f*age)+hold*(.48f*age);
  // Gentle tape-like pitch flutter approximated by blending a delayed sample.
  // A real pitch-shifter would be needed for substantial changes to the voice.
  const float mod=0.5f+0.5f*std::sin(6.2831853f*flutterPhase);
  flutterPhase+=static_cast<float>((.8f+2.2f*wobble)/sr);
  if(flutterPhase>=1.f)flutterPhase-=1.f;
  v=v*(1.f-.095f*wobble)+last*(.095f*wobble*mod);
  last=v;
  // Diffuse ambience. Three short feedback delays avoid a metallic single echo.
  const float r1=processRoom(roomA,aIdx,v,.58f);
  const float r2=processRoom(roomB,bIdx,v+r1*.17f,.60f);
  const float r3=processRoom(roomC,cIdx,v+r2*.17f,.57f);
  const float ambience=(r1+r2+r3)*.28f;
  const float delaySamples=static_cast<float>(sr*.245);
  const auto lag=static_cast<size_t>(delaySamples);
  size_t read=(delayIdx+delay.size()-(lag%delay.size()))%delay.size();
  const float tap=delay[read];
  delay[delayIdx]=clamp(v+tap*(.12f+.22f*echo),-2.f,2.f);
  delayIdx=(delayIdx+1)%delay.size();
  const float wet=v+ambience*.7f*space+tap*.30f*echo;
  const float mix=clamp(ctrl.mix,0.f,1.f);
  return clamp((dry*(1.f-mix)+wet*mix)*ctrl.output,-1.5f,1.5f);
 }
private:
 static float processRoom(std::vector<float>& buf,size_t& pos,float x,float feedback){float tap=buf[pos];buf[pos]=clamp(x+tap*feedback,-3.f,3.f);pos=(pos+1)%buf.size();return tap;}
 double sr=48000;float hpIn=0,hpOut=0,low=0,bright=0,hold=0,phase=0,last=0,flutterPhase=0;
 size_t delayIdx=0,aIdx=0,bIdx=0,cIdx=0;
 std::vector<float> delay,roomA,roomB,roomC;
};
}
