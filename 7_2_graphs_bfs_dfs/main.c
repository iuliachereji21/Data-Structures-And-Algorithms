#include <stdio.h>
#include <stdlib.h>
#include "module2.h"

int main(int argc, char* argv[])
{
    pfin=fopen(argv[1],"r");
    pfout=fopen(argv[2],"w");
    nr_noduri=read_nodes(V_noduri,1);
    read_arcs(V,1);
    breadth_first_traversal(1);
    depth_first_traversal(1);


    fclose(pfin);
    fclose(pfout);
    return 0;
}
