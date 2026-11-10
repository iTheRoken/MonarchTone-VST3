#include "../Source/VoiceDSP.h"
#include <cassert>
#include <cmath>
#include <iostream>
int main(){for(int style=0;style<3;++style){monarch::Controls c;c.style=style;monarch::Channel d;for(double sr:{22050.,44100.,48000.,96000.}){d.prepare(sr);double sum=0;for(int n=0;n<static_cast<int>(sr);++n){float x=.25f*std::sin(2.f*3.14159265358979f*180.f*n/static_cast<float>(sr));float z=d.process(x,c);assert(std::isfinite(z));assert(std::abs(z)<1.51f);sum+=z*z;}assert(sum>0.001);}}std::cout<<"DSP tests passed\n";}
