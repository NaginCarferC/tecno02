#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

using namespace std;

class AnalizadorOperacion {
private:
    double* numeros;
    char* operadores;
    int cantidadNumeros;
    int cantidadOperadores;

public:
    AnalizadorOperacion() {
        numeros = new double[6];
        operadores = new char[5];
        cantidadNumeros = 0;
        cantidadOperadores = 0;
    }

    ~AnalizadorOperacion() {
        delete[] numeros;
        delete[] operadores;
    }

    bool analizar(const string& expresion) {
        cantidadNumeros = 0;
        cantidadOperadores = 0;
        string limpia = "";
        for (char c : expresion) {
            if (!isspace(c)) {
                limpia += c;
            }
        }

        if (limpia.empty()) {
            return false;
        }

        size_t i = 0;
        while (i < limpia.length()) {
            if (i == 0 && limpia[i] == '-') {
                size_t start = i++;
                while (i < limpia.length() && (isdigit(limpia[i]) || limpia[i] == '.')) {
                    i++;
                }
                if (start + 1 == i) {
                    return false;
                }
                if (cantidadNumeros >= 6) {
                    return false;
                }
                numeros[cantidadNumeros++] = stod(limpia.substr(start, i - start));
                continue;
            }

            if (isdigit(limpia[i]) || limpia[i] == '.') {
                if (cantidadNumeros >= 6) {
                    return false;
                }
                size_t start = i;
                while (i < limpia.length() && (isdigit(limpia[i]) || limpia[i] == '.')) {
                    i++;
                }
                numeros[cantidadNumeros++] = stod(limpia.substr(start, i - start));
            } else if (limpia[i] == '+' || limpia[i] == '-' || limpia[i] == '*' || limpia[i] == '/') {
                if (cantidadOperadores >= 5) {
                    return false;
                }
                operadores[cantidadOperadores++] = limpia[i];
                i++;
            } else {
                return false;
            }
        }

        if (cantidadNumeros == 0 || cantidadNumeros != cantidadOperadores + 1) {
            return false;
        }

        return true;
    }

    double* getNumeros() const {
        return numeros;
    }

    char* getOperadores() const {
        return operadores;
    }

    int getCantidadNumeros() const {
        return cantidadNumeros;
    }

    int getCantidadOperadores() const {
        return cantidadOperadores;
    }
};

class AdministradorOperaciones {
public:
    double sumar(double a, double b) {
        return a + b;
    }

    double restar(double a, double b) {
        return a - b;
    }

    double multiplicar(double a, double b) {
        return a * b;
    }

    double dividir(double a, double b) {
        if (b == 0.0) {
            throw runtime_error("Division por cero");
        }
        return a / b;
    }

    double calcular(const double* nums, const char* ops, int cantNums, int cantOps) {
        if (cantNums <= 0) {
            return 0.0;
        }

        double* tempNums = new double[cantNums];
        char* tempOps = new char[cantOps];

        for (int i = 0; i < cantNums; ++i) {
            tempNums[i] = nums[i];
        }
        for (int i = 0; i < cantOps; ++i) {
            tempOps[i] = ops[i];
        }

        int n = cantNums;
        int o = cantOps;

        for (int i = 0; i < o; ) {
            if (tempOps[i] == '*' || tempOps[i] == '/') {
                double res = 0.0;
                if (tempOps[i] == '*') {
                    res = multiplicar(tempNums[i], tempNums[i + 1]);
                } else {
                    res = dividir(tempNums[i], tempNums[i + 1]);
                }
                tempNums[i] = res;
                for (int j = i + 1; j < n - 1; ++j) {
                    tempNums[j] = tempNums[j + 1];
                }
                for (int j = i; j < o - 1; ++j) {
                    tempOps[j] = tempOps[j + 1];
                }
                n--;
                o--;
            } else {
                i++;
            }
        }

        double resultado = tempNums[0];
        for (int i = 0; i < o; ++i) {
            if (tempOps[i] == '+') {
                resultado = sumar(resultado, tempNums[i + 1]);
            } else if (tempOps[i] == '-') {
                resultado = restar(resultado, tempNums[i + 1]);
            }
        }

        delete[] tempNums;
        delete[] tempOps;
        return resultado;
    }
};

class ProcesadorOperacion {
private:
    AnalizadorOperacion* analizador;
    AdministradorOperaciones* administrador;

public:
    ProcesadorOperacion() {
        analizador = new AnalizadorOperacion();
        administrador = new AdministradorOperaciones();
    }

    ~ProcesadorOperacion() {
        delete analizador;
        delete administrador;
    }

    void procesar(const string& expresion) {
        cout << "Operacion: " << expresion << endl;
        if (!analizador->analizar(expresion)) {
            cout << "Error: Expresion invalida o excede el maximo de 6 numeros." << endl;
            return;
        }

        try {
            double resultado = administrador->calcular(
                analizador->getNumeros(),
                analizador->getOperadores(),
                analizador->getCantidadNumeros(),
                analizador->getCantidadOperadores()
            );
            cout << "Resultado: " << resultado << endl;
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
};

int main() {
    ProcesadorOperacion procesador;

    procesador.procesar("10+37");
    procesador.procesar("45+14-42");
    procesador.procesar("1+2+3+4+5+6");

    cout << "\nIngrese una operacion: ";
    string entrada;
    if (getline(cin, entrada) && !entrada.empty()) {
        procesador.procesar(entrada);
    }

    return 0;
}
