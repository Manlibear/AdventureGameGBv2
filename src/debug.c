#include "../include/debug.h"

unsigned char dmb[200];

void BGB_print_xy()
{
#ifdef _DEBUG_TOOLS_ENABLED

    BGB_MESSAGE_FMT(dmb, "[%d,%d]", position_x, position_y)

#endif
}