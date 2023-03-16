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
double read_pressure(double voltage) {
    double r1 = 2200; // valor de R1 em ohms
    double r2 = 4700; // valor de R2 em ohms
    double inclinacao = 93.3;
    double vout = voltage * r2 / (r1 + r2);
    double pressao_absoluta = (vout / 1.0) * inclinacao / (3.3 / (r1 + r2)) + 13.3;
    return pressao_absoluta * 1000; // Converter kPa para Pa
}

};
