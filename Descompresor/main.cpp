#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<char> rlc_descompresor(vector<pair<char, uint16_t>>);

vector<pair<char, uint16_t>> leerArchivoComprimido(string);

void escribirArchivoDescomprimido(vector<char>, string);

int main(){

    string nombreArchivo;

    cout<<"Ingrese el nombre del archivo rlc comprimido: ";
    cin>>nombreArchivo;

    if(!ifstream(nombreArchivo).fail()){
        vector<pair<char, uint16_t>> data_comprimida = leerArchivoComprimido(nombreArchivo);
        
        vector<char> data_descomprimida = rlc_descompresor(data_comprimida);

        escribirArchivoDescomprimido(data_descomprimida, "desRlc"+nombreArchivo);
    }else{
        cout<<"No existe el archivo"<<endl;
    }


    return 0;
}

vector<char> rlc_descompresor(vector<pair<char, uint16_t>> data_comprimida){
    vector<char> data_descomprimida;

    
    for(auto &pair: data_comprimida){
        for(uint16_t i = 0; i < pair.second; i++){
            data_descomprimida.push_back(pair.first);
        }
    }

    return data_descomprimida;
}

vector<pair<char, uint16_t>> leerArchivoComprimido(string nombreArchivo){
    vector<pair<char, uint16_t>> data_comprimida;

    ifstream archivo(nombreArchivo, ios::binary);

    //Verificar cabecera
    uint8_t cabecera[5];
    archivo.read(reinterpret_cast<char*>(cabecera), sizeof(cabecera));

    if(cabecera[0] != 'R' || cabecera[1] != 'L' || cabecera[2] != 'C' || cabecera[3] != 8 || cabecera[4] != 16 ){
        cerr << "El archivo no fue comprimido en RLC" << endl;
        exit(1);
    }

    char data;
    uint16_t repeticiones;

    while( archivo.read(reinterpret_cast<char*>(&data), sizeof(data)) ){
        archivo.read(reinterpret_cast<char*>(&repeticiones), sizeof(repeticiones));
        data_comprimida.push_back(make_pair(data, repeticiones));
    }

    archivo.close();

    return data_comprimida;
}

void escribirArchivoDescomprimido(vector<char> data_descomprimida, string nombreArchivo){
    ofstream archivo(nombreArchivo, ios::binary);
    for(auto &caracter: data_descomprimida){
        archivo.write(&caracter, sizeof(caracter));
    }

    archivo.close();
}