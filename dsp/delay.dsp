import("stdfaust.lib");

maxDelay = 1.5 * ma.SR; // 1.5s max delay time
interpTime = 42 * ma.SR / 1000; // 1ms interpolation time

p_drive = vslider("drive[unit:dB][style:knob]", 0.0, -24.0, 12.0, 0.1) : ba.db2linear : si.smoo;
p_volume = vslider("volume[unit:dB][style:knob]", 0.0, -24.0, 12.0, 0.1) : ba.db2linear : si.smoo;

p_dryWet_L = vslider("dryWet_L[unit:%][style:knob]", 0, 0, 100, 0) / 100 : si.smoo;
p_dryWet_R = vslider("dryWet_R[unit:%][style:knob]", 0, 0, 100, 0) / 100 : si.smoo;

p_cutoffLP_L = vslider("cutoffLP_L[unit:Hz][style:knob][scale:log]", 20000, 20, 20000, 0.1) : /(20000.0) : si.smoo;
p_cutoffHP_L = vslider("cutoffHP_L[unit:Hz][style:knob][scale:log]", 20, 20, 20000, 0.1) : /(20000) : si.smoo;
p_cutoffLP_R = vslider("cutoffLP_R[unit:Hz][style:knob][scale:log]", 20000, 20, 20000, 0.1) /(20000) : si.smoo;
p_cutoffHP_R = vslider("cutoffHP_R[unit:Hz][style:knob][scale:log]", 20, 20, 20000, 0.1) : /(20000) : si.smoo;

p_feedback_L = vslider("feedback_L[unit:%][style:knob]", 0.0, 0.0, 100.0, 0.1) / 100.0 : si.smoo;
p_feedback_R = vslider("feedback_R[unit:%][style:knob]", 0.0, 0.0, 100.0, 0.1) / 100.0 : si.smoo;

p_delayTime_L = vslider("delayTime_L[unit:ms][style:knob][scale:log]", 0.0, 0.0, 1500.0, 0.01) * ma.SR / 1000.0 : si.smoo;
p_delayTime_R = vslider("delayTime_R[unit:ms][style:knob][scale:log]", 0.0, 0.0, 1500.0, 0.01) * ma.SR / 1000.0 : si.smoo;

p_width = vslider("stereoWidth[unit:%][style:knob]", 100, 0, 100, 1) / 100;

// Left channel
voice_L = _ <: delayLoop_L * p_dryWet_L, *(1 - p_dryWet_L) :> *(p_volume);
delayLoop_L = *(p_drive) : aa.tanh1 : /(p_drive) : (+ : delay_L) ~ (*(p_feedback_L) : feedbackChain_L);
feedbackChain_L = ve.sallenKeyOnePoleLPF(p_cutoffLP_L) : ve.sallenKeyOnePoleHPF(p_cutoffHP_L);
delay_L = de.sdelay(maxDelay, interpTime, p_delayTime_L);

// Right channel
voice_R = _ <: delayLoop_R * p_dryWet_R, *(1 - p_dryWet_R) :> *(p_volume);
delayLoop_R = *(p_drive) : aa.tanh1 : /(p_drive) : (+ : delay_R) ~ (*(p_feedback_R) : feedbackChain_R);
feedbackChain_R = ve.sallenKeyOnePoleLPF(p_cutoffLP_R) : ve.sallenKeyOnePoleHPF(p_cutoffHP_R);
delay_R = de.sdelay(maxDelay, interpTime, p_delayTime_R);

// DC blocking and stereo width
DCBlock_L = fi.dcblockerat(20);
DCBlock_R = fi.dcblockerat(20);
stereoChain = _, _ : *(p_width), *(p_width) : _, _;
monoChain = _, _ :> /(2.0) : *(1 - p_width) <: _, _;
DCBlockChain = voice_L, voice_R : DCBlock_L, DCBlock_R;

process = _, _ : DCBlockChain <: stereoChain, monoChain :> _, _;
