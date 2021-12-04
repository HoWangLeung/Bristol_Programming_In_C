#include "./specific.h"
#include "../boolarr.h"

boolarr *boolarr_init(void)
{

    boolarr *ba = (boolarr *)ncalloc(1, sizeof(boolarr));
    ba->size=0;
    return ba;
}