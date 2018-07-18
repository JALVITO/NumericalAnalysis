//
//  interpolation
//

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

void montante(vector<vector<double>> &mat, vector<vector<double>> matAux){
    double p_prev = 1;
    double p_act = 1;
    bool noSol = false;
    
    for (int k = 0; k < mat.size() && !noSol; k++){
        
        int shift = 0;
        p_act = mat[k][k];
        
        //Encuentra primer valor != 0
        while(mat[k+shift][k] == 0 && k+shift < mat.size()){
            shift++;
        }
        
        //Si columna entera quedo en 0's
        if (k+shift == mat.size())
            noSol = true;
        
        //Intercambia renglones de ser necesario
        if (k+shift != mat.size() && shift){
            int temp[mat[0].size()];
            for (int x = 0; x < mat[0].size(); x++)
                temp[x] = mat[k][x];
            for (int y = 0; y < mat[0].size(); y++)
                mat[k][y] = mat[k+shift][y];
            for (int z = 0; z < mat[0].size(); z++)
                mat[k+shift][z] = temp[z];
            
            p_act = mat[k][k];
        }
        
        //Llena columnas previas con 0 o Pivote actual
        for (int y = 0; y < mat.size(); y++){
            for (int x = 0; x <= k; x++){
                if (x == y){ matAux[y][x] = p_act; }
                else { matAux[y][x] = 0; }
            }
        }
        
        //Llena renglon de pivote actual
        for (int x=k+1; x < mat[0].size(); x++){
            matAux[k][x] = mat[k][x];
        }
        
        //Cuadrante I
        for (int y=0; y < k; y++){
            for (int x=k+1; x < mat[0].size(); x++){
                matAux[y][x] = -1*(mat[y][k]*mat[k][x]-mat[y][x]*mat[k][k])/p_prev;
            }
        }
        
        //Cuadrante IV
        for (int y=k+1; y < mat.size(); y++){
            for (int x=k+1; x < mat[0].size(); x++){
                matAux[y][x] = (mat[y][x]*mat[k][k]-mat[y][k]*mat[k][x])/p_prev;
            }
        }
        
        //Copy Aux to OG
        mat = matAux;
        
        //Actualizar pivote
        p_prev = p_act;
    }
    
    if (mat[0][0] == 0 || noSol)
        cout << "Sistema no tiene solucion unica" << endl;
    else{
        cout << "Como fueron " << mat.size() << " datos, entonces por el método Polinomio único de interpolación, el polinomio obtenido es de grado " << mat.size()-1 << " y corresponde a: " << endl << endl << "P" << mat.size()-1 << "(x) = ";
        
        bool firstTerm = mat[0][mat.size()]/mat[0][0] != 0;
        
        if (firstTerm)
            cout << mat[0][mat.size()]/mat[0][0];
        
        for (int x = 1; x < mat.size(); x++){
            
            //Agrega + si positivo y no primer termino
            if (mat[x][mat.size()]/mat[0][0] > 0 && firstTerm)
                cout << "+";
            
            //Si termino existe
            if (mat[x][mat.size()]/mat[0][0] != 0){
                firstTerm = true;
                
                //Si termino tiene coeficiente de uno
                if (abs(mat[x][mat.size()]/mat[x][x]) == 1){
                    //Si termino tiene coeficiente de menos uno
                    if (mat[x][mat.size()]/mat[x][x] < 0)
                        cout << "-";
                    cout << "x";
                }
                else
                    cout << mat[x][mat.size()]/mat[x][x] << "x";
                
                //Si requiere exponente
                if (x != 1)
                    cout << "^" << x;
            }
        }
        cout << endl;
    }
    
}

bool repetido(double arr[], int size, double num){
    for (int x = 0; x < size; x++){
        if (num == arr[x])
            return true;
    }
    return false;
}

int main() {
    
    char c;
    
    do{
        int datos = 0;
        cout << "Cantidad de datos: ";
        cin >> datos;
        
        double parejas[2][datos];
        
        for (int x = 0; x < datos; x++){
            bool re = false;
            do{
                cout << "x" << x << ": ";
                cin >> parejas[0][x];
                cout << "y" << x << ": ";
                cin >> parejas[1][x];
                cout << endl;
                
                re = repetido(parejas[0], x, parejas[0][x]);
                if (re)
                    cout << "Ese valor de x ya existe, vuelva a ingresar uno valido" << endl;
                
            } while(re);
        }
        
        vector<vector<double>> mat;
        for (int y = 0; y < datos; y++){
            mat.push_back(vector<double>());
            mat[y].push_back(1);
            for (int z = 1; z < datos; z++){
                mat[y].push_back(pow(parejas[0][y], z));
            }
            mat[y].push_back(parejas[1][y]);
        }
        
        montante(mat, mat);
        
        cout << "Quieres resolver otro? (s/n)";
        cin >> c;
        
    } while (c != 'n');
        
    return 0;
}
