#include <iostream>

using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(int valor) {
        dato = valor;
        siguiente = nullptr;
        anterior = nullptr;
    }
};

class ListaDoblementeEnlazada {
private:
    Nodo* cabeza;
    Nodo* cola;

public:
    ListaDoblementeEnlazada() {
        cabeza = nullptr;
        cola = nullptr;
    }

    ~ListaDoblementeEnlazada() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* temp = actual->siguiente;
            delete actual;
            actual = temp;
        }
        cabeza = nullptr;
        cola = nullptr;
    }

    bool estaVacia() const {
        return cabeza == nullptr;
    }

    void insertarInicio(int valor) {
        Nodo* nuevo = new Nodo(valor);
        if (estaVacia()) {
            cabeza = nuevo;
            cola = nuevo;
        } else {
            nuevo->siguiente = cabeza;
            cabeza->anterior = nuevo;
            cabeza = nuevo;
        }
    }

    void insertarFinal(int valor) {
        Nodo* nuevo = new Nodo(valor);
        if (estaVacia()) {
            cabeza = nuevo;
            cola = nuevo;
        } else {
            cola->siguiente = nuevo;
            nuevo->anterior = cola;
            cola = nuevo;
        }
    }

    void eliminarInicio() {
        if (estaVacia()) {
            return;
        }
        Nodo* temp = cabeza;
        if (cabeza == cola) {
            cabeza = nullptr;
            cola = nullptr;
        } else {
            cabeza = cabeza->siguiente;
            cabeza->anterior = nullptr;
        }
        delete temp;
    }

    void eliminarFinal() {
        if (estaVacia()) {
            return;
        }
        Nodo* temp = cola;
        if (cabeza == cola) {
            cabeza = nullptr;
            cola = nullptr;
        } else {
            cola = cola->anterior;
            cola->siguiente = nullptr;
        }
        delete temp;
    }

    bool eliminarValor(int valor) {
        if (estaVacia()) {
            return false;
        }
        Nodo* actual = cabeza;
        while (actual != nullptr && actual->dato != valor) {
            actual = actual->siguiente;
        }
        if (actual == nullptr) {
            return false;
        }

        if (actual == cabeza) {
            eliminarInicio();
        } else if (actual == cola) {
            eliminarFinal();
        } else {
            actual->anterior->siguiente = actual->siguiente;
            actual->siguiente->anterior = actual->anterior;
            delete actual;
        }
        return true;
    }

    bool buscar(int valor) const {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato == valor) {
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    void mostrarHaciaAdelante() const {
        Nodo* actual = cabeza;
        cout << "Lista (inicio a fin): ";
        while (actual != nullptr) {
            cout << actual->dato << " <-> ";
            actual = actual->siguiente;
        }
        cout << "NULL" << endl;
    }

    void mostrarHaciaAtras() const {
        Nodo* actual = cola;
        cout << "Lista (fin a inicio): ";
        while (actual != nullptr) {
            cout << actual->dato << " <-> ";
            actual = actual->anterior;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    ListaDoblementeEnlazada lista;

    lista.insertarFinal(10);
    lista.insertarFinal(20);
    lista.insertarFinal(30);
    lista.insertarInicio(5);

    lista.mostrarHaciaAdelante();
    lista.mostrarHaciaAtras();

    cout << "Buscando 20: " << (lista.buscar(20) ? "Encontrado" : "No encontrado") << endl;
    cout << "Buscando 50: " << (lista.buscar(50) ? "Encontrado" : "No encontrado") << endl;

    cout << "Eliminando inicio..." << endl;
    lista.eliminarInicio();
    lista.mostrarHaciaAdelante();

    cout << "Eliminando final..." << endl;
    lista.eliminarFinal();
    lista.mostrarHaciaAdelante();

    cout << "Eliminando valor 20..." << endl;
    lista.eliminarValor(20);
    lista.mostrarHaciaAdelante();

    return 0;
}
