#ifndef MESHCREATION_H_
#define MESHCREATION_H_

// forward declare the triangle list structure
struct AEGfxTriList;

AEGfxTriList * MakeQuad(u32 color);
AEGfxTriList * MakeCircle(u32 precision, u32 color);

#endif