#include "ALFA_Version2,1,14.h"

/*
Es un programa de apuestas de carreras automovilisticas 

*Tener varias competencias: Nascar, Formula 1, 500 millas de indianapolis, etc 
*Crear una cuenta donde puede guardar lo que quiera apostar 
*Apostar por un carro ganador, en caso de que gane va a duplicar lo apostado
*Generar la carrera aleatoriamente con un generador de numeros aleatorios
*Ver resultados de la carrera, puntos de cada vuelta y puntos totales
*Generar un archivo con los ganadores de cada carrera 
*Generar un archivo con las ganancias o perdidas de dinero
*/

int main (){
	setlocale (LC_ALL, "spanish");
	system ("color B");

	int resp;
	string cent;

	do{			
		switch (MenuInicio(resp)){
		case 1:{//Iniciar sesion
			cliente();
			break;
			}
		case 2:{//Crear cuenta 
			CrearCuenta();
			break;
			}
		
		case 3:{//Cerrar programa
			exit(0);
			break;
			}

		default:{
			cout<<"ERROR: Digite una opcion valida. ";
			break;
			}
		}
		cout << "\n¿Desea volver al menu principal? Y | N - "; cin>>cent;
	}while(cent == "Y" || cent == "y");
return 0;
}
