
#include "src\Engine\AEX.h"
#include <iostream>
#include "imgui\imgui.h"
using namespace AEX;
using namespace ImGui;
using namespace std;
//gl includes
#include "Extern\GL\glew.h"
#include "Extern\GL\wglew.h"
#include "extern\GL\GL.h"

// HELPER FUNCTIONS DECLARATIONS

static GLuint       g_FontTexture = 0;
static int          g_ShaderHandle = 0, g_VertHandle = 0, g_FragHandle = 0;
static int          g_AttribLocationTex = 0, g_AttribLocationProjMtx = 0;
static int          g_AttribLocationPosition = 0, g_AttribLocationUV = 0, g_AttribLocationColor = 0;
static unsigned int g_VboHandle = 0, g_VaoHandle = 0, g_ElementsHandle = 0;

void CreateFontTexture();

void CreateGUIDeviceObject();

void InitializeImGui();

void UpdateImGui();

void DrawImGui();

