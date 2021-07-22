/*
DESARROLLAR UN PROGRAMA QUE PERMITA REGISTRA LOS ALUMNOS DE UN CURSO
EL DOCENTE A CARGO LOS EVAL�A UTILIZANDO TRES INDICADORES (evaluaci�n
parcial, evaluaci�n final y proyecto certificador) LOS CUALES TIENEN
UN PESO DE 1, 2 Y 3 RESPECTIVAMENTE
SE DEBE SOLICITAR NOMBRES, APELLIDO PATERNO Y MATERNO, DNI y SEXO DEL
ESTUDIANTE AS� COMO LAS NOTAS DE LAS TRES EVALUACIONES
EL PROGRAMA DEBE REPORTAR LO SIGUIENTE:
	1. LISTADO DE TODOS LOS ESTUDIANTES: nombre completo, promedio
	y condici�n final
	2. LISTADO DE LOS APROBADOS EN EL PROYECTO CERTIFICADOR: nombre
	completo y calificaci�n
	3. PORCENTAJES DE APROBADOS Y DESAPROBADOS POR SEXO
	4. LISTADO DE LOS ESTUDIANTES QUE OBTUVIERON EL PROMEDIO MAS ALTO
	5. EL PROMEDIO DEL AULA, EL PROMEDIO M�S BAJO Y EL MAS ALTO
*/

#include "basicas.cpp"

#define MAXDNI 9
#define DELTA 2

char *evaluaciones[]={" Examen parcial  "," Examen final  "," Proyecto certificador  "};
char *msgEvaluaciones[]={"\tExamen parcial[0-20] : ","\tExamen final[0-20] : ","\tProyecto certificador[0-20] : "};

//ESTUDIANTE
class Estudiante{
  private:
   	char nombres[MAX];
   	char apellidoPaterno[MAX];
   	char apellidoMaterno[MAX];
   	char DNI[MAXDNI];
   	char sexo;
   	int notas[3];

  public:
	Estudiante()
   	{
   		this->nombres[0] = NULL;
   		this->apellidoPaterno[0] = NULL;
   		this->apellidoMaterno[0] = NULL;
   		this->DNI[0] = NULL;
		this->sexo = NULL;
      	for( int i=0; i<3; i++)
      	{
			this->notas[i] = 0;
      	}
	}

   	void leer()
   	{
      	char auxDNI[MAXDNI];
      	int pos;

      	cout << "Nombres : "; cin >> this->nombres;
   		cout << "Ap. Paterno : "; cin >> this->apellidoPaterno;
   		cout << "Ap. Materno : "; cin >> this->apellidoMaterno;
      	this->sexo = leeCaracter(" F: Femenino"," M: Masculino",'F','M',"Sexo[F/M] : ");
   	}

   	void *getNombre(char *nombre)
   	{
   		strcpy(nombre,this->nombres);
   	}

   	void getNombreCompleto( char *nombre)
   	{
      	strcpy( nombre, this->apellidoPaterno);
      	strcat( nombre, " ");
      	strcat( nombre, this->apellidoMaterno);
      	strcat( nombre , " ");
      	strcat( nombre, this->nombres);
   	}

   	void getDescripcionSexo(char *sexo){
   		if(this->sexo=='F')
		{
      		strcpy(sexo,"Femenino");
      	}
		else
		{
       		strcpy(sexo,"Masculino");
      	}
   	}

   	char getSexo()
	{
   		return this->sexo;
   	}

   	char *getDNI()
	{
   		return this->DNI;
   	}

   	void getDNI(char *nDNI)
	{
   		strcpy(nDNI,this->DNI);
   	}
   	
   	void setDNI(char *dni)
	{
   		strcpy(this->DNI,dni);
   	}

	void setCalificacion( int evaluacion, int nota)
	{
   		this->notas[ evaluacion - 1 ] = nota;
   	}

   	void getPromedio(float &promedio)
	{
      	int suma=0;

	   	for(int i=0;i<3;i++)
		{
	      	suma+=this->notas[i];
	    }
	    promedio=(float)suma/3;
   	}

   	int getCondicion(float prom)
	{
   		if(prom>10.5)
		{
			return 1;
      	}
		else
		{
			return 0;
      	}
   	}

   	int getNota(int n)
	{
   		return this->notas[n];
   	}
};

//LISTA ESTUDIANTES
class ListaEstudiantes{
  private:
	int n;
   	int max;
   	Estudiante *data;

  public :
	ListaEstudiantes()
	{
   		this->n = 0;
      	this->max = 0;
      	this->data = NULL;
   	}

   	~ListaEstudiantes()
	{
   		if(this->max > 0)
		{
      		delete []this->data;
      	}
      	this->max = 0;
   		this->n = 0;
      	this->data = 0;
   	}

   	int getN()
	{
   		return this->n;
   	}

   	Estudiante *get( int pos)
	{
  		return (this->data + pos);
   	}

	void agregar(Estudiante &estudiante)
	{
   		if( this->n == this->max)
		{
      		this->crecer();
      	}

      	this->data[this->n] = estudiante;
		this->n++;
   	}

   	void eliminar(int pos)
	{
   		Estudiante *temp;
      	int num=0;

      	temp=new Estudiante[this->max];

      	for(int i=0;i<this->n;i++)
		{
      		if(i!=pos)
			{
         		temp[num]=this->data[i];
            	num++;
         	}
      	}
      	if(this->n > 0)
		{
      		delete []this->data;
      	}
      	this->data=temp;
      	this->n--;
   	}

   	Estudiante *buscar(char *nombre)
	{
   		Estudiante *temp;
		char aux[MAX];

      	for(int i=0;i<this->n;i++)
		{
      		temp=this->get(i);
      		temp->getNombre(aux);
      		if(strcmpi(nombre,aux)==0)
			{
         		return temp;
      		}
      	}
      	return NULL;
   	}

	int buscarDNI(char *DNIbuscar)
	{
      	Estudiante *temp;
		char dni[MAXDNI];

   		for(int i=0;i<this->n;i++)
		{
         	temp=this->get(i);
   			temp->getDNI(dni);
      		if(strcmpi(DNIbuscar,dni)==0)
			{
      			return i;
      		}
   		}
   		return -1;
	}

  private:
	void crecer()
	{
   		Estudiante *temp;

      	this->max += DELTA;
      	temp = new Estudiante[this->max];

      	for( int i=0; i<this->n; i++)
		{
      		temp[i] = this->data[i];
      	}
      	if( this->n > 0)
		{
      		delete []this->data;
      	}
      	this->data = temp;
   	}

};

ListaEstudiantes alumnos;

int leerOpcion()
{
	char *opciones[] = {"Registrar estudiante", "Modificar estudiante",
   		"Eliminar estudiante", "Registrar calificacion",
         "Reportes","Salir"};
   	int op;

	cout << " - MENU PRINCIPAL -" << endl;
   	for( int i=0; i<6; i++)
	{
   		cout << (i+1) << ".- " << opciones[i] << endl;
   	}

   	op = leeEntero(" Opcion : ", 1, 6, "\t* Opcion no valida");

   	return op;
}

void registrarEstudiante()
{
	Estudiante alumno;
   	char auxDNI[MAXDNI];
   	int pos;

   	do
	{
   		cout << "\n";
      	do
		{
      		cout << "DNI(8 caracteres): ";
      		cin >> auxDNI;
      	}while(!(strlen(auxDNI)==MAXDNI-1));
      	pos=alumnos.buscarDNI(auxDNI);
      	if(pos==-1)
		{
      		alumno.setDNI(auxDNI);
         	alumno.leer();
      	}
		else
		{
      		cout<<"\t* El DNI ingresado ya ha sido registrado"<<endl;
      	}
   	}while(pos>-1);

   	alumnos.agregar(alumno);
   	cout << "\t* Estudiante registrado exitosamente" << endl;
   	getch();
}

void modificarEstudiante()
{
	char nombre[MAX];
   	Estudiante *alumno;

   	cout << "\nNombre del Estudiante a modificar: ";
   	cin >> nombre;
   	alumno=alumnos.buscar(nombre);
   	if(nombre!=NULL)
	{
   		alumno->leer();
      	cout << "\t* Estudiante modificado exitosamente" << endl;
   	}
	else
	{
   		cout << "\t* Estudiante no encontrado" << endl;
   	}
   	getch();
}

void eliminarEstudiante()
{
	char numDNI[MAXDNI];
   	int pos;

   	cout << "\nDNI del Estudiante a eliminar(8 caracteres): ";
   	cin >> numDNI;
   	pos=alumnos.buscarDNI(numDNI);
   	if(pos>=0)
	{
   		alumnos.eliminar(pos);
      	cout << "\t* Estudiante eliminado exitosamente" << endl;
   	}
	else
	{
   		cout << "\t* Estudiante no encontrado" << endl;
   	}
   	getch();
}

void registrarCalificacion()
{
   	char nombreCompleto[MAX*3];
   	int evaluacion;
   	int nota;

   	cout << "\n";
	for( int i=0; i<3; i++)
	{
   		cout << (i+1) << ".-" << evaluaciones[i] << endl;
   	}
   	evaluacion = leeEntero(" Evaluacion[1-3] : ", 1, 3,"\t* No valida");

	for( int i=0; i<alumnos.getN(); i++)
	{
   		alumnos.get(i)->getNombreCompleto(nombreCompleto);
   		
      	cout << "\n";
      	cout << nombreCompleto << endl;
   		nota = leeEntero(msgEvaluaciones[evaluacion - 1],0, 20,"\t* Nota no valida");
     	alumnos.get(i)->setCalificacion(evaluacion, nota);
   	}
}

int leerReporte()
{
	char *reportes[]={"Listado de Estudiantes",
		"Listado de aprobados en el proyecto certificador",
      	"Porcentaje de aprobados y desaprobados por sexo",
      	"Listado de estudiantes que obtuvieron el promedio mas alto",
      	"El promedio de aula, promedio mas alto y promedio mas bajo","Salir"};
   	int op;

	cout << " - REPORTES -" << endl;
   	for(int i=0;i<6;i++)
	{
   		cout << (i+1) << "." << reportes[i] << endl;
   	}

   	op=leeEntero(" Opcion : ",1,6,"\t* Opcion no valida");

   	return op;
}

//REPORTE N 01
void presentarLista()
{
	char nombreCompleto[MAX*3];
   	float promedio=0.0;
   	char condicion[MAX];

   	cout << "\n";
   	cout << "LISTADO DE ESTUDIANTES" << endl;
	for(int i=0;i<alumnos.getN();i++)
	{
      	alumnos.get(i)->getNombreCompleto(nombreCompleto);
      	alumnos.get(i)->getPromedio(promedio);

      	if(alumnos.get(i)->getCondicion(promedio)==1)
		{
      		strcpy(condicion,"Aprobado");
      	}
		else
		{
   			strcpy(condicion,"Desaprobado");
      	}

      	cout << "\n";
      	cout << " " << (i+1) << ".- " << nombreCompleto << "   " << promedio <<
      	"(" << condicion << ")" << endl;
   	}
   	cout << "=================================================" <<endl;
	getch();
}

//REPORTE N 02
void listadoAprobadosProyecto()
{
	char nombreCompleto[MAX*3];
   	int n=0;

   	cout << "\n";
   	cout << "LISTADO DE ESTUDIANTES APROBADOS EN EL PROYECTO CERTIFICADOR" << endl;
	for(int i=0;i<alumnos.getN();i++)
	{
      	alumnos.get(i)->getNombreCompleto(nombreCompleto);

      	if(alumnos.get(i)->getNota(2)>10.5)
		{
			cout << "\n";
      		cout << " " << (n+1) << ".- " << nombreCompleto << "   " << alumnos.get(i)->getNota(2) << endl;
         	n++;
      	}
   	}
   	cout << "============================================================" <<endl;
	getch();
}

//REPORTE N 03
void porcentajeAprobadosDesaprobados()
{
	int numF=0, aprobadoF=0, numM=0, aprobadoM=0;
   	float promedio=0.0, porcentajeFA=0.0, porcentajeFD=0.0,
   		porcentajeMA=0.0,porcentajeMD=0.0;

   	cout << "\n";
   	cout << "PORCENTAJE DE APROBADOS Y DESAPROBADOS SEGUN SU SEXO" << endl;
   	for(int i=0;i<alumnos.getN();i++)
	{
   		alumnos.get(i)->getPromedio(promedio);

		if(alumnos.get(i)->getSexo()=='F')
		{
      		numF++;
         	if(promedio>10.5)
			{
         		aprobadoF++;
         	}
   		}
		else
		{
      		numM++;
         	if(promedio>10.5)
			{
         		aprobadoM++;
         	}
   		}
   	}
   	if(numF>0)
	{
   		porcentajeFA=(float)aprobadoF*100/numF;
      	porcentajeFD=100-porcentajeFA;
   	}
   	if(numM>0)
	{
   		porcentajeMA=(float)aprobadoM*100/numM;
      	porcentajeMD=100-porcentajeMA;
   	}

   	cout << "\n";
   	cout << "  + Mujeres" << endl;
   	cout << "\tAprobadas : " << porcentajeFA << "%" << endl;
   	cout << "\tDesaprobadas : " << porcentajeFD << "%" << endl;
   	cout << "\n";
   	cout << "  + Hombres " << endl;
   	cout << "\tAprobados : " << porcentajeMA << "%" << endl;
   	cout << "\tDesaprobados : " << porcentajeMD << "%" << endl;
   	cout << "====================================================" <<endl;
	getch();
}

//REPORTE N 04
void listadoPromedioAlto()
{
	char nombreCompleto[MAX*3];
   	float promedio=0.0,mayor=0.0;
   	int n=0;

   	cout << "\n";
   	cout << "LISTADO DE ESTUDIANTES QUE OBTUVIERON EL PROMEDIO MAS ALTO";
	for(int i=0;i<alumnos.getN();i++)
	{
      	alumnos.get(i)->getPromedio(promedio);

		if(promedio>mayor)
		{
      		mayor=promedio;
   		}
   	}
   	cout << "(" << mayor << ")" << endl;
   	cout << "\n";
   	for(int i=0;i<alumnos.getN();i++)
	{
      	alumnos.get(i)->getNombreCompleto(nombreCompleto);
      	alumnos.get(i)->getPromedio(promedio);

   		if(promedio==mayor)
		{
      		cout << " " << (n+1) << ".- " << nombreCompleto << endl;
         	n++;
      	}
   	}
   	cout << "==========================================================" <<endl;
	getch();
}

//REPORTE N 05
void promedioBajoAlto()
{
   	float promedio=0.0,mayor=0.0,menor=20.0,promAula,suma=0.0;

   	cout << "\n";
   	cout << "EL PROMEDIO DEL AULA, PROMEDIO MAS ALTO Y PROMEDIO MAS BAJO" << endl;
	for(int i=0;i<alumnos.getN();i++)
	{
      	alumnos.get(i)->getPromedio(promedio);

      	suma+=promedio;
		if(promedio>mayor)
		{
      		mayor=promedio;
   		}
      	if(promedio<menor)
		{
      		menor=promedio;
      	}
   	}
   	promAula=(float)promedio/alumnos.getN();

   	cout << "\n";
   	cout << "\tPromedio del aula : " << promAula << endl;
   	cout << "\tPromedio mas alto : " << mayor << endl;
   	cout << "\tPromedio mas bajo : " << menor << endl;
   	cout << "===========================================================" <<endl;
	getch();
}

void listaReportes()
{
	int op;

   	do
	{
   		system("cls");
      	op=leerReporte();
      	switch(op)
		{
      		case 1: presentarLista(); break;
         	case 2: listadoAprobadosProyecto(); break;
         	case 3: porcentajeAprobadosDesaprobados(); break;
         	case 4: listadoPromedioAlto(); break;
         	case 5: promedioBajoAlto(); break;
         	case 6: break;
      	}
   	}while(op<6);
}

int main()
{
	int op;

   	do
	{
      	system("cls");
   		op = leerOpcion();
      	switch(op)
		{
      		case 1: registrarEstudiante(); break;
         	case 2: modificarEstudiante(); break;
         	case 3: eliminarEstudiante(); break;
      		case 4: registrarCalificacion(); break;
         	case 5: listaReportes(); break;
         	case 6: cout << "\tOFF"; break;
      	}
   	}while(op < 6);
   
   	return 1;
}

