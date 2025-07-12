//falta correrlo en un servidor http y que use mail
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Clima {
    int temperatura;
    int humedad;
    string Fecha;
};

class MSForecastMock {
private:
    int temperatura;
    int humedad;

public:
    MSForecastMock() : temperatura(25), humedad(50) {}

    void Up_Temp(int x) { temperatura += x; }
    void Down_Temp(int x) { temperatura -= x; }
    void Up_Humity(int x) { humedad += x; }
    void Down_Humity(int x) { humedad -= x; }

    int Read_Temp() const { return temperatura; }
    int Read_Humity() const { return humedad; }
};

class ClimaController {
private:
    MSForecastMock forecast;
    vector<Clima> historial;

public:
    void ajustarTemperatura(int delta) {
        if (delta > 0) forecast.Up_Temp(delta);
        else forecast.Down_Temp(-delta);

        registrar();
    }

    void ajustarHumedad(int delta) {
        if (delta > 0) forecast.Up_Humity(delta);
        else forecast.Down_Humity(-delta);

        registrar();
    }

    void registrar() {
        Clima c;
        string fecha = "14/7/2025"; //es un ejemplo por ahora
        
        c.Fecha = fecha;
        c.temperatura = forecast.Read_Temp();
        c.humedad = forecast.Read_Humity();
        historial.push_back(c);

        guardarRegistroEnArchivo(c);
    }

    void guardarRegistroEnArchivo(const Clima& c) {
        ofstream archivo("Registro.txt", ios::app);
        if (archivo.is_open()) {
            archivo << "Fecha: " << c.Fecha 
                    << ", Temp: " << c.temperatura 
                    << ", Hum: " << c.humedad << endl;
            archivo.close();
        } else {
            cerr << "Error al abrir historial.txt" << endl;
        }
    }

    void mostrarHistorial() {
        for (int i = 0; i < historial.size(); i++) {
            cout << "Temp: " << historial[i].temperatura
                 << ", Hum: " << historial[i].humedad
                 << ", Fecha: " << historial[i].Fecha << endl;
        }
    }
};

int main() {
    ClimaController app;

    app.ajustarTemperatura(3);
    app.ajustarHumedad(-5);
    app.ajustarTemperatura(-2);

    app.mostrarHistorial();

    return 0;
}
