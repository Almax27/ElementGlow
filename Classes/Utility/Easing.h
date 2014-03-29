//Adapted from Robert Penner's Easing Functions: http://www.robertpenner.com/easing/

#ifndef __Easing_h__
#define __Easing_h__

class Easing
{
public:
    enum Method
    {
        Linear,
        QuadIn, QuadOut, QuadInOut,
        CubicIn, CubicOut, CubicInOut,
        QuartIn, QuartOut, QuartInOut,
        QuintIn, QuintOut, QuintInOut,
        SineIn, SineOut, SineInOut,
        ExpoIn, ExpoOut, ExpoInOut,
        ElasticIn, ElasticOut, ElasticInOut,
        CircularIn, CircularOut, CircularInOut,
        BackIn, BackOut, BackInOut,
        BounceIn, BounceOut, BounceInOut,
        EASE_COUNT
    };
    
    enum WrapType
    {
        Clamp,
        Loop,
        PingPong,
        WRAP_COUNT
    };
    
    //function pointer prototypes
    typedef float (*EasingFunction)(float, float, float, float);
    typedef float (*WrappingFunction)(float, float, float);
    
    //ctor
    Easing();
    
    //easing functions
    static float EaseLinear(float t, float b, float c, float d);
    static float EaseQuadIn(float t, float b, float c, float d);
    static float EaseQuadOut(float t, float b, float c, float d);
    static float EaseQuadInOut(float t, float b, float c, float d);
    static float EaseCubicIn(float t, float b, float c, float d);
    static float EaseCubicOut(float t, float b, float c, float d);
    static float EaseCubicInOut(float t, float b, float c, float d);
    static float EaseQuartIn(float t, float b, float c, float d);
    static float EaseQuartOut(float t, float b, float c, float d);
    static float EaseQuartInOut(float t, float b, float c, float d);
    static float EaseQuintIn(float t, float b, float c, float d);
    static float EaseQuintOut(float t, float b, float c, float d);
    static float EaseQuintInOut(float t, float b, float c, float d);
    static float EaseSineIn(float t, float b, float c, float d);
    static float EaseSineOut(float t, float b, float c, float d);
    static float EaseSineInOut(float t, float b, float c, float d);
    static float EaseExpoIn(float t, float b, float c, float d);
    static float EaseExpoOut(float t, float b, float c, float d);
    static float EaseExpoInOut(float t, float b, float c, float d);
    static float EaseCircularIn(float t, float b, float c, float d);
    static float EaseCircularOut(float t, float b, float c, float d);
    static float EaseCircularInOut(float t, float b, float c, float d);
    static float EaseElasticIn(float t, float b, float c, float d);
    static float EaseElasticOut(float t, float b, float c, float d);
    static float EaseElasticInOut(float t, float b, float c, float d);
    static float EaseBackIn(float t, float b, float c, float d);
    static float EaseBackOut(float t, float b, float c, float d);
    static float EaseBackInOut(float t, float b, float c, float d);
    static float EaseBounceOut(float t, float b, float c, float d);
    static float EaseBounceIn(float t, float b, float c, float d);
    static float EaseBounceInOut(float t, float b, float c, float d);
    
    //wrap functions
    static float WrapClamp(float v, float vMin, float vMax);
    static float WrapLoop(float v, float vMin, float vMax);
    static float WrapPingPong(float v, float vMin, float vMax);
    
    //helper function
    static float Ease(float t, float b, float c, float d, Method method, WrapType wrapType = Clamp);
    static float Wrap(float v, float min, float max, WrapType type);
private:
    static EasingFunction easingFunctions[EASE_COUNT];
    static WrappingFunction wrappingFunctions[WRAP_COUNT];
};

#endif //__Easing_h__
