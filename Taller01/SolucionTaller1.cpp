#include <iostream> 

using namespace std;

struct Programmer
{
    int cedula;
    float salario;
    int cantFunciones;
    float bonificacion;
};

void crearEmpleados(Programmer empleados[], int cantidad)
{
    for(int i=0;i<cantidad;i++)
    {
        cout << endl << "-------------  EMPLEADO " << i << "  -------------" << endl;
        cout << "Cedula del empleado " << i << ": ";
        cin >> empleados[i].cedula;
        cout << "Salario del empleado " << i << ": ";
        cin >> empleados[i].salario;
        cout << "Cantidad de funciones desarrolladas por el empleado " << i << ": ";
        cin >> empleados[i].cantFunciones;
    }
}

float promedioSueldo(Programmer empleados[], int cantidad)
{
    float suma = 0;
    float promedio;

    for(int i=0;i<cantidad;i++)
    {
        suma = suma + empleados[i].salario;
    }

    promedio = suma/cantidad;
    
    return promedio;
}

float promedioFunciones(Programmer empleados[], int cantidad)
{
    float suma = 0;
    float promedio;

    for(int i=0;i<cantidad;i++)
    {
        suma = suma + empleados[i].cantFunciones;
    }

    promedio = suma/cantidad;
    
    return promedio;
}

float bonificacion(float salario, int cantFunciones, float pSueldo, float pFunciones, float minimo)
{
    float bonificacion;

    if(salario==minimo && cantFunciones>pFunciones)
    {
        bonificacion = (salario*10)/100;
    }
    else if(salario>minimo && salario<pSueldo && cantFunciones>pFunciones)
    {
        bonificacion = (salario*5)/100;
    }
    else
    {
        bonificacion = 0;
    }

    return bonificacion;
}

void reporte(Programmer empleados[], int cantidad)
{
    cout << endl << "-------- REPORTE ----------" << endl;
    for (int i = 0; i < cantidad; i++)
    {
        cout << "Empleado " << i << ":" << endl;
        cout << "- Cedula " << empleados[i].cedula << endl;
        cout << "- Sueldo base inicial " << empleados[i].salario << endl;
        cout << "- Valor bonificación " << empleados[i].bonificacion << endl;
        cout << "- Salario Final " << empleados[i].salario + empleados[i].bonificacion << endl;
    }
    
}

int main()
{
    int cantidad, cedulaEvaluar;
    float pSueldo, pFunciones;
    float minimo = 100;

    cout << "Ingrese la cantidad de empleados que desea crear: ";
    cin >> cantidad;

    Programmer empleados[cantidad];

    crearEmpleados(empleados, cantidad);
    pSueldo = promedioSueldo(empleados, cantidad);
    pFunciones = promedioFunciones(empleados, cantidad);

    cout << "Calculando bonificación para todos los empleados...";

    for(int i=0;i<cantidad;i++)
    {
        empleados[i].bonificacion = bonificacion(empleados[i].salario, empleados[i].cantFunciones, pSueldo, pFunciones, minimo);
    }

    reporte(empleados, cantidad);
}