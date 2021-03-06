/*
 * Este programa es mi entrega de la tarea "Gestor de listado de compras"
 * Victor de la Rosa
 * 2015-2747
 * */
#include <stdio.h>
#include <stdlib.h>
//Declaramos la estructura de los elementos de la lista de compras
typedef struct{
	struct producto* anterior;	//Atributo que me ayudara en el manejo de los elementos de la lista
	struct producto* siguiente;	//Atributo que me ayudara en el manejo de los elementos de la lista
	int id;						//Me permite identificar los productos
	char* nombre;				//Nombre del producto
	int cantidad;				//Cantidad a comprar
	int mostrar;
	
	
} producto;

producto* primer = NULL;		//Atributo que me ayudara en el manejo de los elementos de la lista
producto* ultimo = NULL;		//Atributo que me ayudara en el manejo de los elementos de la lista
producto* ultimoUltimo = NULL;
producto* primerPrimer = NULL;


//Funcion que agrega un producto al programa
void agregar(producto* _producto){
	//Instancio estos atributos para evitar explosiones
	_producto -> siguiente = NULL;
	_producto -> anterior = NULL;
	_producto -> mostrar = 1;
	
	//Me valida si existe un elemento en la lista, sino, que asuma los roles de primero y ultimo
	if (primer == NULL){
		primer = _producto;
		ultimo = _producto;
		primerPrimer = _producto;
		ultimoUltimo = _producto;
	} else{									//De lo contrario, aplica la logica de agregado
		_producto -> anterior = ultimo;		//El producto anterior al que acabo de añadir es el que estaba de ultimo en la lista antes de su insercion
		ultimo -> siguiente = _producto;	//El producto siguiente del que estaba de ultimo es el recien insertado
		ultimo = _producto;					//Determino quien es el ultimo ahora
	}
	
}

void eliminar(int i){
	producto* productoAEliminar = ultimo;
	int a = productoAEliminar -> id;
	printf("antes del while");
	while(a != i){
		printf("Despues del while");
		producto* productoAEliminar = ultimo;		//Declaro una variable intermediaria
		ultimo = productoAEliminar -> anterior;
		a = productoAEliminar -> id;
	}
	ultimo = productoAEliminar -> anterior;
	printf("hasta aqui todo bien");
	free(productoAEliminar);
}

//Este metodo me extrae los productos de forma LIFO, es decir, del ultimo introducido al primero
producto* extraerDesc(){
	//No devolver nada si no existen productos en la lista
	if (ultimo == NULL){
		return NULL;
	}
	producto* producto_retorno = ultimo;		//Declaro una variable intermediaria
	ultimo = producto_retorno -> anterior;		//Utilizo la intermediaria para poder cambiar el valor el ultimo reconocido en la lista
	return producto_retorno;					//Pero poder mostrar el verdadero ultimo a mostrar en este momento
}

//Este metodo me extrae los productos de forma FIFO, es decir, del primer insertado al ultimo
producto* extraerAsc(){
	//No devolver nada si la lista esta vacia
	if (primer == NULL){
		return NULL;
	}
	producto* producto_retorno = primer;
	primer = producto_retorno -> siguiente;
	return producto_retorno;
}

int main(){
	int agregarOtro = 1;				//Variable que controlara la iteracion de introduccion de productos
	int contador = 1;					//Variable que me servira para determinar los identificadores de los productos
	int opcion = 0;
	int b = 0;
	printf("Bienvenido a la lista de compras\n");		//Mensaje de bienvenida :D

	
	while(opcion != 4){
		switch (opcion){
			case 1:
				printf("Decidiste aniadir un producto\n");
				//Iterador de entrada de productos
				while(agregarOtro == 1){
				char* nombreProducto = malloc(sizeof(char));	//Me crea dinamicamente nuevos espacios para los nuevos nombres que se vayan introduciendo
				int* cantidadProducto = malloc(sizeof(int));	//Me crea dinamicamente nuevos espacios para las nuevas cantidades
				
				producto* productoTemp = malloc(sizeof(producto));	//Me crea dinamicamente nuevos espacions para los nuevos productos que introduzcamos
				
				printf("Introduzca el nombre del producto:\n");		//Mensaje
				scanf(" %99[0-9a-zA-Z ]s", nombreProducto);			//Me recibe cualquier caracter alfanumerico, y espacios, el espacio inicial es para que ignore saltos de linea anteriores
				productoTemp -> nombre = nombreProducto;			//Asigno el valor obtenido a la propiedad del producto
				
				printf("Introduzca la cantidad que desea comprar:\n");
				scanf(" %i", &cantidadProducto);
				productoTemp -> cantidad = cantidadProducto;
				
				//Adicion del identificador
				productoTemp->id = contador;
				contador++;
				
				agregar(productoTemp);								//Agrego el producto a la estructura de la lista
				
				//Confirmacion del usuario
				printf("Desea agregar otro? 0/1:");
				//agregarOtro = 0;
				scanf("%i", &agregarOtro);
				}
				break;
				
			case 2:
				printf("Decidiste listar los productos\n");printf("Vamos a mostrar\n");

				producto* i = extraerAsc();
				
				while (i != NULL && i -> mostrar == 1){
					printf("%i - %i de %s\n", i->id, i->cantidad, i->nombre);
					i = extraerAsc();
				}
				primer = primerPrimer;
				break;
				
			case 3:
				
				printf("Decidiste eliminar un producto\n");
				printf("Introduzca el numero del producto a eliminar\n");
				scanf("%i", &b);
				
				producto* k = extraerAsc();
	
				while (k != NULL){
					if(k -> id == b	){
						k -> mostrar = 0;
					}
					k = extraerAsc();
				}
	
				break;
				
			case 4:
				printf("Decidiste salir del programa\n");
				system("pause");
				break;
				
			default:
				break;
		}	
		
		
			printf("Seleccione una opcion del menu:\n");
			printf("1 - Aniadir productos\n");
			printf("2 - Listar productos\n");
			printf("3 - Eliminar productos\n");
			printf("4 - Salir del programa\n");
			scanf("%i", &opcion);
	}
	
	//Menu
	
	/*
	//Iterador de entrada de productos
	while(agregarOtro == 1){
		char* nombreProducto = malloc(sizeof(char));	//Me crea dinamicamente nuevos espacios para los nuevos nombres que se vayan introduciendo
		int* cantidadProducto = malloc(sizeof(int));	//Me crea dinamicamente nuevos espacios para las nuevas cantidades
		
		producto* productoTemp = malloc(sizeof(producto));	//Me crea dinamicamente nuevos espacions para los nuevos productos que introduzcamos
		
		printf("Introduzca el nombre del producto:\n");		//Mensaje
		scanf(" %99[0-9a-zA-Z ]s", nombreProducto);			//Me recibe cualquier caracter alfanumerico, y espacios, el espacio inicial es para que ignore saltos de linea anteriores
		productoTemp -> nombre = nombreProducto;			//Asigno el valor obtenido a la propiedad del producto
		
		printf("Introduzca la cantidad que desea comprar:\n");
		scanf(" %i", &cantidadProducto);
		productoTemp -> cantidad = cantidadProducto;
		
		//Adicion del identificador
		productoTemp->id = contador;
		contador++;
		
		agregar(productoTemp);								//Agrego el producto a la estructura de la lista
		
		//Confirmacion del usuario
		printf("Desea agregar otro? 0/1:");
		//agregarOtro = 0;
		scanf("%i", &agregarOtro);
		
	}
	
	
	
	printf("Vamos a mostrar\n");
	
	producto* i = extraerAsc();
	
	while (i != NULL){
		if(i -> id != 2){
			printf("%i - %i de %s\n", i->id, i->cantidad, i->nombre);
		}
		i = extraerAsc();
	}
	
	system("pause");*/
	
	return 0;
}