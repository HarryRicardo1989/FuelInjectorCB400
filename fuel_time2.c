#include <math.h>

#define bico 40
#define cilinder_volume 224

class Injector {
public:
  double get_injection_time(double temp, double p_abs, double p_fuel) {
    double p_air = (p_abs - 0.98692) * 100000; // Convert pressure to Pa
    double n_air = p_air * cilinder_volume / (8.314 * (temp + 273.15)); // Calculate air mass
    double n_fuel = n_air / 14.7 * p_fuel; // Calculate fuel mass
    double t_inj = n_fuel * 3600 / (bico * 0.001); // Calculate injection time in ms

    return t_inj;
  }
};
