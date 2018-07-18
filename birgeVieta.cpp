//
//  birgeVieta
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

//Metodo para division sintetica
void synDiv(vector <double> poly, vector <double> &temp, double div){
    temp.push_back(poly.at(0));
    
    for (int x = 1; x < poly.size(); x++)
        temp.push_back(poly.at(x) + div*temp.at(x-1));
}

int main() {
    
    srand(time(0)); //Generar random seed
    char choice; //Hacer otro polinomio
    
    do{
        
        //Declaracion de variables
        bool stop;
        double div, error, coef;
        int size, iter = 0, iterCap;
        vector <double> poly, temp1, temp2, ans;
    
        //Ingresar datos
        do{
            cout << "Grado de polinomio: ";
            cin >> size;
            
            if (size <= 0)
                cout << "Grado de polinomio no valido. Intente de nuevo" << endl << endl;
        } while (size <= 0);
    
        for (int x = size; x >= 0; x--){
            cout << "Coeficiente de termino grado " << x << ": ";
            cin >> coef;
            poly.push_back(coef);
        }
    
        cout << endl << "Maximo de iteraciones: ";
        cin >> iterCap;
    
        cout << "Tolerancia de error: ";
        cin >> error;
    
        cout << endl;

        do{
            
            //Inicializar valores
            temp1.clear();
            temp2.clear();
            stop = false;
            div = (rand())/(RAND_MAX/(-20.0)) + 10;
            
            do{
                //Primera división sintetica
                synDiv(poly, temp1, div);
                
                //Es raiz
                if (abs(temp1.back()) < error){
                    //Contabilizar respuestas
                    size--;
                    stop = true;
                    ans.push_back(div);
                    
                    //Definir nuevo polinomio reducido
                    temp1.pop_back();
                    poly = temp1;
                }
                
                //No es raiz
                else{
                    
                    //f'(x)
                    synDiv(temp1, temp2, div);
                    temp2.pop_back();
                    
                    //x = x - f'(x)/f(x)
                    div = div - temp1.back()/temp2.back();
                    
                    //Limpiar arreglos y contar iter
                    temp1.clear();
                    temp2.clear();
                    iter++;
                }
                
            }while(!stop && iter < iterCap);
            
        }while (size > 0 && iter < iterCap);
    
        //Imprimir respuestas
        
        //Avisar si se llego al limite
        if (iter >= iterCap)
            cout << "NOTA: se llego al limite de iteraciones ingresado. Respuestas pueden estar incorrectas o incompletas" << endl << endl;
        
        //Ordenar racies
        sort(ans.begin(), ans.end());
        
        //Mostrar racies
        cout << "Raices reales: " << endl;
        for (int y = 0; y < ans.size(); y++)
            cout << ans.at(y) << endl;
        
        //Poner mensaje si no se hallaron reales
        if (ans.size() == 0)
            cout << "(Ninguna)" << endl;
    
        //Imprimir imaginarias
        if (size != 0)
            cout << endl << size << " raices imaginarias restantes" << endl;
        
        //Volver a resolver
        cout << endl << "Desea resolver otro (s/n): ";
        cin >> choice;
        
        cout << endl;
        
    } while(choice == 's');
    
    return 0;
}
