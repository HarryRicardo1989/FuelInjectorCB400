#include "math.h"

#define BICO 40  // Definindo a taxa de fluxo do bico injetor em libras por hora
#define CILINDER_VOLUME 224  // Definindo o volume do cilindro em centímetros cúbicos

class Injector {
private:
    double temperature;  // Temperatura do ar em graus Celsius
    double pressure_abs;  // Pressão absoluta do ar em mmHg
    double pressure_fuel;  // Pressão de combustível em bar

public:
    Injector(double temp, double p_abs, double p_fuel) {
        temperature = temp;
        pressure_abs = p_abs;
        pressure_fuel = p_fuel;
    }

    double get_injection_time() {
        // Cálculo do tempo de injeção em milissegundos (ms)
        double density_fuel = 0.75;  // Densidade do combustível em gramas por mililitro
        double pressure_diff = pressure_fuel - 3.0;  // Diferença de pressão entre o combustível e o ar (em bar)
        double flow_rate = BICO * pressure_diff / 3.0;  // Taxa de fluxo do bico injetor em gramas por segundo
        double air_mass = (pressure_abs * 1.333) * (CILINDER_VOLUME / 1000.0) * (1.0 / (0.0821 * (temperature + 273.15)));  // Massa de ar em gramas
        double fuel_mass = air_mass * 0.065;  // Massa de combustível em gramas (supondo uma proporção ar/combustível de 14,7:1)
        double injection_time = 1000.0 * fuel_mass / (flow_rate * density_fuel);  // Tempo de injeção em milissegundos (ms)
        return injection_time;
    }
};
