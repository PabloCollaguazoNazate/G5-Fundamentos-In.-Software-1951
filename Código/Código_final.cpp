#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>
#include <map>
using namespace std;
// Estructura para representar un producto
struct Producto {
    string nombre;
    float precio;
};
vector<Producto> productos; // Lista de productos disponibles
vector<Producto> carrito;   // Productos seleccionados para la compra

// Función para validar nombres
bool esNombreValido(const string& nombre) {
    if (nombre.empty()) return false;
    for (char c : nombre) {
        if (isdigit(c) || (!isalnum(c) && !isspace(c))) return false;
    }
    return true;
}

// Función para ingresar un precio válido
float ingresarPrecio() {
    float precio;
    while (true) {
        cout << "Ingrese el precio del producto: ";
        cin >> precio;
        if (cin.fail() || precio <= 0) {
            cout << "Error: ingrese un valor mayor que 0." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return precio;
        }
    }
}
// Agregar productos sin salir del menú
void agregarProducto() {
    char continuar;
    do {
        Producto p;
        string nombreProducto;
        cin.ignore();

        do {
            cout << "Ingrese el nombre del producto: ";
            getline(cin, nombreProducto);
            if (!esNombreValido(nombreProducto)) {
                cout << "Error: Nombre inválido." << endl;
            }
        } while (!esNombreValido(nombreProducto));

        p.nombre = nombreProducto;
        p.precio = ingresarPrecio();
        productos.push_back(p);
        cout << "Producto agregado con éxito!" << endl;

        cout << "¿Desea agregar otro producto? (s/n): ";
        cin >> continuar;
    } while (continuar == 's' || continuar == 'S');
}

// Mostrar productos disponibles
void mostrarProductos(const vector<Producto>& lista) {
    if (lista.empty()) {
        cout << "No hay productos." << endl;
        return;
    }
    cout << "\nLista de productos:" << endl;
    for (size_t i = 0; i < lista.size(); i++) {
        cout << i + 1 << ". " << lista[i].nombre << " - $" << fixed << setprecision(2) << lista[i].precio << endl;
    }
}

// Eliminar un producto
void eliminarProducto() {
    mostrarProductos(productos);
    if (productos.empty()) return;

    int indice;
    cout << "Ingrese el número del producto a eliminar: ";
    cin >> indice;
    if (indice < 1 || indice > productos.size()) {
        cout << "Error: número inválido." << endl;
        return;
    }
    productos.erase(productos.begin() + (indice - 1));
    cout << "Producto eliminado correctamente!" << endl;
}

// Seleccionar productos para la compra
void seleccionarCompra() {
    mostrarProductos(productos);
    if (productos.empty()) return;

    int indice;
    char continuar;
    do {
        cout << "Ingrese el número del producto que desea comprar: ";
        cin >> indice;
        if (indice < 1 || indice > productos.size()) {
            cout << "Error: número inválido." << endl;
        } else {
            carrito.push_back(productos[indice - 1]);
            cout << "Producto agregado al carrito." << endl;
        }
        cout << "¿Desea agregar otro producto? (s/n): ";
        cin >> continuar;
    } while (continuar == 's' || continuar == 'S');
}

// Calcular total de la compra
float calcularTotal() {
    float total = 0.0;
    for (const auto& p : carrito) total += p.precio;
    return total;
}

// Calcular cambio en billetes y monedas
void calcularCambio(float pago) {
    float total = calcularTotal();
    float cambio = pago - total;

    if (cambio < 0) {
        cout << "Dinero insuficiente." << endl;
        return;
    }

    cout << "Cambio a devolver: $" << fixed << setprecision(2) << cambio << endl;
}

// Ingresar pago y calcular cambio
void realizarPago() {
    float total = calcularTotal();
    if (total == 0) {
        cout << "No hay productos en el carrito." << endl;
        return;
    }

    float pago;
    cout << "Total a pagar: $" << fixed << setprecision(2) << total << endl;

    do {
        cout << "Ingrese la cantidad con la que paga: ";
        cin >> pago;
        if (pago < total) cout << "Error: El pago es menor al total." << endl;
    } while (pago < total);

    calcularCambio(pago);
    carrito.clear();
}

int main() {
    int opcion;

    // Imprimir el menú una sola vez al principio
    cout << "\n--- MENU ---" << endl;
    cout << "1. Agregar producto" << endl;
    cout << "2. Mostrar productos" << endl;
    cout << "3. Eliminar producto" << endl;
    cout << "4. Seleccionar productos para compra" << endl;
    cout << "5. Realizar pago y calcular cambio" << endl;
    cout << "6. Salir" << endl;

    do {
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: agregarProducto(); break;
            case 2: mostrarProductos(productos); break;
            case 3: eliminarProducto(); break;
            case 4: seleccionarCompra(); break;
            case 5: realizarPago(); break;
            case 6: cout << "Saliendo..." << endl; break;
            default: cout << "Opción no válida." << endl;
        }

        // Solo mostrar el menú después de ejecutar una opción
        if (opcion != 6) {
            cout << "\n--- MENU ---" << endl;
            cout << "1. Agregar producto" << endl;
            cout << "2. Mostrar productos" << endl;
            cout << "3. Eliminar producto" << endl;
            cout << "4. Seleccionar productos para compra" << endl;
            cout << "5. Realizar pago y calcular cambio" << endl;
            cout << "6. Salir" << endl;
        }

    } while (opcion != 6);

    return 0;
}


