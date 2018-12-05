  xlc -c -g -DCICS_AIX -I/opt/IBM/cicstg/include eci_addc.c
        xlc -o eci_addc eci_addc.o -L/opt/IBM/cicstg/lib -lpthreads -lc_r -lcclaix
        rm -f eci_addc.o
