import("stdfaust.lib");

maxDelay = 1.5 * ma.SR; // 1.5s max delay time
interpTime = 42 * ma.SR / 1000; // 1ms interpolation time

p_inGain = vslider("inputVolume[unit:dB][style:knob]", 0.0, -24.0, 12.0, 0.1) : ba.db2linear;
p_outVolume = vslider("outputVolume[unit:dB][style:knob]", 0.0, -24.0, 12.0, 0.1) : ba.db2linear;

p_dryWet_L = vslider("dryWet_L[unit:%][style:knob]", 0, 0, 100, 0) / 100 : si.smoo;
p_dryWet_R = vslider("dryWet_R[unit:%][style:knob]", 0, 0, 100, 0) / 100 : si.smoo;

p_fcLP_L = vslider("fcLP_L[unit:Hz][style:knob][scale:log]", 20000, 20, 20000, 0.1) / (ma.SR / 2) : si.smoo;
p_fcHP_L = vslider("fcHP_L[unit:Hz][style:knob][scale:log]", 20, 20, 20000, 0.1) / (ma.SR / 2) : si.smoo;
p_fcLP_R = vslider("fcLP_R[unit:Hz][style:knob][scale:log]", 20000, 20, 20000, 0.1) / (ma.SR / 2) : si.smoo;
p_fcHP_R = vslider("fcHP_R[unit:Hz][style:knob][scale:log]", 20, 20, 20000, 0.1) / (ma.SR / 2) : si.smoo;

p_feedback_L = vslider("feedback_L[unit:%][style:knob]", 0, 0, 100, 1) / 100 : si.smoo;
p_feedback_R = vslider("feedback_R[unit:%][style:knob]", 0, 0, 100, 1) / 100 : si.smoo;

p_deTime_L = vslider("delayTime_L[unit:ms][style:knob][scale:log]", 0.0, 0.0, 1500.0, 0.01) * ma.SR / 1000.0 : si.smoo;
p_deTime_R = vslider("delayTime_R[unit:ms][style:knob][scale:log]", 0.0, 0.0, 1500.0, 0.01) * ma.SR / 1000.0 : si.smoo;

p_width = vslider("stereoWidth[unit:%][style:knob]", 100, 0, 100, 1) / 100;

// Left channel
voice_L = _ : *(p_inGain) <: delayLoop_L * p_dryWet_L, *(1 - p_dryWet_L) :> *(p_outVolume);
delayLoop_L = (+ : delay_L) ~ (*(p_feedback_L) : feedbackChain_L);
feedbackChain_L = aa.tanh1 : ve.sallenKeyOnePoleLPF(p_fcLP_L) : ve.sallenKeyOnePoleHPF(p_fcHP_L);
delay_L = de.sdelay(maxDelay, interpTime, p_deTime_L);

// Right channel
voice_R = _ : *(p_inGain) <: delayLoop_R * p_dryWet_R, *(1 - p_dryWet_R) :> *(p_outVolume);
delayLoop_R = (+ : delay_R) ~ (*(p_feedback_R) : feedbackChain_R);
feedbackChain_R = aa.tanh1 : ve.sallenKeyOnePoleLPF(p_fcLP_R) : ve.sallenKeyOnePoleHPF(p_fcHP_R);
delay_R = de.sdelay(maxDelay, interpTime, p_deTime_R);

// DC blocking and stereo width
DCBlock_L = fi.dcblockerat(20);
DCBlock_R = fi.dcblockerat(20);
stereoChain = _, _ : *(p_width), *(p_width) : _, _;
monoChain = _, _ :> /(2.0) : *(1 - p_width) <: _, _;
DCBlockChain = voice_L, voice_R : DCBlock_L, DCBlock_R;

process = _, _ : DCBlockChain <: stereoChain, monoChain :> _, _;
