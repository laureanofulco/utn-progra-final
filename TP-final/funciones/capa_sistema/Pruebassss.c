#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char nombre[50];
    char password[50];
} Administrador;

void scanString(char cadena[], int tam){
    fgets(cadena, tam, stdin);

    int len = strlen(cadena);

    if(len > 0 && cadena[len - 1] == '\n'){
        cadena[len - 1] = '\0';
    }
}

void error(const char *titulo, const char *mensaje){
    printf("\n============================\n");
    printf("  %s\n", titulo);
    printf("============================\n");
    printf("  %s\n", mensaje);
    printf("============================\n");
}

int existe_admin(){
    FILE *archivo = fopen("admins.dat", "rb");

    Administrador admin;

    if(archivo == NULL){
        return 0;
    }

    int existe = fread(&admin, sizeof(Administrador), 1, archivo);

    fclose(archivo);

    return existe;
}

int buscar_admin(char nombre[], char archivo_admins[]){
    FILE *archivo = fopen(archivo_admins, "rb");

    Administrador admin_aux;

    if(archivo == NULL){
        return 0;
    }

    while(fread(&admin_aux, sizeof(Administrador), 1, archivo) == 1){
        if(strcmp(admin_aux.nombre, nombre) == 0){
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    return 0;
}

void guardar_admin(char archivo_admins[]){
    Administrador neu_admin;

    printf("Ingrese nombre: ");
    scanString(neu_admin.nombre, 50);

    printf("Ingrese contraseña: ");
    scanString(neu_admin.password, 50);

    if(buscar_admin(neu_admin.nombre, archivo_admins)){
        error("ERROR", "Admin existente");
        return;
    }

    FILE *archivo = fopen(archivo_admins, "ab");

    if(archivo == NULL){
        error("ERROR", "No se pudo abrir el archivo");
        return;
    }

    fwrite(&neu_admin, sizeof(Administrador), 1, archivo);

    fclose(archivo);

    printf("\nAdmin guardado con exito.\n");
}

void ver_admins(char archivo_admins[], Administrador admin){
	FILE * archivo = fopen(archivo_admins, "rb");
	Administrador aux_admin;
	
	if(archivo != NULL){
		while(fread(&aux_admin, sizeof(Administrador), 1, archivo) > 0){
			printf(" - Nombre: %s -\n", aux_admin.nombre);
		}
	}
}

int main(){
    char archivo_admins[] = "admins.dat";
	Administrador admin;

    if(!existe_admin()){
        printf("No existe ningun administrador.\n");
        printf("Creando administrador principal...\n\n");

        guardar_admin(archivo_admins);
    }else{
        printf("Ya existe al menos un administrador en el sistema.\n");
    }
    
    int opc = 0;
    printf("\n\n");
    do{
    	printf("1 - ver admins\n");
    	printf(" opcion: ");
    	scanf("%d", &opc);
    	
    	switch(opc){
    		case 1:{
    			ver_admins(archivo_admins, admin);
				break;
			}
		}
		
	}while(opc != 0);
    

    return 0;
}