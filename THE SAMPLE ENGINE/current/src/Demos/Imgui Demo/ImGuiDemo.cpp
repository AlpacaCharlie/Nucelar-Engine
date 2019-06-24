#include "ImGuiDemo.h"
#include "../../Engine/ImGui/Gui.h"

void TopBar() {
	if (BeginMainMenuBar()) {
		if (BeginMenu("File")) {
			if (MenuItem("New", "Ctrl + N")) {
				cout << "New\n";
			}
			if (MenuItem("Open", "Crtl + O")) {
				cout << "Open\n";
			}
			if (MenuItem("Save", "Crtl + S")) {
				cout << "Save\n";
			}
			if (MenuItem("Save as")) {
				cout << "Save as\n";
			}
			ImGui::EndMenu();
		}


		//include more taps in top bar here


		ImGui::SameLine(GetWindowSize().x -108);
		if (BeginMenu("Close editor")) {
			exit(1);
		}
		
	}



	ImGui::EndMainMenuBar();
}
AEX::Transform tr{ AEVec2{100.0f,100.0f}, AEVec2{10.0f,10.0f}, PI };
bool gVisible = true;
void GameObjectWindow() {
	
	if (Begin("Game Object")) {
		if (CollapsingHeader("Object")) {
			if (TreeNode("Transform")) {
				Text("Position");
				DragFloat3("a", tr.mTranslationZ.v, 0.5f, -10000.0f, 10000.0f); 
				Text("Scale");
				DragFloat2("b", tr.mScale.v, 0.5f, 0.0f, 10000.0f);
				Text("Rotation");
				DragFloat("c", &tr.mOrientation, 0.5f, 0.0f, 2.0f * PI);
				
				TreePop();
			}
			
			if (TreeNode("Texture")) {
				TreePop();
			}
			
			if (MenuItem("Create")) {
				cout << "New game object created\n";
			}
			if (MenuItem("Delete")) {
				cout << "Game object deleted\n";
			}

			Checkbox("Visible", &gVisible);

			if (gVisible == true)
				cout << "Window is visible\n";
			else
				cout << "Window hidden\n";

			//TreePop();
		}
	}
	End();
}

void MyEditor() {

	TopBar();
	
	GameObjectWindow();
	
}
// ----------------------------------------------------------------------------
// GAMESTATE FUNCTIONS
void ImGuiDemo::Initialize(){
	// initialize ImGui
	InitializeImGui();
}
void ImGuiDemo::LoadResources()
{
	// Images
	aexGraphics->LoadTexture(".\\data\\Images\\Default.png");

	// Models
	aexGraphics->LoadModel(".\\data\\Models\\Quad.model");
}
void ImGuiDemo::Update()
{
	// get main window dimensions
	auto mainWin = aexWindowMgr->GetMainWindow();
	auto winWH = AEVec2(f32(mainWin->GetWidth()), f32(mainWin->GetHeight()));

	// control the engine
	if (aexInput->KeyTriggered('B'))
		aexTime->LockFrameRate(!aexTime->FrameRateLocked());
	if (aexInput->KeyTriggered('V'))
		aexGraphics->SetVSyncEnabled(!aexGraphics->GetVSyncEnabled());
	if (aexInput->KeyPressed(VK_OEM_PLUS))
		aexTime->SetMaxFrameRate(aexTime->GetMaxFrameRate() + 1.0);
	if (aexInput->KeyPressed(VK_OEM_MINUS))
		aexTime->SetMaxFrameRate(aexTime->GetMaxFrameRate() - 1.0);
	if (aexInput->KeyTriggered('F'))
		mainWin->SetFullScreen(!mainWin->GetFullScreen());

	f32 fps = (f32)aexTime->GetFrameRate();
	std::string wintitle = "Simple Demo - FPS: "; wintitle += std::to_string(fps);
	if (aexTime->FrameRateLocked())	wintitle += "(LOCKED)";
	wintitle += " - VSYNC: ";	wintitle +=	aexGraphics->GetVSyncEnabled() ? "ON" : "OFF";
	wintitle += " - Controls: FPS: 'B', '+/-'. VSYNC: 'V'";
	aexWindowMgr->GetMainWindow()->SetTitle(wintitle.c_str());


	Logic::Instance()->Update();

}
void ImGuiDemo::Render()
{
	auto mainWin = aexWindowMgr->GetMainWindow();
	auto winWH = AEVec2(f32(mainWin->GetWidth()), f32(mainWin->GetHeight()));

	aexGraphics->SetViewport(0, 0, s32(winWH.x), s32(winWH.y));
	aexGraphics->SetClearColor(Color(0.7f,0.7f,0.7f,1.0f));
	aexGraphics->ClearFrameBuffer();

	UpdateImGui();
	//ShowDemoWindow();
	MyEditor();
	DrawImGui();

	aexGraphics->Present();
}
