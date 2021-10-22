#include <iostream>
#include <fstream>
#include <locale.h>
#include <stdio.h> //para cambiar el color de la consola
#include <string>
#include <cstdlib>
#include <time.h>//Generar valores random
#include <iomanip>

using namespace std;

/*-------------------------Variables-------------------------*/
const int tamF = 4;
int verificadorUsuarioPass; //Es el verificador del usuario y de la contraseña
string vUsuario,vPass;


/*-------------------------Vectores-------------------------*/
string pilotosnascar[][2] = {{"Kyle Larson","1"},{"Denny Hamlin","2"},{"Kyle Busch","3"},{"Martin Truex","4"},{"Ryan Blanea","5"}}; 
string pilotosformula1[][2] = {{"Lewis Hamilton","1"},{"Max Verstappen","2"},{"Valtteri Bottas","3"},{"Lando Norris","4"},{"Sergio Perez","5"}}; 
string pilotosdakar[][2] = {{"Hubert Auriol","1"},{"Ari Vatanen","2"},{"Cyril Despres","3"},{"Marc Coma", "4"},{"Nairo Quintana", "5"}}; 

float historialSaldo[3] = {0,0,0};

/*-------------------------Matrices-------------------------*/
string usuarioPassword[tamF][2]; // {{a,b,c,d},{p1,p2,p3,p4}}

/*---------------------------Menus---------------------------*/
void borde(string); //Genera borde de * alrededor del string 

int MenuInicio(int opc); //Menu principal del programa

int menuCliente(); //Menu del programa, donde estan las principales funciones a las que accede el usuario

int menuApostar(); // Menu donde se registran todas las competiciones a las que el programa tiene acceso

void apostar(); //Complemento del menu de apuestas, donde muestra las competenciciones

/*----------------------Procedimientos-----------------------*/
void iniciarSesion();
void historial1(string Usuario);
void registrarU();
void CrearCuenta();
void escribirUsuarioPassword();
void cliente();
void consultarSaldo(); //Rectifica el saldo del usuario dentro del archivo txt
void recargarCuenta(); //Realiza el proceso de "recarga" a la cuenta del ususario, inicializada en $0
void historial1(string usuario); //Inicia el archivo para guardar, el nombre del ususario que opera en dicho momento
void historial2(int operacion); //Complemento del historial, donde todas las operaciones del usuario quedan registradas (perdidas y ganancias)
void competicion(string carrera, string pilotos[][2],int TamF, int tamF); //Se realiza el proceso de presentar la competencias y determinar la apuesta
void mostrarMatrizStr(string matriz[][2],int,int);
void historialOperaciones();
void escribirHistorialOperaciones();
/*-------------------------Funciones-------------------------*/
int VerificarOpc(int, int);
int VerificarOpc(int OpcAux, int opciones);
int numeroRan(int generarN,int limiteN);


/*---------------------------Menus---------------------------*/
void borde(string titulo){
	for(int i=0; i<titulo.length()+12 ; i++){
		cout <<"*";
	}
	
	cout << "\n*     " << titulo << "     *\n";
	
	for(int i=0; i<titulo.length()+12 ; i++){
		cout <<"*";
	}
}

int MenuInicio (int opc){
	system("cls");
	
	borde("A L F A   A P U E S T A S");
	cout<< "\n1 - Iniciar sesion"
		<< "\n2 - Crear Cuenta"
		<< "\n3 - Salir\n\n\t= ";
	cin >> opc;
	
return opc;
}

int menuCliente(){
	int opcion;
	system("cls");
	borde("A L F A   R A C E");
	cout<< "\n1 - Apostar"
		<< "\n2 - Consultar saldo"
		<< "\n3 - Recargar cuenta"
		<< "\n4 - Historial de operaciones"
		<< "\n5 - Volver\n\n\t= "; cin>>opcion;
	
	return opcion;
}

int menuApostar(){
	system("cls");
	borde("APOSTAR");
	int opcion;
	cout<< "\n1 - Nascar"
		<< "\n2 - Formula 1"
		<< "\n3 - Dakar"
		<< "\n4 - Salir\n\n\t= "; cin>>opcion;

	return opcion;
}

/*----------------------Procedimientos-----------------------*/
void iniciarSesion(){
	system("cls");
	borde("Iniciar Sesion");
	int verificador=0;
	ifstream archivolee("usuarioPassword.txt");
	cout<<"\nUsuario: ";cin>>vUsuario;
	cout<<"Contraseña: ";cin>>vPass;
	if (archivolee.fail()){
		cout<<"ERROR: Fue imposible abrir el archivo. \n";
	}else{
		while(!archivolee.eof()){
			for (int l = 0; l < 2; l++){
				
				for (int c = 0; c < tamF; c++){
				archivolee>>usuarioPassword[0][c];
				archivolee>>usuarioPassword[1][c];
					if (usuarioPassword[1][c] == vPass && usuarioPassword[0][c]==vUsuario){ //Se verifica que la contraseña sea la misma que la digitada
					verificadorUsuarioPass = 1;
					}
				}
			}
		}
		archivolee.close();
	}
	historial1(vUsuario);
}

void CrearCuenta(){
	string cent;
	int numl=0 ;
	do{
		system("cls");
		borde("Crear Cuenta");	
		
		cout<<"\n¿Cuantas cuentas desea crear?\n\n\t= ";cin>>numl;
		if (numl >= 5){
		cout<<"\nNo se pueden crear más cuentas. \n";
		cent = "n";
		}else{
			for (int l = 0; l < numl; l++){
				cout<<"\nUsuario: ";cin>>usuarioPassword[l][0];
				cout<<"Contraseña: ";cin>>usuarioPassword[l][1];
			}
			
			cout << "\n¿Desea crear otra cuenta? Y | N - "; cin>>cent;
			escribirUsuarioPassword();
		}
	} while (cent == "Y" || cent == "y"); 	
}

void escribirUsuarioPassword(){
	ofstream archivo("usuarioPassword.txt",ios::app);

	if (archivo.fail()){
		cout<<"ERROR: Fue imposible abrir el archivo. \n";
	}else{
		for (int l = 0; l < tamF; l++){ 
			for (int c = 0; c < 2; c++){ 
			archivo<<usuarioPassword[l][c]<<" "; 
			}		 
			archivo<<endl;
		}
		cout<<"\nSe ha creado el archivo. \n";
	}
	archivo.close();
}

void cliente(){
	string centinelaCliente;
	iniciarSesion();
	if (verificadorUsuarioPass == 1){ //En caso de no haber escrito el usuario o contraseña correctos, no deja entrar al menu cliente
		borde("BIENVENIDO, HAZ INICIADO CON EXITO");
		cout << "\n\n";
		system("pause");
		do{
			switch (menuCliente()){
			case 1:{ //Apostar
				apostar();
				break;
				}

			case 2:{ //Consultar saldo
				consultarSaldo();
				break;
				}
			case 3:{ //Recargar cuenta
				recargarCuenta();
				break;
				}
			case 4:{ //Historial de operaciones
				historialOperaciones();
				break;
				}
			case 5:{ //Volver al menu del cliente
				break;
				}
			default:{
				cout<<"ERROR: Digite una opción valida. ";
				break;
				}	
			}
			cout<<"\n¿Desea volver al menu del cliente? Y | N - "; cin>>centinelaCliente;
			system("cls");
		} while (centinelaCliente == "Y" || centinelaCliente == "y");

	}else{
		cout<<"Usuario o contraseña incorrectos. ";	
	}
}

void apostar(){
	string centinelaApostar;
	if (historialSaldo[0] <= 0){
		cout<<"ERROR: No tiene suficiente saldo para apostar";
	}else{
		do{
			switch (menuApostar()){		
			case 1:{ //Nascar
				competicion("Nascar",pilotosnascar,5,2); 
				break;
				}
			case 2:{ //Formula 1
				competicion("Formula 1",pilotosformula1,5,2);
				break;
				}
			case 3:{ //Dakar
				competicion("Dakar",pilotosdakar,5,2);
				break;
				}
			case 4:{ //Salir
				break;
				}
			default:{
				cout<<"ERROR: Digite una opcion valida. ";
				break;
				}
			}
			cout<<"¿Desea volver al menu de apuestas? Y | N "; cin>>centinelaApostar;
		} while (centinelaApostar == "Y" || centinelaApostar == "y");
	}
}

void historial1(string usuario){
	ofstream archivo("historial.txt",ios::app);

	if (archivo.fail()){
		cout<<"ERROR: Fue imposible abrir el archivo. \n";
	}else{
	archivo<<usuario;		
	archivo<<endl;
		}
		cout<<"Se ha creado el archivo. \n";
		archivo.close();
		system("cls");
	}
	
void historial2(int operacion){
	ofstream archivo("historial.txt",ios::app);
	if (archivo.fail()){
		cout<<"ERROR: Fue imposible abrir el archivo. \n";
	}else{
		archivo << "$ " << operacion << endl; 
	}
	archivo.close();
	system("cls");
}

void consultarSaldo(){
	int verificadorConsulta,i;
	system("cls");
	borde("CONSULTAR SALDO");

	for (i = 0; i < 10; i++){ 
		if(historialSaldo[0] == historialSaldo[1]){
			verificadorConsulta == 1;
		}
	}

	if (verificadorConsulta == 1){ /*En caso de que la primera recarga sea igual que el saldo
	se entiende que son lo mismo y no se hace el acumulador*/
		cout<<"\nSu saldo es $"<<fixed<<setprecision(0)<<historialSaldo[0]<<" pesos\n"; 
		//cout<<fixed<<setprecision(0) para evitar que se se imprima con notación cientifica
	}else{
		historialSaldo[0] = historialSaldo[1]-historialSaldo[2]; /*Pero si son diferentes, si se realizara la acumulación*/
		cout<<"\nSu saldo es $"<<fixed<<setprecision(0)<<historialSaldo[0]<<" pesos\n";
		//cout<<fixed<<setprecision(0) para evitar que se se imprima con notación cientifica
		}
}

void recargarCuenta(){	

	float recarga;
	
	system("cls");
	borde("RECARGAR CUENTA");

		cout<<"\n¿Cuanto desea recargar: $";cin>>recarga;
		
		if (recarga <= 0){
			cout<<"Digite un valor valido. ";
		}else{
			historialSaldo[1] = historialSaldo[1]+recarga;
			cout<<"\nSe ha realizado la recarga.\n";
			system("pause");
		}
		consultarSaldo();
}

void competicion(string carrera, string pilotos[][2],int TamF, int tamF){
	float apuesta;
	int ganador,verificador;
	string apuestaStr,centinela;


		do{
			system("cls");
			borde(carrera);
			cout<<"\nEn caso de ganar, el dinero apostado sera multiplicado por 2";
			cout<<"\n¿Cuanto dinero desea apostar?: ";cin>>apuesta;	
			if(apuesta>historialSaldo[0]){
				cout<<"ERROR: No cuenta con esa cantidad de dinero. ";
			}else{
				mostrarMatrizStr(pilotos,5,2);
				cout<<"\nDigite el numero del piloto por el cual desea apostar: "; cin>>apuestaStr;

				for (int i = 0; i < numeroRan(1,10); i++){ //Así nos aseguramos que se genere un buen numero random
					ganador = numeroRan(1,5); /*Generando el ganador, el 1 es la cantidad de digitos que se 
					desean generar y 5 la cantidad de corredores, es decir 5 corredores*/
				}
				
		
				for (int l = 0; l < 5; l++){
					if (pilotos[l][1] == apuestaStr){ //Ver que se haya digitado un numero valido
						verificador = 1;
					}
				}

				if(verificador == 1){	
					if (pilotos[ganador][1] == apuestaStr){ /* Ganador es la ubicacion del
					ganador en lineas y 1 es la columna donde están los numeros de los pilotos */
						cout<<"Felicitaciones, el ganador fue: "<<pilotos[ganador][1]<<" "<<pilotos[ganador][0]<<endl;
						/*pilotosNascar[ganador][1] imprime el numero del piloto ganador y pilotosNascar[ganador][0] el nombre del piloto*/
						historialSaldo[1] = historialSaldo[1]+apuesta*2; //Se registra la ganancia de la apuesta
						system("pause");
						consultarSaldo();
					}else{
						cout<<"Lo sentimos, el ganador fue: "<<pilotos[ganador][1]<<" "<<pilotos[ganador][0]<<endl;
						/*pilotosNascar[ganador][1] imprime el numero del piloto ganador y pilotosNascar[ganador][0] el nombre del piloto*/
						historialSaldo[2] = historialSaldo[2]+apuesta; //Se registra la perdida de la apuesta
						system("pause");
						consultarSaldo();
					}
				}else{
					cout<<"Digite un piloto valido.";
				}
			}	
			cout<<"\n\n¿Desea volver a apostar? Y | N: ";cin>>centinela; 
		}while(centinela == "Y" || centinela == "y");	
}
void mostrarMatrizStr(string matriz[][2],int nlineas,int ncolumnas){
	for (int l = 0; l < nlineas; l++){
		for (int c = 0; c < ncolumnas; c++){
			cout<<matriz[l][c]<<" ";
		}
		cout<<endl;
	}
}

void historialOperaciones(){
	system("cls");
	borde("HISTORIAL OPERACIONES");
	
	time_t now = time(0); //funcion de la biblioteca time.h que pide al sistema operativo fecha y hora
  	string dt = ctime(&now);

	cout<<endl<<dt<<"\nUsuario\tSaldo Entradas Perdidas\n";
	cout<<vUsuario<<"\t";
	for (int l = 0; l < 3; l++){ 
		cout<<historialSaldo[l]<<"\t"; 
	}	
	escribirHistorialOperaciones();
}

void escribirHistorialOperaciones(){
	ofstream archivo("historialOperaciones.txt",ios::app);

	if (archivo.fail()){
		cout<<"ERROR: Fue imposible abrir el archivo. \n";
	}else{
		time_t now = time(0); //funcion de la biblioteca time.h que pide al sistema operativo fecha y hora
  		string dt = ctime(&now);

		archivo<<dt<<"Usuario\tSaldo Entradas Perdidas\n";
		archivo<<vUsuario<<"\t";
		for (int l = 0; l < 3; l++){ 
			archivo<<historialSaldo[l]<<"\t\t"; 
		}
		archivo<<endl<<endl;
		cout<<"\nSe ha creado el archivo. \n";
	}
	archivo.close();
}

/*-------------------------Funciones-------------------------*/
int numeroRan(int generarCantidadDigitos,int generarHasta){
	int aleatorio;
	for(int i=1; i<= generarCantidadDigitos; i++){ 
	// Ciclo for para generar X digitos
    aleatorio = rand()%generarHasta;
    }
	return aleatorio;
}
