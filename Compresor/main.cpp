#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<pair<char, uint16_t>> rlc_compresor(vector<char>);

void escribirEnArchivo(vector<pair<char, uint16_t>>, string);

int main(){

    string nombreArchivo;
    cout<<"Ingrese el nombre del archivo: ";
    cin>>nombreArchivo;

    ifstream archivo(nombreArchivo);

    if(!archivo.fail()){
        vector<char> data;
        char caracter;
        while(archivo.get(caracter)){
            data.push_back(caracter);
        }

        archivo.close();

        vector<pair<char, uint16_t>> data_comprimida = rlc_compresor(data);

        
        escribirEnArchivo(data_comprimida, nombreArchivo.substr(0, nombreArchivo.find_last_of("."))+".rlc" );
    }


    return 0;
}

vector<pair<char, uint16_t>> rlc_compresor(vector<char> data){
    vector<pair<char, uint16_t>> data_comprimida;

    char simboloActual = data[0];
    uint16_t repeticiones = 1;

    for(size_t i = 1; i < data.size(); i++){
        if(data[i] == simboloActual){
            repeticiones++;
        }else{
            //Crear el par (simbolo, repeticion) y lo inserta en la lista
            data_comprimida.push_back(make_pair(simboloActual, repeticiones));
            simboloActual = data[i];
            repeticiones = 1;
        }
    }

    data_comprimida.push_back(make_pair(simboloActual, repeticiones));

    return data_comprimida;
}

void escribirEnArchivo(vector<pair<char, uint16_t>> data_comprimida, string nombreArchivo){
    ofstream archivoComprimido(nombreArchivo, ios::binary);

    uint8_t cabecera[] = {'R','L','C',8,16};

    archivoComprimido.write(reinterpret_cast<char*>(cabecera), sizeof(cabecera));

    for(pair<char, uint16_t> &pair : data_comprimida){
        archivoComprimido.write(reinterpret_cast<char*>(&pair.first), sizeof(pair.first));
        archivoComprimido.write(reinterpret_cast<char*>(&pair.second), sizeof(pair.second));
    }

    archivoComprimido.close();
}
