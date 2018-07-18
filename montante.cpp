//
//  montante
//

#include <iostream>
using namespace std;

int main() {
    
    //Variables
    double p_prev = 1;
    double p_act = 1;
    bool noSol = false;
    
    //Numero de ecuaciones e incognitas
    int eqn, incog;
    
    do{
        cout << "Numero de ecuaciones: ";
        cin >> eqn;
        cout << "Numero de incognitas: ";
        cin >> incog;
        
        if (incog != eqn)
            cout << "Se requiere mismo numero de ecuaciones e incognitas para empezar. Intente de nuevo." << endl << endl;
        
        if ((incog < 0) || (eqn < 0))
            cout << "Input no valido para numero de ecuaciones o incognitas." << endl << endl;
        
    }while ((incog != eqn) || (incog < 0) || (eqn < 0));
    
    //Matrices
    double mat[eqn][incog+1];
    double matAux[eqn][incog+1];
    
    //Captura de datos
    for (int x = 0; x < eqn; x++){
        cout << endl << "ECUACION #" << x+1 << ":" << endl;
        for (int y = 0; y < incog; y++){
            cout << "Coeficiente de incognita " << y+1 << ": ";
            cin >> mat[x][y];
        }
        cout << "Constante de ecuacion: ";
        cin >> mat[x][incog];
    }
    
    //Resolucion de matriz
    for (int k = 0; k < eqn && !noSol; k++){
        
        int shift = 0;
        p_act = mat[k][k];
        
        //Encuentra primer valor != 0
        while(mat[k+shift][k] == 0 && k+shift < eqn){
            shift++;
        }
        
        //Si columna entera quedo en 0's
        if (k+shift == eqn)
            noSol = true;
        
        //Intercambia renglones de ser necesario
        if (k+shift != eqn && shift){
            int temp[incog+1];
            for (int x = 0; x < incog+1; x++)
                temp[x] = mat[k][x];
            for (int y = 0; y < incog+1; y++)
                mat[k][y] = mat[k+shift][y];
            for (int z = 0; z < incog+1; z++)
                mat[k+shift][z] = temp[z];
            
            p_act = mat[k][k];
        }
        
        //Llena columnas previas con 0 o Pivote actual
        for (int y = 0; y < eqn; y++){
            for (int x = 0; x <= k; x++){
                if (x == y){ matAux[y][x] = p_act; }
                else { matAux[y][x] = 0; }
            }
        }
        
        //Llena renglon de pivote actual
        for (int x=k+1; x < incog+1; x++){
            matAux[k][x] = mat[k][x];
        }
        
        //Cuadrante I
        for (int y=0; y < k; y++){
            for (int x=k+1; x < incog+1; x++){
                matAux[y][x] = -1*(mat[y][k]*mat[k][x]-mat[y][x]*mat[k][k])/p_prev;
            }
        }
        
        //Cuadrante IV
        for (int y=k+1; y < eqn; y++){
            for (int x=k+1; x < incog+1; x++){
                matAux[y][x] = (mat[y][x]*mat[k][k]-mat[y][k]*mat[k][x])/p_prev;
            }
        }
        
        //Copy Aux to OG
        memcpy(mat, matAux, sizeof(matAux));
        
        //Actualizar pivote
        p_prev = p_act;
        
    }
    
    //Soluciones
    cout << endl;
    if (mat[0][0] == 0 || noSol)
        cout << "Sistema no tiene solucion unica" << endl;
    else{
        for (int x = 0; x < incog; x++)
            cout << "x" << (x+1) << ": " << mat[x][incog]/mat[x][x] << endl;
    }
    
    return 0;
}
