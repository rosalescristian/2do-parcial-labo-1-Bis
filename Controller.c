#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Participante.h"
#include "Parser.h"
#include "utn.h"

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	FILE* pFile;
	pFile = fopen(path,"r");
	if(pFile != NULL)
	{
		parser_EmployeeFromText(pFile,pArrayListEmployee);
		//parser_ConcursanteFromText(pFile,pArrayListEmployee);
	}
	fclose(pFile);
    return 1;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{

    FILE* pArchivo = 0;
    int retorno = -1;

    if(pArchivo != NULL)
    {
        pArchivo = fopen(path, "rb");
        parser_EmployeeFromBinary(pArchivo,pArrayListEmployee);
        retorno = 1;
    }
    fclose(pArchivo);

    return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int maxLen;
	int maxId;
	int i;
	char bId[8];
	char bNombre[128];
	char bHorasTrabajadas[8];
	char bSueldo[8];
	Employee* aEmployee;

	char bufferId[8];
	char bufferNombre[128];
	char bufferHorasTrabajadas[8];
	char bufferSueldo[8];

    char numeroConcursante[255];
	char anio[255];
	char nombre[255];
	char dni[255];
	char fechaPresentacion[255];
	char temaPresentacion[255];
	char puntajePrimeraRonda[255];

	if(pArrayListEmployee != NULL)
	{
		maxLen = ll_len(pArrayListEmployee);
		maxId = 0;

		for(i=0;i<maxLen;i++)
		{
			aEmployee = ll_get(pArrayListEmployee,i);
			if(aEmployee->id > maxId)
			{
				maxId = aEmployee->id;
			}
		}
			maxId++;
			sprintf(bId,"%d",maxId);
            strcpy(bufferId,bId);

		if(getNombreStr(bNombre, "Ingrese el nombre del Empleado: \n", "Ha ingresado un nombre invalido. Reintente\n",2,sizeof(bNombre),3)==0)
        {
            strcpy(bufferNombre,bNombre);
            if(getHsTrabajadasStr(bHorasTrabajadas, "\nIngrese las horas trabajadas del nuevo empleado.\n","Ha ingresado un valor invalido, reingrese.\n",0,99000,3)==0)
            {
                strcpy(bufferHorasTrabajadas,bHorasTrabajadas);
                if(getSueldoStr(bSueldo, "\nIngrese el sueldo del nuevo empleado.\n","Ha ingresado un valor invalido, reingrese.\n",0,999999,3)==0)
                {
                    strcpy(bufferSueldo,bSueldo);
//                    aEmployee = employee_newParametros(bufferId, bufferNombre, bufferHorasTrabajadas, bufferSueldo);
                    aEmployee = employee_newParametros(numeroConcursante,anio,nombre,dni,fechaPresentacion,temaPresentacion,puntajePrimeraRonda);
                    ll_add(pArrayListEmployee, aEmployee);
                    //printf("\nSe ingreso el empleado Id: %d - Nombre: %s - Horas: %d - Sueldo: %d\n\n",aEmployee->id, aEmployee->nombre, aEmployee->horasTrabajadas, aEmployee->sueldo);
                }
            }
        }
		else
		{
			printf("No se pudo completar la carga del empleado, reintente.\n");
		}
	}
	return 1;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno;
	int maxLen;
	int idEditar;
	int bIdStruct;
	char bId[8];
	char respuesta;
	char respuestaDos;
	char bNombre[128];
	char bSueldo[8];
	char bHorasTrabajadas[8];

	Employee* aEmployee;

	if(pArrayListEmployee != NULL)
	{
	    retorno = -1;
		respuesta = 'n';
		maxLen = ll_len(pArrayListEmployee);
		system("cls");
		printf("\n\n\t\t*** EDICION DE EMPLEADOS ***\n\n");

		controller_ListEmployee(pArrayListEmployee);
		if(getIdStr(bId,"\nIngrese el ID el Empleado a modificar: \n","Ha ingresado un ID invalido. Reintente\n",0,maxLen,3)==0)
		{
			system("cls");
			idEditar=atoi(bId);

            for(int i=0; i<maxLen;i++)
            {
                aEmployee = ll_get(pArrayListEmployee,i);
                employee_getId(aEmployee,&bIdStruct);
                if(idEditar==bIdStruct)
                {
                    aEmployee=ll_get(pArrayListEmployee,i);
                    break;
                }
            }
			printf("\nVa a editar el siguiente empleado:\n\n");
//			controller_PrintEmployee(aEmployee);
            getChar(&respuesta, "Desea proceder? (s/n)\n\n", "La respuesta es invalida, reintente.\n",'n','s',3);
            if(respuesta == 's')
            {
                printf("\nQue campo desea editar?\n");
                printf("\tA- Nombre\n");
                printf("\tB- Hs Trabajadas\n");
                printf("\tC- Sueldo\n");

                if(getCharVarios(&respuestaDos,"Ingrese la opcion deseada.\n","Ha ingresesado una opcion invalida. Reintente.\n",'A','C',3)==0)
                {
                    switch(respuestaDos)
                    {
                        case 'A':
                                getNombreStr(bNombre, "Ingrese el nuevo nombre del Empleado: \n", "Ha ingresado un nombre invalido. Reintente\n",2,sizeof(bNombre),3);
                                employee_setNombre(aEmployee, bNombre);
                                break;
                        case 'B':
                                getHsTrabajadasStr(bHorasTrabajadas, "Ingrese las nuevas horas trabajadas del empleado: \n","Ha ingresado un valor invalido, reingrese.\n",0,99000,3);
//                                employee_setHorasTrabajadas(aEmployee, bHorasTrabajadas);
                                break;
                        case 'C':
                                getSueldoStr(bSueldo, "Ingrese el nuevo sueldo del empleado: \n","Ha ingresado un valor invalido, reingrese.\n",0,999999,3);
//                                employee_setSueldo(aEmployee,bSueldo);
                                break;
                    }
                        retorno = 0;
                        printf("\nSe realizo la modificacion solicitada.\n\n");
                }

            }
            retorno = -1;
		}
	}
	return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int retorno;
	int maxLen;
//	int i;
	int idEditar;
	int bIdPointer;
	int bIdStruct;
	int maxId;
	char bId[12];
	char respuesta;
    int deleteId = -1;

	Employee* aEmployee;
    retorno = -1;
    system("cls");
    printf("\n\n\t\t*** ELIMINAR EMPLEADOS ***\n\n");
	if(pArrayListEmployee != NULL)
	{
		respuesta = 'n';
		maxLen = ll_len(pArrayListEmployee);
		controller_ListEmployee(pArrayListEmployee);
		if(maxLen > 1)
        {
            for(int i=0;i<maxLen;i++)
            {
                aEmployee = ll_get(pArrayListEmployee,i);
                employee_getId(aEmployee,&bIdPointer);
                if(bIdPointer > maxId)
                {
                    maxId = bIdPointer;
                }
            }
            getIdStr(bId,"\n\n Ingrese el ID el Empleado a Eliminar: \t","Ha ingresado un ID invalido. Reintente\n",0,maxLen,3);
			idEditar=atoi(bId);
            for(int i=0; i<maxLen;i++)
            {
                aEmployee = ll_get(pArrayListEmployee,i);
                employee_getId(aEmployee,&bIdStruct);
                if(idEditar==bIdStruct)
                {
                    aEmployee=ll_get(pArrayListEmployee,i);
                    deleteId = i;
                    break;
                }
            }
			printf("\nVa a borrar el siguiente empleado:\n");
//			controller_PrintEmployee(aEmployee);
            getChar(&respuesta, "\nDesea proceder? (s/n)\t", "La respuesta es invalida, reintente.\n",'n','s',3);
            if(respuesta != 'n')
            {
                ll_remove(pArrayListEmployee,deleteId);
                printf("Se elimino el empleado solicitado.\n\n");
                retorno = 0;
            }
        }
        else if(maxLen == 1)
		{
		    aEmployee = ll_get(pArrayListEmployee,0);
            printf("\nVa a borrar el siguiente empleado:\n");
//            controller_PrintEmployee(aEmployee);
            getChar(&respuesta, "\nDesea proceder? (s/n)\t", "La respuesta es invalida, reintente.\n",'n','s',3);
            if(respuesta != 'n')
            {
                ll_remove(pArrayListEmployee,0);
                printf("Se elimino el empleado solicitado.\n\n");
                retorno = 0;
            }
        }
        else
        {
            printf("\t\tNo hay empleados para eliminar.\n\n");
        }
            retorno = -1;
    }
	return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int i;
	int maxLen;
	Employee* aEmployee;

	if(pArrayListEmployee != NULL)
	{
		maxLen = ll_len(pArrayListEmployee);
		for(i=0;i<maxLen;i++)
		{
			aEmployee = ll_get(pArrayListEmployee,i);
			controller_PrintEmployee(aEmployee);
		}
	}
    return 1;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;

    if(pArrayListEmployee != NULL)
    {
        ll_sort(pArrayListEmployee, employee_sortByName, 1);
        printf("\n\t\tSe ordenaron los empleados por nombre de manera ascendente exitosamente.\n\n");
        retorno = 0;
    }
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
/*int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
    FILE* pArchivo;
    Employee* auxEmployee;

    int retorno = -1;

    int id;
    int anioNacimiento;
    char nombre[50];
    char dni[9];
    char fechaPresentacion[12];
    char temaPresentacion[30];
    int primeraRonda;
    int segundaRonda;
    float promedioPuntaje;
    char* idStr=NULL;
    char* anioNacimientoStr=NULL;
    char* primeraRondaStr=NULL;
    char* segundaRondaStr=NULL;
    char* promedioPuntajeStr=NULL;
    promedioPuntajeStr=(char*)malloc(sizeof(char)*6);
    char resultado[]={"resultado"};
    int len;

    if(pArrayListEmployee != NULL && path != NULL)
    {
        pArchivo = fopen(path, "w");
        if(pArchivo != NULL)
        {
            //fprintf(pArchivo,"id,nombre,horasTrabajadas,sueldo\n");
            fprintf(pArchivo,"numeroConcursante,anio,nombre,dni,fechaPresentacion,temaPresentacion,puntajePrimeraRonda,puntajeSegundaRonda,promedioPuntaje\n");
            for(int i=0; i< ll_len(pArrayListEmployee); i++)
            {
                auxEmployee = ll_get(pArrayListEmployee,i);
                employee_getId(auxEmployee,&id);
                employee_getAnio(auxEmployee,&anioNacimiento);
                employee_getNombre(auxEmployee,nombre);
                employee_getDni(auxEmployee,dni);
                employee_getFechaPresentacion(auxEmployee,fechaPresentacion);
                employee_getTemaPresentacion(auxEmployee,temaPresentacion);
                employee_getPuntajePrimeraRonda(auxEmployee,&primeraRonda);
                employee_getPuntajeSegundaRonda(auxEmployee,&segundaRonda);
                employee_getPromedioPuntaje(auxEmployee,&promedioPuntaje);
                //fprintf(pArchivo,"%d,%s,%d,%d\n",idAux,nombreAux,horasAux,sueldoAux);
                fprintf(pArchivo,"%d,%d,%s,%s,%s,%s,%d,%d,%.2f");
            }
            fclose(pArchivo);
            retorno = 0;
        }
        else
        {
            printf("\t\tNo se puede escribir el archivo.\n");
        }
    }
    return retorno;
}
*/

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
    FILE* pArchivo;
    Employee* aEmployee;

    int retorno = -1;
    int i = 0;

    if(pArrayListEmployee != NULL && path != NULL)
    {
        pArchivo = fopen(path,"wb");

        for(i=0; i< ll_len(pArrayListEmployee); i++)
        {
            aEmployee = (Employee*)ll_get(pArrayListEmployee,i);
            fwrite(aEmployee, sizeof(Employee),1,pArchivo);
        }
        fclose(pArchivo);
    }
    return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployees(LinkedList* pArrayListEmployee)
{
	int i;
	int maxLen;
	void* aEmployee;

	if(pArrayListEmployee != NULL)
	{
		maxLen = ll_len(pArrayListEmployee);
		for(i=0;i<maxLen;i++)
		{
			aEmployee = ll_get(pArrayListEmployee,i);
			controller_PrintEmployee(aEmployee);
		}
	}
    return 1;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
void controller_PrintEmployee(void* this)
{
    int idStruct;
    int anioNacimientoStruct;
    char* nombreStruct=NULL;
    char* dniStruct=NULL;
    char* fechaPresentacionStruct=NULL;
    char* temaPresentacionStruct=NULL;
    int puntajePrimeraRondaStruct;
    int puntajeSegundaRondaStruct;
    float promedioPuntaje;

    nombreStruct=(char*)malloc(sizeof(char)*50);
    dniStruct=(char*)malloc(sizeof(char)*9);
    fechaPresentacionStruct=(char*)malloc(sizeof(char)*12);
    temaPresentacionStruct=(char*)malloc(sizeof(char)*50);

    Employee* auxEmployee = (Employee*)this;

	if(this != NULL)
	{
		employee_getId(auxEmployee,&idStruct);
        employee_getAnio(auxEmployee,&anioNacimientoStruct);
        employee_getNombre(auxEmployee,nombreStruct);
        employee_getDni(auxEmployee,dniStruct);
        employee_getFechaPresentacion(auxEmployee,fechaPresentacionStruct);
        employee_getTemaPresentacion(auxEmployee,temaPresentacionStruct);
        employee_getPuntajePrimeraRonda(auxEmployee,&puntajePrimeraRondaStruct);
        employee_getPuntajeSegundaRonda(auxEmployee,&puntajeSegundaRondaStruct);
        employee_getPromedioPuntaje(auxEmployee,&promedioPuntaje);
        printf("|%-6d|%-20d|%-15s|%-9s|%-22s|%-30s|%-22d|%-22d|%-9.2f|\n",idStruct,anioNacimientoStruct,nombreStruct,dniStruct,fechaPresentacionStruct,temaPresentacionStruct,puntajePrimeraRondaStruct,puntajeSegundaRondaStruct,promedioPuntaje);
    }

}

int controller_asignValues(LinkedList* pArrayListEmployee)
{
    int retorno;
    retorno = -1;
    if (pArrayListEmployee != NULL)
    {
        if(ll_map(pArrayListEmployee,employee_juradoCalculaPuntaje)==0)
        {
            retorno = 0;
        }
    }
    return retorno;
}


int controller_countUnderTen(LinkedList* pArrayListEmployee)
{
    int retorno;
    int counter = 0;
    retorno = -1;
    if (pArrayListEmployee != NULL)
    {
        counter = ll_count(pArrayListEmployee,employee_countMinusTen);
    }
    printf("El valor de concursantes con menos de 10 puntos en la primera ronda es: %d\n\n",counter);
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveOneAsText(char* path , LinkedList* pArrayListEmployee)
{
    FILE* pArchivo;
    Employee* auxEmployee;

    int retorno = -1;

    int id;
    int bufferId;
    int anioNacimiento;
    char nombre[50];
    char dni[9];
    char fechaPresentacion[12];
    char temaPresentacion[30];
    int primeraRonda;
    int segundaRonda;
    float promedioPuntaje;
    char* idStr=NULL;
    char* anioNacimientoStr=NULL;
    char* primeraRondaStr=NULL;
    char* segundaRondaStr=NULL;
    char* promedioPuntajeStr=NULL;
    promedioPuntajeStr=(char*)malloc(sizeof(char)*6);
    char resultado[]={"resultado"};
    int len;

    if(pArrayListEmployee != NULL && path != NULL)
    {
        pArchivo = fopen(path, "w");
        if(pArchivo != NULL)
        {
            //fprintf(pArchivo,"id,nombre,horasTrabajadas,sueldo\n");
            fprintf(pArchivo,"numeroConcursante,anio,nombre,dni,fechaPresentacion,temaPresentacion,puntajePrimeraRonda,puntajeSegundaRonda,promedioPuntaje\n");
            for(int i=0; i< ll_len(pArrayListEmployee); i++)
            {
                employee_getId(auxEmployee,&id);
                employee_getAnio(auxEmployee,&anioNacimiento);
                employee_getNombre(auxEmployee,nombre);
                employee_getDni(auxEmployee,dni);
                employee_getFechaPresentacion(auxEmployee,fechaPresentacion);
                employee_getTemaPresentacion(auxEmployee,temaPresentacion);
                employee_getPuntajePrimeraRonda(auxEmployee,&primeraRonda);
                employee_getPuntajeSegundaRonda(auxEmployee,&segundaRonda);
                employee_getPromedioPuntaje(auxEmployee,&promedioPuntaje);
                //fprintf(pArchivo,"%d,%s,%d,%d\n",idAux,nombreAux,horasAux,sueldoAux);
                fprintf(pArchivo,"%d,%d,%s,%s,%s,%s,%d,%d,%.2f");
            }
            fclose(pArchivo);
            retorno = 0;
        }
        else
        {
            printf("\t\tNo se puede escribir el archivo.\n");
        }
    }
    return retorno;
}
