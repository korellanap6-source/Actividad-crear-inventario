#include <iostream> 
#include <fstream>  
#include <stdexcept>
#include <vector>   
#include <algorithm>
#include <stdlib.h>

using namespace std;

struct Producto {
    int codigo, stock;
    char nombre[40];
    float precio;
};

const int MAX = 50;
Producto inventario[MAX];
int totalProductos=0;

void guardarInventario(const string& archivo) {
        ofstream file(archivo, ios::binary | ios::trunc);
        if(!file) throw runtime_error("Error al guardar: " + archivo);
        file.write(reinterpret_cast<const char*>(inventario),
                totalProductos * sizeof(Producto));
    }

int main(){
    const string ARCH = "inventario.dat";
    vector <Producto> vProductos;
    system("cls");
    try{
        for (int i= 0; i < 5; i++ ){
            cout << "\nIngrese los datos del producto "<< i+1 << endl; 
            cout << "codigo: ";
            cin >> inventario[i].codigo;

            cout <<"Nombre: ";
            cin.ignore();
            cin.getline(inventario[i].nombre, 40);

            cout << "Precio: ";
            cin >> inventario[i].precio;

            cout << "stock: ";
            cin >> inventario[i].stock;

            totalProductos++;
            system("cls");
        }
        guardarInventario(ARCH);
        
        cout << "\nLos 5 productos se guardaron exitosamente" << endl;
    } catch (const runtime_error& e){
        cerr << "erro: "<<e.what() << endl;
    }
    return 0;
}

