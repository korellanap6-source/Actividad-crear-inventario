#include <iostream> 
#include <fstream>  
#include <stdexcept>
#include <vector>   
#include <algorithm>
#include <stdlib.h>
#include <iomanip>

using namespace std;

struct Producto {
    int codigo, stock;
    char nombre[40];
    float precio;
};

const int MAX = 50;
Producto inventario[MAX];
int totalProductos=0;

void ordenarPorPrecio() {
        for(int i=0;i<totalProductos-1;i++)
        for(int j=0;j<totalProductos-i-1;j++)
            if(inventario[j].precio > inventario[j+1].precio)
                swap(inventario[j], inventario[j+1]);
}

void guardarInventario(const string& archivo) {
        ofstream file(archivo, ios::binary | ios::trunc);
        if(!file) throw runtime_error("Error al guardar: " + archivo);
        file.write(reinterpret_cast<const char*>(inventario),
                totalProductos * sizeof(Producto));
    }

int BuscarPorNombre(const string& NombreBuscado){
    for(int i=0; i<totalProductos; i++){
        if(string(inventario[i].nombre)==NombreBuscado){
            return i;
        }
    }
    return -1;
}

void MostrarInventarioTabla(){
    cout << "\n================ INVENTARIO ================" << endl;
    cout << left << setw(10) << "codigo"
         << setw(20) << "nombre"
         << setw(10) << "Precio" 
         << setw(10) << "Stock" << endl;
    cout << "--------------------------------------------------" << endl;

    for(int i = 0; i<totalProductos; i++){
        cout << left << setw(10) << inventario[i].codigo
             << setw(20) << inventario[i].nombre
             << setw(10) << inventario[i].precio
             << setw(10) << inventario[i].stock << endl;
    }
    cout << "==================================================\n" << endl;
}

void cargarInventario(const string& arch, vector<Producto>& vProd){
    ifstream file(arch, ios::binary);
    if(!file) throw runtime_error("no existe o no se puede abrir: "+ arch);

    vProd.clear();
    Producto P;

    while(file.read(reinterpret_cast<char*>(&P), sizeof(P))){
        vProd.push_back(P);
    }
}

bool compararPorCodigo(const Producto& a, const Producto& b){
    return a.codigo < b.codigo;
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

        ordenarPorPrecio();
        MostrarInventarioTabla();

        string nombrebuscar;
        cout << "Ingrese el nombre del producto que desea buscar; ";
        cin >> nombrebuscar;

        int indice = BuscarPorNombre(nombrebuscar);
        if (indice!=-1){
            cout << "Producto encontrado"<<endl;
            cout << "El producto '"<<inventario[indice].nombre
                 << "' cuesta $"<<inventario[indice].precio
                 << " y hay "<<inventario[indice].stock<< " en stock."<<endl;
        }else {
            cout << "El producto '"<< nombrebuscar<< "' no existe en el inventario "<<endl;
        }

    cargarInventario(ARCH, vProductos);
    cout<<"\nSe cargaron "<< vProductos.size()<<" productos al vector STL"<<endl;

    sort(vProductos.begin(), vProductos.end(), compararPorCodigo);
    cout << "El vector STL ha sido ordenado por codigo."<<endl;

    cout << "\n--- Modificar Precio (Acceso Aleatorio) ---" << endl;
    int indiceMod;

    cout << "Ingrese el indice del producto a modificar (0 a "<< vProductos.size()-1<<"): ";
    cin>>indiceMod;

    if(indiceMod >= 0 && indiceMod < vProductos.size()){
        float  nuevoPrecio;
        cout << "El producto actual es: " << vProductos[indiceMod].nombre<< " $"<< vProductos[indiceMod].precio << endl;
        cout << "ingrese el nuevo precio: ";
        cin >> nuevoPrecio;

        vProductos[indiceMod].precio=nuevoPrecio;

        fstream archivo(ARCH, ios::in | ios::out | ios::binary);
        if(!archivo) throw runtime_error("No se pudo abrir para modificar");

        int posicionfisica= indiceMod*sizeof(Producto);

        archivo.seekp(posicionfisica);

        archivo.write(reinterpret_cast<const char*>(&vProductos[indiceMod]), sizeof(Producto));
        cout << "Precio modificado exitosamente en el archivo" << endl;
    }else {
        cout << "Indice fuera de rango." << endl;
    }

    } catch (const runtime_error& e){
        cerr << "erro: "<<e.what() << endl;
    }
    return 0;
}

