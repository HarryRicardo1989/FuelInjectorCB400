#include <math.h>

#define bico 40
#define cilinder_volume 224

#define THERMISTOR_RESISTOR 4700.0 // valor do resistor em ohms
#define THERMISTOR_A 0.000903621 // constante A do termistor
#define THERMISTOR_B 0.000247207 // constante B do termistor
#define THERMISTOR_C 9.47828e-08 // constante C do termistor
#define THERMISTOR_REF_RESISTANCE 10000.0 // resistência de referência em ohms


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
  double read_fuel_pressure(double voltage) {
    double r1 = 2200; // valor de R1 em ohms
    double r2 = 4700; // valor de R2 em ohms
  // Calcular a tensão no sensor considerando o divisor de tensão r1-r2
    double sensor_voltage = voltage * (r1 + r2) / r2;

  // Calcular a pressão de combustível com base na curva característica do sensor
    double pressure = (sensor_voltage - 0.5) / 4.0 * 10.0;

  // Retornar o valor em bar
  return pressure;
}
double get_temperature(double voltage) {
  double resistance = THERMISTOR_RESISTOR * (5.0 / voltage - 1.0);
  double ln_resistance = log(resistance);
  double inv_temperature = THERMISTOR_A + THERMISTOR_B * ln_resistance 
    + THERMISTOR_C * pow(ln_resistance, 3);
  double temperature = 1.0 / inv_temperature - 273.15; // converter para Celsius
  return temperature;
}

};
