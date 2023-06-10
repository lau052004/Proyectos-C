#include <iostream>
#include <fstream>
#include <iomanip> 
#define maxaf 100 
#define maxrut 20 
#define maxcoderut 20
#define maxprohibi 20
using namespace std;

struct rutina //Estructura con la información de cada rutina
{ 
    int cod;
    char nomRutina[20];
    char horario;
    int cantprohibiciones;
    char pro1;
    char pro2;
    char simultaneo;
}; 

struct afiliado //Estructura datos del afiliado
{
    int cedula; 
    char nombre[20]; 
    int telefono; 
    char direccion[20]; 
    char ciudad[15]; 
    char sexo; 
    char horario; 
    int cantrut; 
    int coderut [maxcoderut]; 
    char nomPariente[20];
    float estatura;
    float peso;
    int cantmeses;
    int cantmeseshoja; 
    int salud[4][12];
    int cantprohibicion; 
    char prohibiciones[maxprohibi]; 
}; 

// DECLARACIÓN DE LAS FUNCIONES
void ingresar_datos(fstream &gymdeath_clientes, fstream &gymdeath_rutinas);//funcion opcion 0
void imprimir_todo (fstream &gymdeath_clientes, fstream &gymdeath_rutinas); //funcion opcion 1
void imprimir_mujer (fstream &gymdeath_clientes);//funcion opcion 2
void imprimir_hombre(fstream &gymdeath_clientes); //funcion opcion 3
void imprimir_Aficonrutina(fstream &gymdeath_clientes, fstream &gymdeath_rutinas);//funcion opcion 4
void cambio_horario(fstream &gymdeath_clientes);//Función 5 SUSTENTACIÓN PROYECTO
void nuevoAfiliado(fstream &gymdeath_clientes);//funcion opcion 6
void programar_rutina(fstream &gymdeath_clientes,fstream &gymdeath_rutinas );//funcion opcion 7
void modifica_hojaval(fstream &gymdeath_clientes); //funcion opcion 8

int main()
{
    fstream gymdeath_clientes; //Definicion de los archivos
    fstream gymdeath_rutinas; 

    cout<< endl << "----------- BIENVENIDO AL GIMNASIO GYM-DEATH -----------";
    bool entro = false; //booleano para saber si ya se entró a la función 0
    int opcion; //para ingresar la opcion
    bool afi_nuevo = false; //para saber si ya se ingresó un afiliado nuevo
    afiliado afiliados;

    gymdeath_clientes.open("datos_clientes.dat", ios::binary| ios::in);
    gymdeath_rutinas.open("datos_rutinas.dat", ios::binary| ios::in); 
    // Se ubica el apuntador de lectura al final del archivo
    gymdeath_clientes.seekg(0,ios::end); 
    gymdeath_rutinas.seekg(0,ios::end); 

    /* Si el apuntador de lectura tiene una pocisión válida 
    quiere decir los archivos ya existen */ 
    if(gymdeath_rutinas.tellg()!=-1 && gymdeath_clientes.tellg()!=-1)
    {
        cout << "leyendo";
        entro = true;
        //para empezar desde cero se cierra y vuelve a abrir
        gymdeath_clientes.close(); 
        gymdeath_clientes.open("datos_clientes.dat", ios::binary| ios::in);
        //leer si sigue teniendo afiliados nuevos
        gymdeath_clientes.read((char*)&afiliados,sizeof(afiliado));
        //SE HACE ANTES DEL DO-WHILE
        while(!gymdeath_clientes.eof())
        {
        if(afiliados.cantrut==0)
            {
            afi_nuevo=true;
            }
            gymdeath_clientes.read((char*)&afiliados,sizeof(afiliado));
        }
    } 
    gymdeath_rutinas.close(); 
    gymdeath_clientes.close(); 

    do
    {   cout<<"\nMENU\n"; 
        cout << "0. Introducir los datos del gimnasio e introducir los datos de afiliados antiguos por primera vez." << endl;
        cout <<"1. Mostrar datos del gimnasio "<< endl ;
        cout <<"2. Imprimir todos los afiliados de sexo femenino y sus datos completos."<< endl ;
        cout <<"3. Imprimir todos los afiliados de masculino y sus datos completos."<<endl;
        cout <<"4. Imprimir todos los afiliados con una rutina dada."<<endl;
        cout <<"5. Posible cambio de horario (Rutina cardio)."<<endl;
        cout <<"6. Ingresar los datos básicos de un afiliado nuevo sin incluir las rutinas de ejercicio."<<endl;
        cout <<"7. Programación de todas las rutinas posibles para un afiliado nuevo"<<endl;
        cout <<"8. Modificar datos de la hoja de valoracion de un afiliado"<<endl;
        cout <<"9. Salir del programa"<<endl;

        cout<<"\n\nPor favor, ingrese la opcion que desea escoger: "; 
        cin>>opcion;

        switch (opcion)
        {
          case 0:
            if(entro==false)
            {
              entro=true;
              gymdeath_clientes.open("datos_clientes.dat", ios::binary| ios::out); 
              gymdeath_rutinas.open("datos_rutinas.dat", ios::binary| ios::out); 
              if(!gymdeath_clientes)
              {
                cout<<"no se pudo abrir de salida el archivo clientes"; 
                return 1;
              }
              else
              {
                if(!gymdeath_rutinas)
                {
                  cout<<"no se pudo abrir de entrada el archivo rutinas"; 
                  return 1;
                }
                else
                {
                  ingresar_datos(gymdeath_clientes, gymdeath_rutinas);
                }
              }  
            }
            else
            {
              cout<<"\nYa ingreso datos del gimnasio."<<endl;
            } 
            break;
          case 1:
           if(entro==true)
           {
             gymdeath_clientes.open("datos_clientes.dat", ios::binary| ios::in); 
             gymdeath_rutinas.open("datos_rutinas.dat", ios::binary| ios::in); 
             if(!gymdeath_clientes)
             {
              cout<<"no se pudo abrir de entrada el archivo clientes"; 
              return 1;
             }
             else
             {
               if(!gymdeath_rutinas)
               {
                cout<<"no se pudo abrir de entrada el archivo rutinas"; 
                return 1;
               }
               else
               {
                imprimir_todo (gymdeath_clientes, gymdeath_rutinas); 
               }
             }  
           }
           else
           {
            cout<<"\nAun no ha ingresado datos de los afiliados viejos."<<endl;
           }
           break;
          case 2:
            if(entro==true)
            {
              gymdeath_clientes.open("datos_clientes.dat", ios::binary| ios::in); 
              if(!gymdeath_clientes)
              {
               cout<<"no se pudo abrir de entrada el archivo"; 
               return 1;
              }
              else
              {
               imprimir_mujer (gymdeath_clientes); 
              } 
            }
            else
            {
             cout<<"\nAun no ha ingresado datos de afiliados en el programa"<<endl;
            } 
           break;
          case 3:
           if(entro==true)
           {
              gymdeath_clientes.open("datos_clientes.dat", ios::binary| ios::in); 
              if(!gymdeath_clientes)
              {
                cout<<"no se pudo abrir de entrada el archivo"; 
                return 1;
              }
              else
              {
                imprimir_hombre (gymdeath_clientes); 
              } 
           }
           else
           {
            cout<<"\nAun no ha ingresado datos de afiliados en el programa"<<endl;
           }
           break;
          case 4:
            if(entro==true)
            {
              gymdeath_clientes.open("datos_clientes.dat", ios::binary| ios::in); 
              gymdeath_rutinas.open("datos_rutinas.dat", ios::binary| ios::in); 
                if(!gymdeath_clientes)
                {
                  cout<<"no se pudo abrir de entrada el archivo"; 
                  return 1;
                }
                else
                {
                 imprimir_Aficonrutina(gymdeath_clientes,gymdeath_rutinas);
                } 
            }
            else
            {
              cout<<"\nAun no ha ingresado datos de afiliados en el programa"<<endl;
            }
            break;

            //MODIFICACIÓN 
            case 5:
            if(entro==true)
            {
              gymdeath_clientes.open("datos_clientes.dat", ios::binary| ios::in); 
              if(!gymdeath_clientes)
              {
                cout<<"no se pudo abrir de salida el archivo"; 
                return 1;
              }
              else
              {
                cambio_horario(gymdeath_clientes);
                afi_nuevo=true;
              } 

            }
            else
            {
                cout<<"\nAun no ha ingresado datos de afiliados en el programa"<<endl;
            }
            break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////          
          case 6:
            if(entro==true)
            {
              gymdeath_clientes.open("datos_clientes.dat", ios::binary| ios::in|ios::out); 
              if(!gymdeath_clientes)
              {
                cout<<"no se pudo abrir de salida el archivo"; 
                return 1;
              }
              else
              {
                nuevoAfiliado(gymdeath_clientes);
                afi_nuevo=true;
              } 

            }
            else
            {
                cout<<"\nAun no ha ingresado datos de afiliados en el programa"<<endl;
            }
            break;
          case 7:
            if(entro==true)
            {
              if(afi_nuevo==true)
              {
                gymdeath_clientes.open("datos_clientes.dat", ios::binary| ios::in|ios::out);
                gymdeath_rutinas.open("datos_rutinas.dat", ios::binary| ios::in);
                if(!gymdeath_clientes)
                {
                  cout<<"no se pudo abrir de entrada el archivo clientes"; 
                  return 1;
                }
                else
                {
                 if(!gymdeath_rutinas)
                 {
                  cout<<"no se pudo abrir de entrada el archivo rutinas"; 
                  return 1;
                 }
                 else
                 {
                   programar_rutina(gymdeath_clientes, gymdeath_rutinas);
                   afi_nuevo=false;
                 }
                }  
              }
              else
              {
               cout<<"\nNo ha ingresado datos de un afiliado nuevo";
              }
            }
            else
            {
              cout<<"\nAun no ha ingresado datos de afiliados en el programa"<<endl;
            } 
            break;
          case 8:
            if(entro==true)
            {
              gymdeath_clientes.open("datos_clientes.dat", ios::binary| ios::out|ios::in); 
              if(!gymdeath_clientes)
              {
                cout<<"no se pudo abrir de salida el archivo"; 
              }
              else
              {
                modifica_hojaval(gymdeath_clientes); 
              }  
            }
            else
            {
              cout<<"\nAun no ha ingresado datos de afiliados en el programa"<<endl;
            }
            break;
          case 9:
            cout << "\nTermina el programa.";
            break;
         default:
            cout<< "\n Opcion invalida ingrese un numero de 0 a 8"<< endl;
            break;
        }
    }
    while(opcion!=9);
}

void ingresar_datos(fstream&gymdeath_clientes, fstream&gymdeath_rutinas)//funcion opcion 0
{
    int cantrutinas;
    int cantafi;
    //variable de tipo de dato estructura que almacena la cantidad total de afiliados y rutinas para retornarlas a la función principal 
    rutina inforutinas;
    afiliado infoafiliados;
    int indice;
    
    cout << endl << "Ingrese cantidad de rutinas ofrecidas por el gimnasio ";
    cin >> cantrutinas;

    //Ciclo para ingresar los datos de las rutinas
    for(int i=0;i<cantrutinas;i++)
    {
        cout << endl << "Codigo de la rutina " << i << " ";
        cin >> inforutinas.cod;
        cout << "Nombre de la rutina ";
        cin >> inforutinas.nomRutina;
        cout << "Prohibicion 01 ";
        cin >> inforutinas.pro1;
        cout << "Prohibicion 02  ";
        cin >> inforutinas.pro2;
        cout << "Las prohibiciones ingresadas son simultaneas? (s/n) ";
        cin >> inforutinas.simultaneo;
        cout << "Horario de la rutina (am ='a', pm = 'p', ambas 'b') ";
        cin >> inforutinas.horario;

        gymdeath_rutinas.write((char*)&inforutinas,sizeof(rutina));
    }
    
    //Cierro el archivo y quedan los datos guardados
    gymdeath_rutinas.close();
  
    

    cout << endl << "\nIngrese cantidad de afiliados del gimnasio ";
    cin >> cantafi;
    
    
    //Ciclo para ingresar los datos x de los afiliados
    for(int i=0;i<cantafi;i++)
    {
        cout << endl << "\nCédula del afiliado " << i << " ";
        cin >> infoafiliados.cedula;
        cout << "\nNombre del afiliado ";
        cin >> infoafiliados.nombre;
        cout << "\nTelefono del afiliado ";
        cin >> infoafiliados.telefono;
        cout << "\nDireccion del afiliado  ";
        cin >> infoafiliados.direccion;
        cout << "\nCiudad del afiliado ";
        cin >> infoafiliados.ciudad;
        cout << "\nHorario del afiliado (am ='a', pm = 'p'): ";
        cin >> infoafiliados.horario;
        cout << "\nSexo del afiliado (f/m) ";
        cin >> infoafiliados.sexo;
        cout << "\nCantidad de rutinas que realiza el afiliado ";
        cin >> infoafiliados.cantrut;
        //Ciclo para almacenar los códigos de cada rutina que realiza el afiliado 
        for(int j=0;j<infoafiliados.cantrut;j++)
        {
          cout << "\nIngrese codigo de la rutina " << j << " que realiza el afiliado ";
          cin >> infoafiliados.coderut[j];
        }

        cout << "\nNombre pariente del afiliado ";
        cin >> infoafiliados.nomPariente;

        cout << endl << "\nHOJA CLINICA DE VALORIACION DEL AFILIADO " << i <<" ";
        cout << endl << "\nEstatura del afiliado ";
        cin >> infoafiliados.estatura;
        cout << "\nPeso del afiliado ";
        cin >> infoafiliados.peso;
        cout << "\nCantidad de meses que lleva afiliado ";
        cin >> infoafiliados.cantmeses;

        infoafiliados.cantmeseshoja=infoafiliados.cantmeses;
        //Ciclo para almacenar la informacion de la hoja de valoración del afiliado para cada mes que lleva en el gimnasio
        if(infoafiliados.cantmeseshoja<=12) //Si la cantidad de meses es menor o igual a 12 se guarda normal los datos en la matriz
        {
          for(int m=0;m<infoafiliados.cantmeses;m++)
          {
            cout << "\nIngrese presion arterial sistolica del afiliado en el mes " << m+1 << " ";
            cin >>infoafiliados.salud[0][m];
            cout << "\nIngrese presion arterial diastolica del afiliado en el mes " << m+1 << " ";
            cin >> infoafiliados.salud[1][m];
            cout << "\nIngrese valor de trigliceridos del afiliado en el mes " << m+1 << " ";
            cin >> infoafiliados.salud[2][m];
            cout << "\nIngrese valor de colesterol del afiliado en el mes " << m+1 << " ";
            cin >> infoafiliados.salud[3][m];
          }
        }
        else //Si la cantidad de meses es mayor a 12 
        {
          int a=0;
          indice=infoafiliados.cantmeses%12-1;
          for(int m=0;m<infoafiliados.cantmeses && a<=indice;m++)
          {   
            if(m<12)
            {
              cout << "\nIngrese presion arterial sistolica del afiliado en el mes " << m+1 << " ";
              cin >>infoafiliados.salud[0][m];
              cout << "\nIngrese presion arterial diastolica del afiliado en el mes " << m+1 << " ";
              cin >> infoafiliados.salud[1][m];
              cout << "\nIngrese valor de trigliceridos del afiliado en el mes " << m+1 << " ";
              cin >> infoafiliados.salud[2][m];
              cout << "\nIngrese valor de colesterol del afiliado en el mes " << m+1 << " ";
              cin >> infoafiliados.salud[3][m];
            }
            else //Se empiezan a reemplazar valores con el contador "a"
            {
                cout<<"\nIngrese presion arterial sistolica del afiliado en el mes "<<m+1<< " "; 
                cin>>infoafiliados.salud[0][a]; 
                cout << "\nIngrese presion arterial diastolica del afiliado en el mes " << m+1 << " ";
                cin >> infoafiliados.salud[1][a];
                cout << "\nIngrese valor de trigliceridos del afiliado en el mes " << m+1 << " ";
                cin >> infoafiliados.salud[2][a];
                cout << "\nIngrese valor de colesterol del afiliado en el mes " << m+1 << " ";
                cin >> infoafiliados.salud[3][a];
                a++;
            }   
          }
        }
        gymdeath_clientes.write((char*)&infoafiliados,sizeof(afiliado));
    }    
    //Cierro el archivo y quedan los datos guardados
    gymdeath_clientes.close();
}

void imprimir_todo (fstream &gymdeath_clientes, fstream &gymdeath_rutinas)//funcion opcion 1
{
  afiliado afiliados;//estructura afiliados para hacer el manejo de archivos
  rutina rutinas;//estructura rutinas para hacer el manejo de archivos
  int i=0, indice;//i para contador del cliente, indice para la hoja val. 
  int a=0, b=0;//para la hoja de valoracion, si ha estado mas de 12 meses

  cout<<"\nDATOS COMPLETOS DEL GIMNASIO";

  cout<<"\nCODIGO"<<setw(11)<<"NOMBRE"<<setw(17)<<"PROHIBICIONES"<<setw(15)<<"SIMULTANEO"<<setw(12)<<"HORARIO";//nombre de las columnas
  cout<<"\n-----------------------------------------------------------------------------\n"; //servira como lineas de separacion
  gymdeath_rutinas.read((char*) &rutinas, sizeof(rutina));//empieza a leer los datos hasta terminar el archivo 
  while(!gymdeath_rutinas.eof())
  {
    //imprime todo en una misma linea
    cout<<rutinas.cod;
    cout<<setw(17)<<rutinas.nomRutina;
    cout<<setw(11)<<rutinas.pro1;
    cout<<setw(15)<<rutinas.simultaneo;
    cout<<setw(15)<<rutinas.horario;
    cout<<endl<<setw(29)<<rutinas.pro2;//queremos que la segunda prohibicion se imprima una fila abajo, por eso se hace al final del ciclo. 
    cout<<"\n-----------------------------------------------------------------------------\n"; 
    gymdeath_rutinas.read((char*) &rutinas, sizeof(rutina)); 
  }
  gymdeath_rutinas.close(); 

  cout<<"\nDATOS COMPLETOS DE LOS AFILIADOS\n";//empieza a leer el archivo de afiliados
  gymdeath_clientes.read((char*) &afiliados, sizeof(afiliado));

  while(!gymdeath_clientes.eof())
  {
    cout<<"\n\nDATOS DEL AFILIADO "<<i+1<<endl;
    cout<<"Cedula: "<<afiliados.cedula<<endl;
    cout<<"Nombre: "<<afiliados.nombre<<endl;
    cout<<"Telefono: "<<afiliados.telefono<<endl;
    cout<<"Nombre del pariente de emergencia: "<<afiliados.nomPariente<<endl;
    cout<<"UBICACION\n"; 
    cout<<"Direccion: "<<afiliados.direccion<<endl;
    cout<<"Ciudad: "<<afiliados.ciudad<<endl;
    cout<<"Sexo: "<<afiliados.sexo<<endl;
    cout<<"Horario: "<<afiliados.horario<<endl;
    cout<<"Cantidad de rutinas que hace: "<<afiliados.cantrut<<endl;
    //va a imprimir las rutinas que se guardaron con base a la cantidad que se cuardo en la variable de cantrut en la estructura afiliados
      if(afiliados.cantrut>0)
      {
        for(int j=0; j<afiliados.cantrut; j++)
        {
          cout<<"\nRUTINA "<<j+1<<": "<<afiliados.coderut[j];
        }
      }
      else
      {
        cout<<"\nTodavia no tiene rutinas asignadas";//si es una filiado nuevo y no se han asignado rutinas todavia
      }

      cout<<"\n\nHOJA DE VALORACION\n"; 
      cout<<"\nCantidad de meses que lleva el afiliado: "<<afiliados.cantmeses; 
      cout<<"\nEstatura actual: "<<afiliados.estatura<<" m"; 
      cout<<"\nPeso actual: "<<afiliados.peso<<" kg\n"; 
      //Mira con que número empieza el índice en la impresion (maximo-su pocisión) Me sirve cuando sea mayor de 12
      indice=afiliados.cantmeseshoja-(afiliados.cantmeseshoja%12-1);

      cout<<"PRESION ARTERIAL SISTOLICA\n";//cada ciclo es para uno de los datos en la matriz
      if(afiliados.cantmeseshoja<=12)
      {
        for(int l=0; l<afiliados.cantmeseshoja; l++)
        {
          cout<<"MES "<<l+1<<": "<<afiliados.salud [0][l]<<endl;
        }
      }
      else
      {//cant meses hoja es para saber cuando modifica datos de la hoja de valoración presión, col,trig
      
      //AQUÍ NO SE MODIFICAN DATOS DE LA LISTA SOLO SE MODIFICA EL ÍNDICE ya que se habían modificado en la función 0 
        for(int l=0; l<=(afiliados.cantmeseshoja%12-1); l++) //Se imprimen los meses excedentes
        {
          cout<<"MES "<<indice+a<<": "<<afiliados.salud [0][l]<<endl;
          a++;
        }
        for(int l=afiliados.cantmeseshoja%12; l<12; l++) //Desde el mes siguiente 
        {
          //Se imprimen los meses normales con el índice cantmeses-12+1 y el b es para añadir uno
          cout<<"MES "<<afiliados.cantmeseshoja-12+b+1<<": "<<afiliados.salud [0][l]<<endl;
          b++;
        }
      }

      a=0; //se reinicia a y b para volver a hacer el proceso de suma del indice
      b=0; 
      cout<<"\nPRESION ARTERIAL DIASTOLICA\n";
      if(afiliados.cantmeseshoja<=12)
      {
        for(int m=0; m<afiliados.cantmeseshoja; m++)
        {
          cout<<"MES "<<m+1<<": "<<afiliados.salud [1][m]<<endl;
        }
      }
      else
      {
        for(int m=0; m<=(afiliados.cantmeseshoja%12-1); m++)
        {
          cout<<"MES "<<indice+a<<": "<<afiliados.salud[0][m]<<endl;
          a++;//no se suma como abajo en b 1. El indice no tiene en cuenta que la lista empieza en 0
        }
        for(int m=afiliados.cantmeseshoja%12; m<12; m++)
        {
          cout<<"MES "<<afiliados.cantmeseshoja-12+1+b<<": "<<afiliados.salud [0][m]<<endl;
          b++;
        }
      }

      a=0; 
      b=0;
      cout<<"\nTRIGLICERIDOS\n";
      if(afiliados.cantmeseshoja<=12)
      {
        for(int n=0; n<afiliados.cantmeseshoja; n++)
        {
          cout<<"MES "<<n+1<<": "<<afiliados.salud[2][n]<<endl;
        }
      }
      else
      {
        for(int n=0; n<=(afiliados.cantmeseshoja%12-1); n++)
        {
          cout<<"MES "<<indice+a<<": "<<afiliados.salud [0][n]<<endl;
          a++;
        }
        for(int n=afiliados.cantmeseshoja%12; n<12; n++)
        {
          cout<<"MES "<<afiliados.cantmeseshoja-12+1+b<<": "<<afiliados.salud [0][n]<<endl;
          b++;
        }
      }

      a=0; 
      b=0; 
      cout<<"\nCOLESTEROL\n";
      if(afiliados.cantmeseshoja<=12)
      {
        for(int o=0; o<afiliados.cantmeseshoja; o++)
        {
          cout<<"MES "<<o+1<<": "<<afiliados.salud [3][o]<<endl;
        }
      }
      else
      {
        for(int m=0; m<=(afiliados.cantmeseshoja%12-1); m++)
        {
          cout<<"MES "<<indice+a<<": "<<afiliados.salud [0][m]<<endl;
          a++;
        }
        for(int m=afiliados.cantmeseshoja%12; m<12; m++)
        {
          cout<<"MES "<<afiliados.cantmeseshoja-12+1+b<<": "<<afiliados.salud [0][m]<<endl;
          b++;
        }
      }
      gymdeath_clientes.read((char*) &afiliados, sizeof(afiliado));
      i++;//este es el que se va sumando cada vez que pasa un cliente
  }
  gymdeath_clientes.close();
}

//funcion opcion 2
void imprimir_mujer (fstream &gymdeath_clientes)
{
  afiliado afiliados;//estructura afiliados para hacer el manejo de archivos
  int i=0; 
  int a=0,b=0, indice;//lo mismo que en la funcion de arriba, para la hoja de valoracion
  bool femenino=false;//para saber si existen mujeres en el gimnasio
  
  cout<<"\nDATOS COMPLETOS DE AFILIADOS DE SEXO FEMENINO\n"; 
  gymdeath_clientes.read((char*)&afiliados, sizeof(afiliado));
  while(!gymdeath_clientes.eof())
  {
    if(afiliados.sexo=='f')//como es f para mujer solo con el if se garantiza imprimir ese genero
    {
      cout<<"\n\nDATOS DEL AFILIADO "<<i+1<<endl;
      cout<<"Cedula: "<<afiliados.cedula<<endl;
      cout<<"Nombre: "<<afiliados.nombre<<endl;
      cout<<"Telefono: "<<afiliados.telefono<<endl;
      cout<<"Nombre del pariente de emergencia: "<<afiliados.nomPariente<<endl;
      cout<<"UBICACION\n"; 
      cout<<"Direccion: "<<afiliados.direccion<<endl;
      cout<<"Ciudad: "<<afiliados.ciudad<<endl;
      cout<<"Sexo: "<<afiliados.sexo<<endl;
      cout<<"Horario: "<<afiliados.horario<<endl;
      cout<<"Cantidad de rutinas que hace: "<<afiliados.cantrut<<endl;
      
      if(afiliados.cantrut>0)
      {
        for(int j=0; j<afiliados.cantrut; j++)
        {
          cout<<"\nRUTINA "<<j+1<<": "<<afiliados.coderut[j];//va a imprimir las rutinas que se guardaron con base a la cantidad que se cuardo en la variable de cantrut en la estructura afiliados
        }
      }
      else
      {
        cout<<"\nTodavia no tiene rutinas asignadas";//si es una filiado nuevo y se decide imprimir las rutinas, si este no se han asignado, es logico imprimir esto
      }

      cout<<"\n\nHOJA DE VALORACION\n"; 
      cout<<"\nCantidad de meses que lleva el afiliado: "<<afiliados.cantmeses; 
      cout<<"\nEstatura actual: "<<afiliados.estatura<<" m"; 
      cout<<"\nPeso actual: "<<afiliados.peso<<" kg\n"; 
      
      indice=afiliados.cantmeseshoja-(afiliados.cantmeseshoja%12-1);

      cout<<"PRESION ARTERIAL SISTOLICA\n";//cada ciclo es para uno de los datos en la matriz
      if(afiliados.cantmeseshoja<=12)
      {
        for(int l=0; l<afiliados.cantmeseshoja; l++)
        {
          cout<<"MES "<<l+1<<": "<<afiliados.salud [0][l]<<endl;
        }
      }
      else
      { 
        for(int l=0; l<=(afiliados.cantmeseshoja%12-1); l++)
        {
          cout<<"MES "<<indice+a<<": "<<afiliados.salud [0][l]<<endl;
          a++;
        }
        for(int l=afiliados.cantmeseshoja%12; l<12; l++)
        {
          cout<<"MES "<<afiliados.cantmeseshoja-12+b+1<<": "<<afiliados.salud [0][l]<<endl;
          b++;
        }
      }

      a=0; 
      b=0; 
      cout<<"\nPRESION ARTERIAL DIASTOLICA\n";
      if(afiliados.cantmeseshoja<=12)
      {
        for(int m=0; m<afiliados.cantmeseshoja; m++)
        {
          cout<<"MES "<<m+1<<": "<<afiliados.salud [1][m]<<endl;
        }
      }
      else
      {
        for(int m=0; m<=(afiliados.cantmeseshoja%12-1); m++)
        {
          cout<<"MES "<<indice+a<<": "<<afiliados.salud[0][m]<<endl;
          a++;
        }
        for(int m=afiliados.cantmeseshoja%12; m<12; m++)
        {
          cout<<"MES "<<afiliados.cantmeseshoja-12+1+b<<": "<<afiliados.salud [0][m]<<endl;
          b++;
        }
      }

      a=0; 
      b=0;
      cout<<"\nTRIGLICERIDOS\n";
      if(afiliados.cantmeseshoja<=12)
      {
        for(int n=0; n<afiliados.cantmeseshoja; n++)
        {
          cout<<"MES "<<n+1<<": "<<afiliados.salud[2][n]<<endl;
        }
      }
      else
      {
        for(int n=0; n<=(afiliados.cantmeseshoja%12-1); n++)
        {
          cout<<"MES "<<indice+a<<": "<<afiliados.salud [0][n]<<endl;
          a++;
        }
        for(int n=afiliados.cantmeseshoja%12; n<12; n++)
        {
          cout<<"MES "<<afiliados.cantmeseshoja-12+1+b<<": "<<afiliados.salud [0][n]<<endl;
          b++;
        }
      }

      a=0; 
      b=0; 
      cout<<"\nCOLESTEROL\n";
      if(afiliados.cantmeseshoja<=12)
      {
        for(int o=0; o<afiliados.cantmeseshoja; o++)
        {
          cout<<"MES "<<o+1<<": "<<afiliados.salud [3][o]<<endl;
        }
      }
      else
      {
        for(int m=0; m<=(afiliados.cantmeseshoja%12-1); m++)
        {
          cout<<"MES "<<indice+a<<": "<<afiliados.salud [0][m]<<endl;
          a++;
        }
        for(int m=afiliados.cantmeseshoja%12; m<12; m++)
        {
          cout<<"MES "<<afiliados.cantmeseshoja-12+1+b<<": "<<afiliados.salud [0][m]<<endl;
          b++;
        }
      }
      femenino=true;//como existe por lo menos una mujer, se cambia a verdadero
      i++;
    }
    gymdeath_clientes.read((char*) &afiliados, sizeof(afiliado));
  } 
  gymdeath_clientes.close();
  if(!femenino)
  {
    cout<<"\nNo hay afiliados del sexo femenino";//Dado el caso de que no hayan afiliados del sexo femenino, se imprimira este mensaje, por ello se usa el booleano sexo femenino
  }
}

void imprimir_hombre(fstream &gymdeath_clientes)//funcion opcion 3
{
  cout<<"\nDATOS COMPLETOS DE AFILIADOS DE SEXO MASCULINO\n"; 
  afiliado afiliados;
  int i=0; //Para decir el numero del afiliado
  int a=0, b=0, indice;  
  bool masculino=false;//dado el caso de que no hayan hombres en el gimnasio

  gymdeath_clientes.read((char*) &afiliados, sizeof(afiliado));
  while(!gymdeath_clientes.eof())
  {
    if(afiliados.sexo=='m')//se pone el if si es igual a m porque con ese caracter repreenta el sexo masculino
    {
      cout<<"\n\nDATOS DEL AFILIADO "<<i+1<<endl;
      cout<<"Cedula: "<<afiliados.cedula<<endl;
      cout<<"Nombre: "<<afiliados.nombre<<endl;
      cout<<"Telefono: "<<afiliados.telefono<<endl;
      cout<<"Nombre del pariente de emergencia: "<<afiliados.nomPariente<<endl;
      cout<<"UBICACION"; 
      cout<<"Direccion: "<<afiliados.direccion<<endl;
      cout<<"Ciudad: "<<afiliados.ciudad<<endl;
      cout<<"Sexo (m/f): "<<afiliados.sexo<<endl;
      cout<<"Horario(a/p): "<<afiliados.horario<<endl;
      cout<<"Cantidad de rutinas que hace: "<<afiliados.cantrut<<endl;
      if(afiliados.cantrut>0)
      {
       for(int j=0; j<afiliados.cantrut; j++)
       {
        cout<<"\nRUTINA "<<j+1<<": "<<afiliados.coderut[j];//va a imprimir las rutinas que se guardaron con base a la cantidad que se cuardo en la variable de cantrut en la estructura afiliados
       }
      }
      else
      {
       cout<<"\nTodavia no tiene rutinas asignadas";//si es una filiado nuevo y se decide imprimir las rutinas, si este no se han asignado, es logico imprimir esto
      }

      cout<<"\n\nHOJA DE VALORACION\n"; 
      cout<<"\nCantidad de meses que lleva el afiliado: "<<afiliados.cantmeses; 
      cout<<"\nEstatura actual: "<<afiliados.estatura<<" m"; 
      cout<<"\nPeso actual: "<<afiliados.peso<<" kg\n"; 
      
      indice=afiliados.cantmeseshoja-(afiliados.cantmeseshoja%12-1);
      cout<<"PRESION ARTERIAL SISTOLICA\n";//cada ciclo es para uno de los datos en la matriz
      if(afiliados.cantmeseshoja<=12)
      {
        for(int l=0; l<afiliados.cantmeseshoja; l++)
        {
          cout<<"MES "<<l+1<<": "<<afiliados.salud [0][l]<<endl;
        }
      }
      else
      { 
        for(int l=0; l<=(afiliados.cantmeseshoja%12-1); l++)
        {
          cout<<"MES "<<indice+a<<": "<<afiliados.salud [0][l]<<endl;
          a++;
        }
        for(int l=afiliados.cantmeseshoja%12; l<12; l++)
        {
          cout<<"MES "<<afiliados.cantmeseshoja-12+b+1<<": "<<afiliados.salud [0][l]<<endl;
          b++;
        }
      }

      a=0; 
      b=0; 
      cout<<"\nPRESION ARTERIAL DIASTOLICA\n";
      if(afiliados.cantmeseshoja<=12)
      {
        for(int m=0; m<afiliados.cantmeseshoja; m++)
        {
          cout<<"MES "<<m+1<<": "<<afiliados.salud [1][m]<<endl;
        }
      }
      else
      {
        for(int m=0; m<=(afiliados.cantmeseshoja%12-1); m++)
        {
          cout<<"MES "<<indice+a<<": "<<afiliados.salud[0][m]<<endl;
          a++;
        }
        for(int m=afiliados.cantmeseshoja%12; m<12; m++)
        {
          cout<<"MES "<<afiliados.cantmeseshoja-12+1+b<<": "<<afiliados.salud [0][m]<<endl;
          b++;
        }
      }

      a=0; 
      b=0;
      cout<<"\nTRIGLICERIDOS\n";
      if(afiliados.cantmeseshoja<=12)
      {
        for(int n=0; n<afiliados.cantmeseshoja; n++)
        {
          cout<<"MES "<<n+1<<": "<<afiliados.salud[2][n]<<endl;
        }
      }
      else
      {
        for(int n=0; n<=(afiliados.cantmeseshoja%12-1); n++)
        {
          cout<<"MES "<<indice+a<<": "<<afiliados.salud [0][n]<<endl;
          a++;
        }
        for(int n=afiliados.cantmeseshoja%12; n<12; n++)
        {
          cout<<"MES "<<afiliados.cantmeseshoja-12+1+b<<": "<<afiliados.salud [0][n]<<endl;
          b++;
        }
      }

      a=0; 
      b=0; 
      cout<<"\nCOLESTEROL\n";
      if(afiliados.cantmeseshoja<=12)
      {
        for(int o=0; o<afiliados.cantmeseshoja; o++)
        {
          cout<<"MES "<<o+1<<": "<<afiliados.salud [3][o]<<endl;
        }
      }
      else
      {
        for(int m=0; m<=(afiliados.cantmeseshoja%12-1); m++)
        {
          cout<<"MES "<<indice+a<<": "<<afiliados.salud [0][m]<<endl;
          a++;
        }
        for(int m=afiliados.cantmeseshoja%12; m<12; m++)
        {
          cout<<"MES "<<afiliados.cantmeseshoja-12+1+b<<": "<<afiliados.salud [0][m]<<endl;
          b++;
        }
      }
     masculino=true;
     i++; 
    } 
   gymdeath_clientes.read((char*) &afiliados, sizeof(afiliado));
  }
  gymdeath_clientes.close();
  if(!masculino)
  {
    cout<<"\nNo hay afiliados del sexo masculino";//Dado el caso de que no hayan afiliados del sexo masculino, se imprimira este mensaje, por ello se usa el booleano sexo fmasculino
  } 
}

//funcion opcion 4
void imprimir_Aficonrutina(fstream &gymdeath_clientes, fstream &gymdeath_rutinas)
{
  int rutinabuscar;
  //Variable para saber si existe una rutina con el código ingresado
  bool existe_rut, tienerut,hayaficonrut;
  hayaficonrut=false;
  existe_rut=false;
  tienerut=false;
  afiliado afiliados;
  rutina rutinas;

  cout << "Ingrese codigo de la rutina que desea buscar ";
  cin >> rutinabuscar;

  cout<<"\nDATOS COMPLETOS DE AFILIADOS DE QUE REALIZAN LA RUTINA " << rutinabuscar << "\n";

  //Se leen los datos del archivo de rutinas para verifica que exista una rutina con el código ingresado 
  gymdeath_rutinas.read((char*) &rutinas, sizeof(rutina));

  while(!gymdeath_rutinas.eof() && existe_rut==false)
    {
      if(rutinas.cod==rutinabuscar)
      {
        existe_rut=true;
      }
      gymdeath_rutinas.read((char*) &rutinas, sizeof(rutina));
    }
    
    gymdeath_rutinas.close();
    
    if(!existe_rut)
    {
      cout<<"\nNo existe ninguna rutina con el codigo ingresado";
    }
    
    else if(existe_rut)
    {
      gymdeath_clientes.seekg(0,ios::beg);
      gymdeath_clientes.read((char*) &afiliados, sizeof(afiliado));
     
      while(!gymdeath_clientes.eof() && tienerut==false)
      {
        for(int j=0; j<afiliados.cantrut; j++)
          {
            if(afiliados.coderut[j]==rutinabuscar)
            {
              tienerut=true;
            }
          }
        
        if(tienerut)
        {
          cout<<"\n\nDATOS DEL AFILIADO "<< endl;
          cout<<"Cedula: "<<afiliados.cedula<<endl;
          cout<<"Nombre: "<<afiliados.nombre<<endl;
          cout<<"Telefono: "<<afiliados.telefono<<endl;
          cout<<"Nombre del pariente de emergencia: "<<afiliados.nomPariente<<endl;
          cout<<"UBICACION"; 
          cout<<"Direccion: "<<afiliados.direccion<<endl;
          cout<<"Ciudad: "<<afiliados.ciudad<<endl;
          cout<<"Sexo: "<<afiliados.sexo<<endl;
          cout<<"Horario: "<<afiliados.horario<<endl;
          cout<<"Cantidad de rutinas que hace: "<<afiliados.cantrut<<endl;

          for(int j=0; j<afiliados.cantrut; j++)
          {
            cout<<"\nRUTINA "<<j+1<<": "<<afiliados.coderut[j];
          }

          cout<<"\n\nHOJA DE VALORACION\n"; 

          cout<<"\nCantidad de meses que lleva el afiliado: "<<afiliados.cantmeses; 

          cout<<"\nEstatura actual: "<<afiliados.estatura<<" m"; 
    
          cout<<"\nPeso actual: "<<afiliados.peso<<" kg\n"; 

          cout<<"PRESION ARTERIAL SISTOLICA\n";
          //cada ciclo es para uno de los datos en la matriz
          for(int l=0; l<afiliados.cantmeses; l++)
          {
              //el de las filas ya se sabe porque es el dato, por eso esta con un numero dado
            cout<<"MES "<<l+1<<": "<<afiliados.salud [0][l]<<endl;
          }

          cout<<"\nPRESION ARTERIAL DIASTOLICA\n";
          for(int m=0; m<afiliados.cantmeses; m++)
          {
            cout<<"MES "<<m+1<<": "<<afiliados.salud [1][m]<<endl;
          }

          cout<<"\nTRIGLICERIDOS\n";
          for(int n=0; n<afiliados.cantmeses; n++)
          {
            cout<<"MES "<<n+1<<": "<<afiliados.salud [2][n]<<endl;
          }

          cout<<"\nCOLESTEROL\n";
          for(int o=0; o<afiliados.cantmeses; o++)
          {
            cout<<"MES "<<o+1<<": "<<afiliados.salud [3][o]<<endl;
          } 

          hayaficonrut=true;
          tienerut=false;
        }

        gymdeath_clientes.read((char*) &afiliados, sizeof(afiliado));
          
      }
    
    if(!hayaficonrut)
    {
      cout<<"\nNo hay afiliados con la rutina ingresada";
    }
  }
    gymdeath_clientes.close();
}

//Función 5 
void cambio_horario(fstream &gymdeath_clientes)
{
  cout<<"\nDATOS COMPLETOS DE AFILIADOS AFECTADOS POR EL CAMBIO DE HORARIO DE LA RUTINA CARDIO\n"; 
  afiliado afiliados;
  int i=0; //Para decir el numero del afiliado
  int a=0, b=0, indice;  
  bool afectado=false;//dado el caso de que no hayan afiliados afectados por el cambio

  gymdeath_clientes.read((char*) &afiliados, sizeof(afiliado));
  while(!gymdeath_clientes.eof())
  {
    for(int h=0;h<afiliados.cantrut;h++)
    {
      if(afiliados.coderut[h]==4&&afiliados.horario=='p')//Si el afiliado realiza la rutina de cardio con código 4 y su horario era am se imprimen sus datos 
        {
          cout<<"\n\nDATOS DEL AFILIADO "<<i+1<<endl;
          cout<<"Cedula: "<<afiliados.cedula<<endl;
          cout<<"Nombre: "<<afiliados.nombre<<endl;
          cout<<"Telefono: "<<afiliados.telefono<<endl;
          cout<<"Nombre del pariente de emergencia: "<<afiliados.nomPariente<<endl;
          cout<<"UBICACION" << endl; 
          cout<<"Direccion: "<<afiliados.direccion<<endl;
          cout<<"Ciudad: "<<afiliados.ciudad<<endl;
          cout<<"Sexo (m/f): "<<afiliados.sexo<<endl;
          cout<<"Horario(a/p): "<<afiliados.horario<<endl;
          cout<<"Cantidad de rutinas que hace: "<<afiliados.cantrut<<endl;
          if(afiliados.cantrut>0)
          {
          for(int j=0; j<afiliados.cantrut; j++)
          {
            cout<<"\nRUTINA "<<j+1<<": "<<afiliados.coderut[j];//va a imprimir las rutinas que se guardaron con base a la cantidad que se cuardo en la variable de cantrut en la estructura afiliados
          }
          }
          else
          {
          cout<<"\nTodavia no tiene rutinas asignadas";//si es una filiado nuevo y se decide imprimir las rutinas, si este no se han asignado, es logico imprimir esto
          }

          cout<<"\n\nHOJA DE VALORACION\n"; 
          cout<<"\nCantidad de meses que lleva el afiliado: "<<afiliados.cantmeses; 
          cout<<"\nEstatura actual: "<<afiliados.estatura<<" m"; 
          cout<<"\nPeso actual: "<<afiliados.peso<<" kg\n"; 
          
          indice=afiliados.cantmeseshoja-(afiliados.cantmeseshoja%12-1);
          cout<<"PRESION ARTERIAL SISTOLICA\n";//cada ciclo es para uno de los datos en la matriz
          if(afiliados.cantmeseshoja<=12)
          {
            for(int l=0; l<afiliados.cantmeseshoja; l++)
            {
              cout<<"MES "<<l+1<<": "<<afiliados.salud [0][l]<<endl;
            }
          }
          else
          { 
            for(int l=0; l<=(afiliados.cantmeseshoja%12-1); l++)
            {
              cout<<"MES "<<indice+a<<": "<<afiliados.salud [0][l]<<endl;
              a++;
            }
            for(int l=afiliados.cantmeseshoja%12; l<12; l++)
            {
              cout<<"MES "<<afiliados.cantmeseshoja-12+b+1<<": "<<afiliados.salud [0][l]<<endl;
              b++;
            }
          }

          a=0; 
          b=0; 
          cout<<"\nPRESION ARTERIAL DIASTOLICA\n";
          if(afiliados.cantmeseshoja<=12)
          {
            for(int m=0; m<afiliados.cantmeseshoja; m++)
            {
              cout<<"MES "<<m+1<<": "<<afiliados.salud [1][m]<<endl;
            }
          }
          else
          {
            for(int m=0; m<=(afiliados.cantmeseshoja%12-1); m++)
            {
              cout<<"MES "<<indice+a<<": "<<afiliados.salud[0][m]<<endl;
              a++;
            }
            for(int m=afiliados.cantmeseshoja%12; m<12; m++)
            {
              cout<<"MES "<<afiliados.cantmeseshoja-12+1+b<<": "<<afiliados.salud [0][m]<<endl;
              b++;
            }
          }

          a=0; 
          b=0;
          cout<<"\nTRIGLICERIDOS\n";
          if(afiliados.cantmeseshoja<=12)
          {
            for(int n=0; n<afiliados.cantmeseshoja; n++)
            {
              cout<<"MES "<<n+1<<": "<<afiliados.salud[2][n]<<endl;
            }
          }
          else
          {
            for(int n=0; n<=(afiliados.cantmeseshoja%12-1); n++)
            {
              cout<<"MES "<<indice+a<<": "<<afiliados.salud [0][n]<<endl;
              a++;
            }
            for(int n=afiliados.cantmeseshoja%12; n<12; n++)
            {
              cout<<"MES "<<afiliados.cantmeseshoja-12+1+b<<": "<<afiliados.salud [0][n]<<endl;
              b++;
            }
          }

          a=0; 
          b=0; 
          cout<<"\nCOLESTEROL\n";
          if(afiliados.cantmeseshoja<=12)
          {
            for(int o=0; o<afiliados.cantmeseshoja; o++)
            {
              cout<<"MES "<<o+1<<": "<<afiliados.salud [3][o]<<endl;
            }
          }
          else
          {
            for(int m=0; m<=(afiliados.cantmeseshoja%12-1); m++)
            {
              cout<<"MES "<<indice+a<<": "<<afiliados.salud [0][m]<<endl;
              a++;
            }
            for(int m=afiliados.cantmeseshoja%12; m<12; m++)
            {
              cout<<"MES "<<afiliados.cantmeseshoja-12+1+b<<": "<<afiliados.salud [0][m]<<endl;
              b++;
            }
          }
        afectado=true;
        i++; 
      } 

    }

    gymdeath_clientes.read((char*) &afiliados, sizeof(afiliado));
  } 
  if(!afectado)
  {
    cout<<"\nNo hay afiliados afectados por el cambio en el horario de la rutina CARDIO";//Dado el caso de que no hayan afiliados afectados se imprime el aviso
  }
gymdeath_clientes.close();
}

//funcion opcion 6
void nuevoAfiliado(fstream &gymdeath_clientes)
{
  afiliado afiliados; 
  int cedula;
  char respuesta; 
  bool encontrado=false; 

  cout<<"\nINGRESO DE DATOS DEL AFILIADO NUEVO: \n"; 
 
  do//por lo menos una vez se debe pedir
  {
    cout<<"Cedula del nuevo afiliado: "; 
    cin>>cedula;
    cout<<endl;
    gymdeath_clientes.read((char*) &afiliados, sizeof(afiliado));
    //este while es para saber si la cedula existe
    while((!gymdeath_clientes.eof()) && (!encontrado)) 
    {
      if(cedula==afiliados.cedula)
      {
        encontrado=true; 
      }
      gymdeath_clientes.read((char*) &afiliados, sizeof(afiliado));
    }

    //si es veradero existe
    if(encontrado)
    {
      cout<<"\nNo puede ser cliente nuevo porque la cedula ya existe."; 
      cout<<"\nDesea intentar ingresar otra cedula? (s/n)";
      cin>>respuesta; 
      encontrado=false; 
    }
    else
    {
      gymdeath_clientes.close(); 
      gymdeath_clientes.open("datos_clientes.dat", ios::binary| ios::app); //se cierra el archivo para que se abra abajo con append
      if(!gymdeath_clientes)
      {
        cout<<"no se pudo abrir de salida el archivo"; 
      }
      else
      {
        cout<<"\n\nDATOS DEL AFILIADO NUEVO "<<endl;
        respuesta='n';//se pone respuesta en n para terminar el ciclo y que el ultimo if no sirva
        cout<<"Cedula: "<<cedula; 
        afiliados.cedula=cedula;
        cout<<"\nNombre: "; 
        cin>>afiliados.nombre;
        cout<<"\nTelefono: "; 
        cin>>afiliados.telefono;
        cout<<"\nUBICACION"; 
        cout<<"\nDireccion: "; 
        cin>>afiliados.direccion;
        cout<<"\nCiudad: "; 
        cin>>afiliados.ciudad;
        cout<<"\nSexo (f/m): "; 
        cin>>afiliados.sexo;
        cout<<"\nHorario (am ='a', pm = 'p'): "; 
        cin>>afiliados.horario;
        cout<<"\nCantidad de rutinas que hace: 0 (por el momento)\n"; 
        afiliados.cantrut=0; //se establece en 0 porque no se le han adignado rutinas
        cout<<"\nNombre del pariente de emergencia: "; 
        cin>>afiliados.nomPariente;
        cout<<"\n\nHOJA DE VALORACION\n";   
        cout<<"\nCantidad de meses que lleva el afiliado: 1\n";
        afiliados.cantmeses=1; //ya se sabe que es su primer mes asi que se establce de una
        afiliados.cantmeseshoja=1;
        cout<<"\nEstatura actual: "; 
        cin>>afiliados.estatura; 
        cout<<"\nPeso actual: "; 
        cin>>afiliados.peso; 
  
        cout<<"\nPRESION ARTERIAL SISTOLICA\n";//cada ciclo es para uno de los datos en la matriz
        for(int l=0; l<afiliados.cantmeseshoja; l++)
        {     
          cout<<"\nMES "<<l+1<<": "; //el de las filas ya se sabe porque es el dato, por eso esta con un numero dado
          cin>>afiliados.salud [0][l];
        }
        cout<<"\nPRESION ARTERIAL DIASTOLICA\n";
        for(int m=0; m<afiliados.cantmeseshoja; m++)
        {
          cout<<"\nMES "<<m+1<<": "; 
          cin>>afiliados.salud [1][m];
        }
        cout<<"\nTRIGLICERIDOS\n";
        for(int n=0; n<afiliados.cantmeseshoja; n++)
        {
          cout<<"\nMES "<<n+1<<": "; 
          cin>>afiliados.salud [2][n];
        }
        cout<<"\nCOLESTEROL\n";
        for(int o=0; o<afiliados.cantmeseshoja; o++)
        {
          cout<<"\nMES "<<o+1<<": "; 
          cin>>afiliados.salud [3][o];
        }
        gymdeath_clientes.write((char*) &afiliados, sizeof(afiliado));//se graba al final del archivo el afiliado nuevo
      }
    }

    if(respuesta=='s')
    {  
      gymdeath_clientes.close();
      gymdeath_clientes.open("datos_clientes.dat", ios::binary| ios::in); 
      if(!gymdeath_clientes)
      {
        cout<<"no se pudo abrir de salida el archivo"; 
      }
    }
  }while(respuesta=='s');  
  gymdeath_clientes.close();//se termina el app y se cierra el archivo
}

//funcion opcion 7
void programar_rutina(fstream&gymdeath_clientes,fstream&gymdeath_rutinas)
{
  int cedula_asignar;
  char continuar;
  afiliado afiliados;
  rutina rutinas;
  char puede;
  int pos;
  bool hallado;
  bool encontrado;

  do{
    continuar='n';

    cout << "Ingrese la cedula del afiliado al que se le desea programar la(s) rutinas ";
    cin >> cedula_asignar;

    gymdeath_clientes.read((char*)&afiliados,sizeof(afiliado));

    hallado=false;
    encontrado=false;

    //Buscar la cedula ingresada y ver si corresponde a alguno de los afiliados
    while(!gymdeath_clientes.eof()&&!hallado)
    {
      //Contador para guardar los codigos de las rutinas que el afiliado pueda hacer en el arreglo coderut
      int s=0;
          //Si se encuentra la cedula y la cantidad de rutinas del afiliado es 0 se llama a la funcion prohibiciones
      if(afiliados.cedula==cedula_asignar)
      {
        hallado=true;
        pos=gymdeath_clientes.tellg(); //Guarda pocisión para determinar el registro a modifica
        
        if(afiliados.cantrut==0)
        { 
          encontrado=true;
                 
          int j=0;
           //SE EVALÚAN LAS PROHIBICIONES DE CADA RUTINA PARA VER SI EL AFILIADO CUMPLE CON ALGUNA
           if(afiliados.peso/(afiliados.estatura*afiliados.estatura)>=25)
           {
             afiliados.prohibiciones[j]='a';
             j++;
           }
           if(afiliados.peso/(afiliados.estatura*afiliados.estatura)<18.5)
           {
             afiliados.prohibiciones[j]='b';
             j++;
           }
          //  sistólica diastólica
           if(afiliados.salud[0][0]>=140&&afiliados.salud[1][0]>=90)
           {
             afiliados.prohibiciones[j]='p';
             j++;
           }
           //Trigliceridos
           if(afiliados.salud[2][0]>199)
           {
             afiliados.prohibiciones[j]='t';
             j++;
           }
           if(afiliados.salud[3][0]>240)
           {
             afiliados.prohibiciones[j]='c';
             j++;
           }
           afiliados.cantprohibicion=j;

          //Inicio lectura de rutinas para comparar las prohibiciones de cada una con las del afiliado que se está evaluando 
          gymdeath_rutinas.read((char*)&rutinas,sizeof(rutina));
          

          cout << "Las rutinas que el afiliado puede realizar son: ";

          while(!gymdeath_rutinas.eof())
          {
            //Si el horario de la rutina no es am y pm y es diferente al del afiliado automáticamente no se le puede asignar
            if(rutinas.horario!=afiliados.horario && rutinas.horario!='b')
            {
              puede='n';
            }
            //Si el horario de la rutina es igual al del afiliado o la rutina se hace en los dos horarios se evalúan las prohibiciones 
            else if (rutinas.horario==afiliados.horario||rutinas.horario=='b')
            {
              //Si solo tiene una prohibicion la rutina 
              if(rutinas.pro1 !='x' && rutinas.pro2 =='x')
              {
                puede='s';
                for(int i=0;i<afiliados.cantprohibicion;i++)
                {
                  if(rutinas.pro1==afiliados.prohibiciones[i])
                  {
                    puede='n';
                  }
                }    
              }
              //Si tiene dos prohibiciones
              else if(rutinas.pro1!='x'&& rutinas.pro2!='x')
              {
                puede='s';
                //Si las prohibiciones son simultaneas solo se 
                if(rutinas.simultaneo=='s')
                {
                  for(int i=0;i<afiliados.cantprohibicion;i++)
                  {
                    if(rutinas.pro1==afiliados.prohibiciones[i])
                    {
                      for(int h=0;h<afiliados.cantprohibicion;h++)
                      {
                        if(rutinas.pro2==afiliados.prohibiciones[h])
                        {
                          puede='n';
                        }
                      }
                    }
                  }
                }
                else if (rutinas.simultaneo=='n')
                {
                  puede='s';
                  for(int i=0;i<afiliados.cantprohibicion;i++)
                  {
                    if(rutinas.pro1==afiliados.prohibiciones[i] || rutinas.pro2 == afiliados.prohibiciones[i])
                    {
                      puede='n';
                    }
                  }
                }
              }
            }
            
            //Se evalúa si puede hacer la rutina o no 
            if(puede=='s')
            {
              afiliados.coderut[s]=rutinas.cod;
              cout << endl << rutinas.nomRutina;
              s++; 
            }

            //Leer la siguiente rutina
            gymdeath_rutinas.read((char*)&rutinas,sizeof(rutina));
          
          }
          afiliados.cantrut=s;
          if(s==0)
          {
            cout << "NINGUNA";
          } 
            //POCISIONO EL APUNTADOR DE ESCRITURA EN LA POCISIÓN -1 DE DONDE QUEDO 
          gymdeath_clientes.seekp(pos-(int)sizeof(afiliado),ios::beg);
          gymdeath_clientes.write((char*)&afiliados,sizeof(afiliado));
        }
        else 
        {
          cout << endl << "INVÁLIDO. La cédula ingresada corresponde a un afiliado que  ya tiene una programación de rutinas establecida. Desea ingresar otra cédula? (s/n)";
          cin >> continuar; 
          if(continuar=='s')
          {  //para volver a empezar desde 0
             gymdeath_clientes.close();
             gymdeath_clientes.open("datos_clientes.dat", ios::binary| ios::in|ios::out);
          }
        }
      }
      if(!encontrado)
      {
        gymdeath_clientes.read((char*)&afiliados,sizeof(afiliado));
      }
    }

    if (!hallado)
      {
        cout << "La cédula no existe en el sistema. Desea ingresar una nueva? (s/n) ";
        cin>>continuar;
        if(continuar=='s')
          {  //para volver a empezar desde 0
             gymdeath_clientes.close();
             gymdeath_clientes.open("datos_clientes.dat", ios::binary| ios::in|ios::out);
          }
      }

  } while ( (hallado == false || encontrado==false) && continuar == 's');

    gymdeath_clientes.close();
    gymdeath_rutinas.close();
}

//funcion opcion 8
void modifica_hojaval(fstream &gymdeath_clientes)
{
   int cedula, posicion, posicion2;//posicion es para saber donde se termino de leer el archivo //posicion2 es para saber lo del reemplazo
   afiliado afiliados;
   char respuesta='s';//la inicio con s para que funcione el if de respuesta grande
   bool encontrado=false;  
   int indice, a=0, b=0; 
   
   cout<<"\nMODIFICACION DE HOJA DE VALORACION\n"; 
   do
   {
     cout<<"\n\nPor favor ingrese la cedula del afiliado que desea ingresar: "; 
     cin>>cedula; 
     gymdeath_clientes.read((char*) &afiliados, sizeof(afiliado));
     while(!gymdeath_clientes.eof())//while para buscar y encontrar la cedula
     {
      if(cedula==afiliados.cedula)
      {
        encontrado=true;  //la encontro
        posicion=gymdeath_clientes.tellg();//si la encuentra guarda la posicion
        cout<<"\nDatos del cliente "<<afiliados.nombre<<" con cedula "<<cedula<<" presenta los siguientes datos: "; 
        cout<<"\nMeses que ha estado en el gimnasio: "<<afiliados.cantmeses;
        cout<<"\nEstatura actual: "<<afiliados.estatura<<" m"; 
        cout<<"\nPeso actual: "<<afiliados.peso<<" kg\n"; 
        
        indice=afiliados.cantmeseshoja-(afiliados.cantmeseshoja%12-1);

        cout<<"PRESION ARTERIAL SISTOLICA\n"; //cada ciclo es para uno de los datos en la matriz
        if(afiliados.cantmeseshoja<=12)
        {
          for(int l=0; l<afiliados.cantmeseshoja; l++)
          {
            cout<<"MES "<<l+1<<": "<<afiliados.salud [0][l]<<endl;
          }
        }
        else
        { 
          for(int l=0; l<=(afiliados.cantmeseshoja%12-1); l++)
          {
            cout<<"MES "<<indice+a<<": "<<afiliados.salud [0][l]<<endl;
            a++;
          }
          for(int l=afiliados.cantmeseshoja%12; l<12; l++)
          {
            cout<<"MES "<<afiliados.cantmeseshoja-12+b+1<<": "<<afiliados.salud [0][l]<<endl;
            b++;
          }
        }

        a=0; 
        b=0; 
        cout<<"\nPRESION ARTERIAL DIASTOLICA\n";
        if(afiliados.cantmeseshoja<=12)
        {
          for(int m=0; m<afiliados.cantmeseshoja; m++)
          {
            cout<<"MES "<<m+1<<": "<<afiliados.salud [1][m]<<endl;
          }
        }
        else
        {
          for(int m=0; m<=(afiliados.cantmeseshoja%12-1); m++)
          {
            cout<<"MES "<<indice+a<<": "<<afiliados.salud[0][m]<<endl;
            a++;
          }
          for(int m=afiliados.cantmeseshoja%12; m<12; m++)
          {
            cout<<"MES "<<afiliados.cantmeseshoja-12+1+b<<": "<<afiliados.salud [0][m]<<endl;
            b++;
          }
        }

        a=0; 
        b=0;
        cout<<"\nTRIGLICERIDOS\n";
        if(afiliados.cantmeseshoja<=12)
        {
          for(int n=0; n<afiliados.cantmeseshoja; n++)
          {
            cout<<"MES "<<n+1<<": "<<afiliados.salud[2][n]<<endl;
          }
        }
        else
        {
          for(int n=0; n<=(afiliados.cantmeseshoja%12-1); n++)
          {
            cout<<"MES "<<indice+a<<": "<<afiliados.salud [0][n]<<endl;
            a++;
          }
          for(int n=afiliados.cantmeseshoja%12; n<12; n++)
          {
            cout<<"MES "<<afiliados.cantmeseshoja-12+1+b<<": "<<afiliados.salud [0][n]<<endl;
            b++;
          }
        }

        a=0; 
        b=0; 
        cout<<"\nCOLESTEROL\n";
        if(afiliados.cantmeseshoja<=12)
        {
          for(int o=0; o<afiliados.cantmeseshoja; o++)
          {
             cout<<"MES "<<o+1<<": "<<afiliados.salud [3][o]<<endl;
          }
        }
        else
        {
          for(int m=0; m<=(afiliados.cantmeseshoja%12-1); m++)
          {
            cout<<"MES "<<indice+a<<": "<<afiliados.salud [0][m]<<endl;
            a++;
          }
          for(int m=afiliados.cantmeseshoja%12; m<12; m++)
          {
            cout<<"MES "<<afiliados.cantmeseshoja-12+1+b<<": "<<afiliados.salud [0][m]<<endl;
            b++;
          }
        }

        cout<<"\nDesea cambiar el valor de la estatura del afiliado (s/n)? "; 
        cin>>respuesta; 
        if(respuesta=='s')
        {
          cout<<"\nIngrese el nuevo valor: "; 
          cin>>afiliados.estatura; 
        }
        cout<<"\nDesea cambiar el valor del peso del afiliado (s/n)? "; 
        cin>>respuesta; 
        if(respuesta=='s')
        {
          cout<<"\nIngrese el nuevo valor: "; 
          cin>>afiliados.peso; 
        }
        cout<<"\nDesea añadir un nuevo valor de mes para los valores de Presión arterial sistólica, Presión arterial diastólica, Triglicéridos y Colesterol?(s/n)"; 
        cin>>respuesta;
        afiliados.cantmeses++;
        if(respuesta=='s')
        {
          afiliados.cantmeseshoja++;
          if(afiliados.cantmeseshoja>12)//si ya todos los meses estan 
          {
            //Pocision2 me dice en que pocision del arreglo se reemplazan los datos del nuevo mes con base en la cantidad de meses
            posicion2=afiliados.cantmeseshoja%12;  
            cout<<"\nIngrese el nuevo valor para la presion arterial sistolica: "; 
            cin>>afiliados.salud[0][posicion2-1]; 
            cout<<"\nIngrese el nuevo valor para la presion arterial diastolica: ";
            cin>>afiliados.salud[1][posicion2-1];  
            if(afiliados.salud[0][posicion2-1]>=140 && afiliados.salud[1][posicion2-1]>=90)
            {
              cout<<"\nALERTA: presenta Hipertencion";
            }

            cout<<"\nIngrese el nuevo valor para los trigliceridos: "; 
            cin>>afiliados.salud[2][posicion2-1]; 
            if(afiliados.salud[2][posicion2-1]>199)
            {
              cout<<"\nALERTA: presenta nivel alto de trigliceridos";
            }
        
            cout<<"\nIngrese el nuevo valor para el colesterol: "; 
            cin>>afiliados.salud[3][posicion2-1]; 
            if(afiliados.salud[3][posicion2-1]>240)
            {
              cout<<"\nALERTA: presenta nivel alto de colesterol";
            }
          }
          else 
          {
            cout<<"\nIngrese el nuevo valor para la presion arterial sistolica: "; 
            cin>>afiliados.salud[0][afiliados.cantmeseshoja-1]; 
            cout<<"\nIngrese el nuevo valor para la presion arterial diastolica: "; 
            cin>>afiliados.salud[1][afiliados.cantmeseshoja-1]; 
            if(afiliados.salud[0][afiliados.cantmeseshoja-1]>=140 && afiliados.salud[1][afiliados.cantmeseshoja-1]>=90)
            {
              cout<<"\nALERTA: presenta Hipertencion";
            }
            cout<<"\nIngrese el nuevo valor para los trigliceridos: "; 
            cin>>afiliados.salud[2][afiliados.cantmeseshoja-1];
            if(afiliados.salud[2][afiliados.cantmeseshoja-1]>199)
            {
              cout<<"\nALERTA: presenta nivel alto de trigliceridos";
            }
            cout<<"\nIngrese el nuevo valor para el colesterol: "; 
            cin>>afiliados.salud[3][afiliados.cantmeseshoja-1];         
            if(afiliados.salud[3][afiliados.cantmeseshoja-1]>240)
            {
              cout<<"\nALERTA: presenta nivel alto de colesterol";
            }
          }
        }
        gymdeath_clientes.seekp(posicion - (int)sizeof(afiliado),ios::beg);
        gymdeath_clientes.write((char *) &afiliados, sizeof(afiliado));       
      }
       gymdeath_clientes.read((char*) &afiliados, sizeof(afiliado));
     }
      if(encontrado==false)//si sigue false es porque no encontro la cedula
      {
        cout<<"\nCedula no encontrada, desea tratar con otra cedula?(s/n)";
        cin>>respuesta; 
        if(respuesta=='n')
        {
          encontrado=true;//como es n, se debe parar el while y se hace cambiando el bool
        }
        else
        {
          gymdeath_clientes.close();
          gymdeath_clientes.open("datos_clientes.dat", ios::binary| ios::in| ios::out);// Posiciona archivo al comienzo para volver  a evaluar si la cedula existe
        }
      }
    }while(encontrado==false); //significa que si encontro la cedula//no se usa el booleano porque este se utilizo para salir del do while de arriba
  gymdeath_clientes.close();
}   