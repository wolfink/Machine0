#pragma once

class Oscillators
{
  double _osc1_freq = 0.0;
  double _osc2_freq = 0.0;
  double _osc3_freq = 0.0;
  double _osc4_freq = 0.0;
  double _osc1_fm2 = 0.0;
  double _osc1_fm3 = 0.0;
  double _osc1_fm4 = 0.0;
  double _osc2_fm3 = 0.0;
  double _osc2_fm4 = 0.0;
  double _osc3_fm4 = 0.0;
  double _osc1_gain = 1.0;
  double _osc2_gain = 0.0;
  double _osc3_gain = 0.0;
  double _osc4_gain = 0.0;

public:
  void Prepare(int note);
  double OutputNext(double sr, double& a1, double& a2, double& a3, double& a4);
private:
  double Get_osc_to_freq(int note, int index);
};
