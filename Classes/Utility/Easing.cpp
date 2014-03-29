#include "Easing.h"

//#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm> //req for max/min in Visual Studio...

Easing::EasingFunction Easing::easingFunctions[EASE_COUNT];
Easing::WrappingFunction Easing::wrappingFunctions[WRAP_COUNT];
Easing easingInstance; //do this so we can call the constructor to intialise the function pointer array based on enum values instead of abitary order as initialiser list

//-------CTOR-------
Easing::Easing()
{
    //populate our easing function point array
    easingFunctions[Linear] = &Easing::EaseLinear;
    easingFunctions[QuadIn] = &Easing::EaseQuadIn;
    easingFunctions[QuadOut] = &Easing::EaseQuadOut;
    easingFunctions[QuadInOut] = &Easing::EaseQuadInOut;
    easingFunctions[CubicIn] = &Easing::EaseCubicIn;
    easingFunctions[CubicOut] = &Easing::EaseCubicOut;
    easingFunctions[CubicInOut] = &Easing::EaseCubicInOut;
    easingFunctions[QuartIn] = &Easing::EaseQuartIn;
    easingFunctions[QuartOut] = &Easing::EaseQuartOut;
    easingFunctions[QuartInOut] = &Easing::EaseQuartOut;
    easingFunctions[QuintIn] = &Easing::EaseQuintIn;
    easingFunctions[QuintOut] = &Easing::EaseQuintOut;
    easingFunctions[QuintInOut] = &Easing::EaseQuintInOut;
    easingFunctions[SineIn] = &Easing::EaseSineIn;
    easingFunctions[SineOut] = &Easing::EaseSineOut;
    easingFunctions[SineInOut] = &Easing::EaseSineInOut;
    easingFunctions[ExpoIn] = &Easing::EaseExpoIn;
    easingFunctions[ExpoOut] = &Easing::EaseExpoOut;
    easingFunctions[ExpoInOut] = &Easing::EaseExpoInOut;
    easingFunctions[ElasticIn] = &Easing::EaseElasticIn;
    easingFunctions[ElasticOut] = &Easing::EaseElasticOut;
    easingFunctions[ElasticInOut] = &Easing::EaseElasticInOut;
    easingFunctions[CircularIn] = &Easing::EaseCircularIn;
    easingFunctions[CircularOut] = &Easing::EaseCircularOut;
    easingFunctions[CircularInOut] = &Easing::EaseCircularInOut;
    easingFunctions[BackIn] = &Easing::EaseBackIn;
    easingFunctions[BackOut] = &Easing::EaseBackOut;
    easingFunctions[BackInOut] = &Easing::EaseBackInOut;
    easingFunctions[BounceIn] = &Easing::EaseBounceIn;
    easingFunctions[BounceOut] = &Easing::EaseBounceOut;
    easingFunctions[BounceInOut] = &Easing::EaseBounceInOut;
    
    //populate our wrapping function pointer array
    wrappingFunctions[Clamp] = &Easing::WrapClamp;
    wrappingFunctions[Loop] = &Easing::WrapLoop;
    wrappingFunctions[PingPong] = &Easing::WrapPingPong;
}

//------HELPER FUNCTIONS------
float Easing::Ease(float t, float b, float c, float d, Method method, WrapType wrapType /*=Clamp*/)
{
    t = Wrap(t, 0, d, wrapType);
    if(t == 0) return b;
    else if( t == d ) return c;
    else return (*easingFunctions[method])(t,b,c,d);
}
float Easing::Wrap(float v, float min, float max, WrapType type)
{
	return (*wrappingFunctions[type])( v, min, max );
}

//------wrappingFunctions------
float Easing::WrapClamp(float v, float vMin, float vMax)
{
    return std::min(vMax,std::max(v,vMin));
}
float Easing::WrapLoop(float v, float vMin, float vMax)
{
    return vMin + fmod(v-vMin, fabsf(vMax-vMin));
}
float Easing::WrapPingPong(float v, float vMin, float vMax)
{
    v = WrapLoop(v, vMin, vMax) - vMin;
    if(v > (vMax-vMin)/2.0f)
        v = (vMax-vMin) - v;
    return vMin + v*2.0f;
}

//------easingFunctions------
//t = tick, b = start, c = end, d = duration
float Easing::EaseLinear(float t, float b, float c, float d)
{
    return (c-b)*(t/d) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseQuadIn(float t, float b, float c, float d)
{
    return (c-b) * (t/=d) * t + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseQuadOut(float t, float b, float c, float d)
{
    return -(c-b) *(t/=d)*(t-2) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseQuadInOut(float t, float b, float c, float d)
{
    if ((t/=d/2) < 1) return (c-b)/2*t*t + b;
    return -(c-b)/2 * ((--t)*(t-2) - 1) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseCubicIn(float t, float b, float c, float d)
{
    return (c-b)*(t/=d)*t*t + b;
}
//t = tick, b = start, c = end, d = duration
inline float Easing::EaseCubicOut(float t, float b, float c, float d)
{
    return (c-b)*((t=t/d-1)*t*t + 1) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseCubicInOut(float t, float b, float c, float d)
{
    if ((t/=d/2) < 1) return (c-b)/2*t*t*t + b;
    return (c-b)/2*((t-=2)*t*t + 2) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseQuartIn(float t, float b, float c, float d)
{
    return (c-b)*(t/=d)*t*t*t + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseQuartOut(float t, float b, float c, float d)
{
    return -(c-b) * ((t=t/d-1)*t*t*t - 1) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseQuartInOut(float t, float b, float c, float d)
{
    if ((t/=d/2) < 1) return (c-b)/2*t*t*t*t + b;
    return -(c-b)/2 * ((t-=2)*t*t*t - 2) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseQuintIn(float t, float b, float c, float d)
{
    return (c-b)*(t/=d)*t*t*t*t + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseQuintOut(float t, float b, float c, float d)
{
    return (c-b)*((t=t/d-1)*t*t*t*t + 1) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseQuintInOut(float t, float b, float c, float d)
{
    if ((t/=d/2) < 1) return (c-b)/2*t*t*t*t*t + b;
    return (c-b)/2*((t-=2)*t*t*t*t + 2) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseSineIn(float t, float b, float c, float d)
{
    return -(c-b) * cosf(t/d * (M_PI/2)) + (c-b) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseSineOut(float t, float b, float c, float d)
{
    return (c-b) * sinf(t/d * (M_PI/2)) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseSineInOut(float t, float b, float c, float d)
{
    return -(c-b)/2 * (cosf(M_PI*t/d) - 1) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseExpoIn(float t, float b, float c, float d)
{
    return (t==0) ? b : (c-b) * powf(2, 10 * (t/d - 1)) + b - (c-b) * 0.001f;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseExpoOut(float t, float b, float c, float d)
{
    return (t==d) ? b+(c-b) : (c-b) * 1.001f * (-powf(2, -10 * t/d) + 1) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseExpoInOut(float t, float b, float c, float d)
{
    if (t==0) return b;
    if (t==d) return b+(c-b);
    if ((t/=d/2) < 1) return (c-b)/2 * powf(2, 10 * (t - 1)) + b - (c-b) * 0.0005f;
    return (c-b)/2 * 1.0005f * (-powf(2, -10 * --t) + 2) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseCircularIn(float t, float b, float c, float d)
{
    return -(c-b) * (sqrtf(1 - (t/=d)*t) - 1) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseCircularOut(float t, float b, float c, float d)
{
    return (c-b) * sqrtf(1 - (t=t/d-1)*t) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseCircularInOut(float t, float b, float c, float d)
{
    if ((t/=d/2) < 1) return -(c-b)/2 * (sqrtf(1 - t*t) - 1) + b;
    return (c-b)/2 * (sqrtf(1 - (t-=2)*t) + 1) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseElasticIn(float t, float b, float c, float d)
{
    if (t==0) return b;
    if ((t/=d)==1) return b+(c-b);
    float p =  d *.3f;
    float s = 0;
    float a = 0;
    if (a == 0.0f || a < fabsf(c-b)) {
        a = (c-b);
        s = p/4;
    } else {
        s = p/(2*M_PI) * asinf ((c-b)/a);
    }
    return -(a*powf(2,10*(t-=1)) * sinf( (t*d-s)*(2*M_PI)/p )) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseElasticOut(float t, float b, float c, float d)
{
    if (t==0) return b;
    if ((t/=d)==1) return b+(c-b);
    float p = d*.3f;
    float s = 0;
    float a = 0;
    if (a == 0.0f || a < fabsf(c-b)) {
        a = (c-b);
        s = p/4;
    } else {
        s = p/(2*M_PI) * asinf ((c-b)/a);
    }
    return (a*powf(2,-10*t) * sinf( (t*d-s)*(2*M_PI)/p ) + (c-b) + b);
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseElasticInOut(float t, float b, float c, float d)
{
    if (t==0) return b;
    if ((t/=d/2)==2) return b+(c-b);
    float p =  d*(.3f*1.5f);
    float s = 0;
    float a = 0;
    if (a == 0.0f || a < fabsf(c-b)) {
        a = (c-b);
        s = p/4;
    } else {
        s = p/(2*M_PI) * asinf ((c-b)/a);
    }
    if (t < 1) return -.5f*(a*powf(2,10*(t-=1)) * sinf( (t*d-s)*(2*M_PI)/p )) + b;
    return a*powf(2,-10*(t-=1)) * sinf( (t*d-s)*(2*M_PI)/p )*.5f + (c-b) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseBackIn(float t, float b, float c, float d)
{
    float s = 1.70158f;
    return (c-b)*(t/=d)*t*((s+1)*t - s) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseBackOut(float t, float b, float c, float d)
{
    float s = 1.70158f;
    return (c-b)*((t=t/d-1)*t*((s+1)*t + s) + 1) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseBackInOut(float t, float b, float c, float d)
{
    float s =  1.70158f;
    if ((t/=d/2) < 1) return (c-b)/2*(t*t*(((s*=(1.525f))+1)*t - s)) + b;
    return (c-b)/2*((t-=2)*t*(((s*=(1.525f))+1)*t + s) + 2) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseBounceIn(float t, float b, float c, float d)
{
    return (c-b) - EaseBounceOut (d-t, 0, (c-b), d) + b;
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseBounceOut(float t, float b, float c, float d)
{
    if ((t/=d) < (1/2.75f))
    {
        return (c-b)*(7.5625f*t*t) + b;
    }
    else if (t < (2/2.75f))
    {
        return (c-b)*(7.5625f*(t-=(1.5f/2.75f))*t + .75f) + b;
    }
    else if (t < (2.5f/2.75f))
    {
        return (c-b)*(7.5625f*(t-=(2.25f/2.75f))*t + .9375f) + b;
    }
    else
    {
        return (c-b)*(7.5625f*(t-=(2.625f/2.75f))*t + .984375f) + b;
    }
}
//t = tick, b = start, c = end, d = duration
float Easing::EaseBounceInOut(float t, float b, float c, float d)
{
    if (t < d/2) return EaseBounceIn (t*2, 0, (c-b), d) * .5f + b;
    else return EaseBounceOut (t*2-d, 0, (c-b), d) * .5f + c*.5f + b;
}
