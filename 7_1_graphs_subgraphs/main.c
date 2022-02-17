#include <stdio.h>
#include <stdlib.h>
#include "module.h"

int main(int argc, char* argv[])
{
    pfin=fopen(argv[1],"r");
    pfout=fopen(argv[2],"w");
    read_nodes(V_noduri,1);
    read_arcs(V,1);
    read_nodes(V1_noduri,2);
    afisare();

    fclose(pfin);
    fclose(pfout);
    return 0;
}
