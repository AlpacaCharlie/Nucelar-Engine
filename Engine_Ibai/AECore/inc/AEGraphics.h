// ---------------------------------------------------------------------------
// Project Name		:	Alpha Engine
// File Name		:	AEGraphics.h
// Author			:	Sun Tjen Fam
// Creation Date	:	2008/01/30
// Purpose			:	Graphics component header file
// History			:
// - 2008/01/30		:	- initial implementation
// ---------------------------------------------------------------------------

#ifndef AE_GRAPHICS_H
#define AE_GRAPHICS_H

// Comment to build the graphics engine on same thread 
// this has been introduced to allow D3D9 to be called by another thread.
#define AE_GFX_MULTITHREADED


// forward declare AEGfx structures
struct AEGfxTriList;
struct AEGfxTexture;
struct AEGfxFont;
struct AEGfxTextureStage;


// ---------------------------------------------------------------------------
// Defines

// maximum number of triangles per mesh
#define AE_GFX_TRI_NUM_MAX	8192

enum AEGfxBlendMode
{
	AE_GFX_BM_NONE = 0,			// Replaces the frame buffer color with the triangle pixel
	AE_GFX_BM_BLEND,			// Blends the fb color with the tri color using the alpha of the tri: FinalColor = TriColor * TriAlpha + FBColor * (1-TriAlpha)
	AE_GFX_BM_ADD,				// Adds the two colors together : FinalColor = TriColor + FBColor
	AE_GFX_BM_ADD_BLENDALPHA,	// Adds the two colors together and Multiplies the triangle color with its alpha: FinalColor = TriColor * TriAlpha + FBColor
	AE_GFX_BM_MULTIPLY,			// Multiplies the two colors together: FinalColor = TriColor * FBColor
	AE_GFX_BM_NUM				// keeps count of how many blend modes are implemented - also the value returned by AEGfxGetBlendMode if the arguments are set manually
};

// use those in order to have better control over the blending operation
enum AEGfxBlendArgument
{
	AE_GFX_BA_ONE = 0,		// 1
	AE_GFX_BA_ZERO,			// 0
	AE_GFX_BA_SRCCOLOR,		// RGB Color of the triangle pixel
	AE_GFX_BA_SRCALPHA,		// Alpha of the triangle pixel
	AE_GFX_BA_INVSRCALPHA,	// 1-Alpha of the triangle pixel
	AE_GFX_BA_DESTCOLOR,	// RGB color of the pixel currently in the frame buffer
	AE_GFX_BA_DESTALPHA,	// Alpha of the pixel currently in the frame buffer
	AE_GFX_BA_INVDESTALPHA,	// 1-Alpha of the pixel currently in the frame buffer
	AE_GFX_BA_NUM
};

// ---------------------------------------------------------------------------
// Struct/Class definitions

struct AEGfxTriList
{
	void* vtxBuffer;
	u32						vtxNum;
};

// ---------------------------------------------------------------------------
struct AEGfxTexture
{
	void* mTexture;
	u32 mWidth;
	u32 mHeight;
	char mpName[256];
};

// ---------------------------------------------------------------------------
// Extern variables

// assuming a Window of dimensions 800 x 600
extern f32	gAEWinMinX; // -400
extern f32	gAEWinMinY; // -300
extern f32	gAEWinMaxX; // 400
extern f32	gAEWinMaxY; // 300

// ---------------------------------------------------------------------------
// System Functions

bool AEGfxInit(HWND hWin, int win_width, int win_height);
void AEGfxReset();
void AEGfxUpdate();
void AEGfxExit();

void AEGfxStart();
void AEGfxEnd();

//-----------------------------------------------------------------------------
// function to set the current transformation matrix to use
void AEGfxSetTransform(AEMtx33* pMtx);
void AEGfxSetTextureTransform(AEMtx33 * pTexMtx);

//-----------------------------------------------------------------------------
// functions to set the frame buffer's clear color
void				AEGfxSetClearColor(u32 clearColor);
u32					AEGfxGetClearColor();
void				AEGfxClearBuffer();
void				AEGfxClearColorBuffer();
void				AEGfxClearDepthBuffer();
void				AEGfxSetDepthBufferEnabled(bool enabled);
bool				AEGfxGetDepthBufferEnabled();
//-----------------------------------------------------------------------------
// function to set the current modulation color and Texture
void AEGfxSetModulationColor(u32 modColor);
u32	 AEGfxGetModulationColor();
void AEGfxEnableModulationColor(bool enabled);
bool AEGfxGetModulationColorEnabled();

//-----------------------------------------------------------------------------
// Blending operations
void				AEGfxSetBlendMode(AEGfxBlendMode blendMode);
void				AEGfxSetSourceBlendArgument(AEGfxBlendArgument blendArg);
void				AEGfxSetDestBlendArgument(AEGfxBlendArgument blendArg);
AEGfxBlendMode		AEGfxGetBlendMode();
AEGfxBlendArgument	AEGfxGetSourceBlendArgument();
AEGfxBlendArgument	AEGfxGetDestBlendArgument();

//-----------------------------------------------------------------------------
// functions to create a mesh
void			AEGfxTriStart	();
void			AEGfxTriAdd		(f32 x0, f32 y0, u32 c0, f32 tu0, f32 tv0,
								 f32 x1, f32 y1, u32 c1, f32 tu1, f32 tv1,
								 f32 x2, f32 y2, u32 c2, f32 tu2, f32 tv2);

AEGfxTriList*	AEGfxTriEnd		();
void			AEGfxTriDraw	(AEGfxTriList* pTriList);
void			AEGfxTriFree(AEGfxTriList* pTriList);

//-----------------------------------------------------------------------------
// functions to create and destroy a texture 
AEGfxTexture*	AEGfxTextureLoad(char *pFileName);						// from file
AEGfxTexture*	AEGfxTextureLoad(u32 *pPixels, int width, int height);	// from 2D array of pixels
void			AEGfxTextureUnload(AEGfxTexture *pTexture);
void			AEGfxTextureSet(AEGfxTexture *pTexture);				// Use NULL for 'no texture'
void			AEGfxTextureSet(AEGfxTexture *pRedTexture);			// Use NULL for 'no texture'
void			AEGfxTextureSetEx(AEGfxTexture *pTexture, u32 index);	// Use NULL for 'no texture'


//-----------------------------------------------------------------------------
// functions to draw simple primitives
// * these are slow!!! use with caution!!
// * DO NOT call any of these function while building mesh using above functions
void			AEGfxPoint		(f32 x0, f32 y0, f32 z0, u32 c0);
void			AEGfxRect		(f32 x0, f32 y0, f32 z0, f32 w, f32 h, u32 c0);
void			AEGfxRectRot	(f32 x0, f32 y0, f32 z0, f32 w, f32 h, f32 angle_rad, u32 c0);
void			AEGfxLine		(f32 x0, f32 y0, f32 z0, u32 c0, f32 x1, f32 y1, f32 z1, u32 c1);
void			AEGfxCircle		(f32 cx, f32 cy, f32 rad, u32 color);
void			AEGfxTri		(f32 x0, f32 y0, f32 z0, u32 c0, 
								 f32 x1, f32 y1, f32 z1, u32 c1, 
								 f32 x2, f32 y2, f32 z2, u32 c2);
void			AEGfxQuad		(f32 x0, f32 y0, f32 z0, u32 c0, 
								 f32 x1, f32 y1, f32 z1, u32 c1, 
								 f32 x2, f32 y2, f32 z2, u32 c2, 
								 f32 x3, f32 y3, f32 z3, u32 c3);
void			AEGfxBox		(f32 x0, f32 y0, f32 z0, f32 sizeX, f32 sizeY, f32 sizeZ, u32 c0 = 0xFFFFFFFF,u32 c1 = 0xFF808080);
void			AEGfxSphere		(f32 x0, f32 y0, f32 z0, f32 radius, u32 c0 = 0xFFFFFFFF, u32 c1 = 0xFF808080, u32 division = 8);
void			AEGfxCone		(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, f32 radius, u32 c0 = 0xFF808080, u32 c1 = 0xFFFFFFFF, u32 division = 8);
void			AEGfxAxis		(f32 scale);
void			AEGfxFlush();
//-----------------------------------------------------------------------------
// Utility functions
// ----------------------------------------------------------------------------

u32		AEGfxColor		(u32 r, u32 g, u32 b, u32 a = 255);				// Computes a 32-bit ARGB color
void	AEGfxColorComp	(u32 color, u32 *r, u32 *g, u32 *b, u32 *a);	// Extracts the component of a 32-bit ARGB color
u32		AEGfxColInterp	(u32 c0, u32 c1, f32 t);						// Interpolates 2 color values.

// Prints text in screen coordinates (origin is top-left of client area)
void AEGfxPrint(s32 x, s32 y, u32 color, s8* pStr);

//-----------------------------------------------------------------------------
// HOOK TO GFX API - TEMP FOR NOW UNTIL THE WHOLE GRAPHICS ENGINE IS BUILT
// note that this returns a LPDIRECT3DDEVICE9 
void *AEGfxGetDeviceRenderer();

//-----------------------------------------------------------------------------
// SIZE & VIEWPORT METHODS
void			AEGfxSetFullscreen(bool fullscreen);
bool			AEGfxGetFullscreen();
void			AEGfxSetWindowsize(u32 w, u32 h);
void			AEGfxGetScreenSize(u32*sw, u32 *sh);
void			AEGfxResizeFrameBuffer(u32 newWidth, u32 newHeight);
void			AEGfxGetFrameBufferSize(u32* w, u32 *h);
void			AEGfxSetViewport(f32 t, f32 l, f32 b, f32 r);
void			AEGfxGetViewport(f32 *t, f32 *l, f32 *b, f32 *r);
//-----------------------------------------------------------------------------
// EXTRA TRANSFORM
void			AEGfxSetViewTransform(f32 * viewMtx);
void			AEGfxSetProjTransform(f32 * projMtx);
void			AEGfxSetWorldTransform(f32 *  worldMtx);
//-----------------------------------------------------------------------------
// EXTRA RENDERING
void			AEGfxTriDraw(void * pVertices, u32 triCount, bool wireframe = false);
void			AEGfxTriDrawIndexed(void * pVertices, u32 vertCount, s16 *pIndices, u32 triCount, bool wireframe  = false);

//-----------------------------------------------------------------------------
// RENDER TARGET SUPPORT

AEGfxTexture *		AEGfxCreateRenderTex(u32 width, u32 height);
void				AEGfxFreeRenderTex(AEGfxTexture * pRTex);
void				AEGfxSetRenderTex(AEGfxTexture * pRTex);// Note: if pRTex is NULL, the the window back buffer becomes the current render target
AEGfxTexture *		AEGfxGetCurrentRenderTex(); // Note: If this function returns NULL, then the window back buffer is the current render target.

//-----------------------------------------------------------------------------
// FONT SUPPORT
struct AEGfxFont
{
	// D3DXFONT interface
	void*	d3dxFont;
	u32			size;
	u32			weight;
	s8			name[32];
};

//-----------------------------------------------------------------------------
// functions to create and free a font object
AEGfxFont *		AEGfxCreateFont(const char * fontName, u32 size, u32 weight);
void			AEGfxFreeFont(AEGfxFont * pFont);
void			AEGfxFontDraw(f32 x, f32 y, const s8 * pText, AEGfxFont * pFont, u32 color);
void			AEGfxFontDimension(const s8 * pText, AEGfxFont * pFont, f32 * w, f32 * h);
//
////-----------------------------------------------------------------------------
//// TEXTURE STAGES
//
///*
//* NOTE: Code below has been taken from D3D directly
//* Enumerations for COLOROP and ALPHAOP texture blending operations set in
//* texture processing stage controls in D3DTSS.
//*/
//typedef enum _AETEXTUREOP
//{
//	// Control
//	AETOP_DISABLE = 1,      // disables stage
//	AETOP_SELECTARG1 = 2,      // the default
//	AETOP_SELECTARG2 = 3,
//
//	// Modulate
//	AETOP_MODULATE = 4,      // multiply args together
//	AETOP_MODULATE2X = 5,      // multiply and  1 bit
//	AETOP_MODULATE4X = 6,      // multiply and  2 bits
//
//	// Add
//	AETOP_ADD = 7,   // add arguments together
//	AETOP_ADDSIGNED = 8,   // add with -0.5 bias
//	AETOP_ADDSIGNED2X = 9,   // as above but left  1 bit
//	AETOP_SUBTRACT = 10,   // Arg1 - Arg2, with no saturation
//	AETOP_ADDSMOOTH = 11,   // add 2 args, subtract product
//	// Arg1 + Arg2 - Arg1*Arg2
//	// = Arg1 + (1-Arg1)*Arg2
//
//	// Linear alpha blend: Arg1*(Alpha) + Arg2*(1-Alpha)
//	AETOP_BLENDDIFFUSEALPHA = 12, // iterated alpha
//	AETOP_BLENDTEXTUREALPHA = 13, // texture alpha
//	AETOP_BLENDFACTORALPHA = 14, // alpha from AERS_TEXTUREFACTOR
//
//	// Linear alpha blend with pre-multiplied arg1 input: Arg1 + Arg2*(1-Alpha)
//	AETOP_BLENDTEXTUREALPHAPM = 15, // texture alpha
//	AETOP_BLENDCURRENTALPHA = 16, // by alpha of current color
//
//	// Specular mapping
//	AETOP_PREMODULATE = 17,     // modulate with next texture before use
//	AETOP_MODULATEALPHA_ADDCOLOR = 18,     // Arg1.RGB + Arg1.A*Arg2.RGB
//	// COLOROP only
//	AETOP_MODULATECOLOR_ADDALPHA = 19,     // Arg1.RGB*Arg2.RGB + Arg1.A
//	// COLOROP only
//	AETOP_MODULATEINVALPHA_ADDCOLOR = 20,  // (1-Arg1.A)*Arg2.RGB + Arg1.RGB
//	// COLOROP only
//	AETOP_MODULATEINVCOLOR_ADDALPHA = 21,  // (1-Arg1.RGB)*Arg2.RGB + Arg1.A
//	// COLOROP only
//
//	// Bump mapping
//	AETOP_BUMPENVMAP = 22, // per pixel env map perturbation
//	AETOP_BUMPENVMAPLUMINANCE = 23, // with luminance channel
//
//	// This can do either diffuse or specular bump mapping with correct input.
//	// Performs the function (Arg1.R*Arg2.R + Arg1.G*Arg2.G + Arg1.B*Arg2.B)
//	// where each component has been scaled and offset to make it signed.
//	// The result is replicated into all four (including alpha) channels.
//	// This is a valid COLOROP only.
//	AETOP_DOTPRODUCT3 = 24,
//
//	// Triadic ops
//	AETOP_MULTIPLYADD = 25, // Arg0 + Arg1*Arg2
//	AETOP_LERP = 26, // (Arg0)*Arg1 + (1-Arg0)*Arg2
//
//	AETOP_FORCE_DWORD = 0x7fffffff,
//} AETEXTUREOP;
//struct AEGfxTexStage
//{
//	AETEXTUREOP		mColorOp;
//	AETEXTUREOP		mAlphaOp;
//	u32				mColorArg1;
//	u32				mColorArg2;
//	u32				mAlphaArg1;
//	u32				mAlphaArg2;
//};
//
//#define AE_TS_NUM				8			// Maximum number of texture stages
//#define	AE_TS_REACHED_MAX		0xFFFFFFFF	// ERROR: Can't add/push more stages
//#define AE_TS_INVALID_PARAMETER	0xFFFFFFFE	// ERROR: Invalid argument for stage 
//#define AE_TS_INVALID_OPERATION	0xFFFFFFFD	// ERROR: Invalid operation for stage
//#define AE_TS_INVALID_ARGUMENT	0xFFFFFFFC	// ERROR: Invalid operation for stage
//
//u32				AEGfxTexStageGetStageCount();
//u32				AEGfxTexStageReset();
//u32				AEGfxTexStagePush(AEGfxTexStage * stage);
//u32				AEGfxTexStagePop();
//u32				AEGfxTexStageAddAt(u32 index, AEGfxTexStage *stage);
//u32				AEGfxTexStageReplaceAt(u32 index, AEGfxTexStage *stage);
//u32				AEGfxTexStageRemoveAt(u32 index);
//u32				AEGfxTexStageRemoveAll();


// ---------------------------------------------------------------------------
// DEBUGGING
std::list<AEGfxTexture*>	AEGfxGetAllocatedTextures();
u32							AEGfxGetAllocatedTexturesCount();
std::list<AEGfxTexture*>	AEGfxGetAllocatedRenderTextures();
u32							AEGfxGetAllocatedRenderTexturesCount();
std::list<AEGfxTriList*>	AEGfxGetAllocatedTrilist();
u32							AEGfxGetAllocatedTrilistCount();
std::list<AEGfxFont*>	AEGfxGetAllocatedFont();
u32							AEGfxGetAllocatedFontCount();

#endif // AE_GRAPHICS_H

