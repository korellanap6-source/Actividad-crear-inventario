#include <iostream> 
#include <fstream>  
#include <stdexcept>
#include <vector>   
#include <algorithm>
using namespace std;

struct Producto {
    int codigo, stock;
    char combre[40];
    float precio;
};

const int MAX = 50;
Producto inventario[MAX];
int totalProductos=0;



