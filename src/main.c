#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#define SYS_procinfo_64 326
#define SYS_procinfo_32 377

int main(int argc, char const *argv[])
{
    int sflag = 0;
    int svalue = 0;
    int c;
    opterr = 0;

    while((c = getopt(argc, argv, "s:"))!= -1)
    {
        switch (c) {
            case 's':
                sscanf(optarg, "%d", &svalue);
                sflag = 1;
                break;
            case '?':
                if(optopt == 's')
                {
                    fprintf(stderr, "Se debe indicar el estado buscado junto al parámetro -%c\n", optopt);
                }
                else if (isprint(optopt))
                {
                    fprintf(stderr, "Opcion desconocida -%c.\n", optopt);
                }
                //	Si el argumento en el que se encuentra el error no se puede imprimir,
                //	se indica que la opción tiene un caracter desconocido.
                else
                {
                    fprintf(stderr, "Opcion con caracter desconocido `\\x%x'.\n", optopt);
                }
                return 1;
            default:
                abort();
        }
    }

    if(sflag == 0)
    {
        fprintf(stderr, "No se ingreso el parametro '-s'\n");
        return -1;
    }

    int salida = syscall(SYS_procinfo_64, svalue);

    return 0;
}