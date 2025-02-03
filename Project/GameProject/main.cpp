#include "Game/Game.h"
#include "Game/Title.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl2.h"
#include "imgui/imgui_ja_gryph_ranges.h"

void MainLoop(void) {
	//--------------------------------------------------------------
	//ゲーム中の動きはここに書く
	//ゲーム中はこの関数_を1秒間に60回呼び出している
	//--------------------------------------------------------------
	CRendaring::GetInstance()->Render([]() {
		TaskManager::RenderAll();
	});
	//GUIの描画の前に一度だけ呼び出す
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	TaskManager::DrawAll();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	TaskManager::DeleteChack();
	CInput::Update();
	TaskManager::UpdateAll();
	TaskManager::CollisionAll();
}

void Init(void)
{
	glClearColor(0.0, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);//ブレンドの有効化
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//固定シェーダー用
	glDisable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_ALPHA_TEST);

	CFPS::SetFPS(DEFAULT_FPS);
	//フレーム制御初期化
	CFPS::Init();
	//ボタンの設定
	CInput::Init();
	CInput::SetButton(0, CInput::eButton1, 'Z');
	CInput::SetButton(0, CInput::eButton2, 'X');
	CInput::SetButton(0, CInput::eButton3, 'C');
	CInput::SetButton(0, CInput::eButton4, VK_LSHIFT);
	CInput::SetButton(0, CInput::eButton5, VK_SPACE);
	CInput::SetButton(0, CInput::eButton6, 'Q');
	CInput::SetButton(0, CInput::eButton7, 'E');
	CInput::SetButton(0, CInput::eButton8, 'R');
	CInput::SetButton(0, CInput::eButton9, 'F');
	CInput::SetButton(0, CInput::eButton10, VK_RETURN);
	CInput::SetButton(0, CInput::eButton11, VK_TAB);
	CInput::SetButton(0, CInput::eUp, 'W');
	CInput::SetButton(0, CInput::eDown, 'S');
	CInput::SetButton(0, CInput::eLeft, 'A');
	CInput::SetButton(0, CInput::eRight, 'D');
	CInput::SetButton(0, CInput::eMouseL, VK_LBUTTON);
	CInput::SetButton(0, CInput::eMouseR, VK_RBUTTON);
	CInput::SetButton(0, CInput::eMouseC, VK_MBUTTON);

	//マウス非表示
//	CInput::ShowCursor(false);
//	CInput::SetMouseInside(true);
	CInput::Update();
	CInput::Update();


	//ライト設定
	CLight::SetType(0, CLight::eLight_Direction);
	CLight::SetPos(0, CVector3D(0, 200, 200));
	CLight::SetDir(0, CVector3D(0, -1, 0.5).GetNormalize());
	CLight::SetColor(1, CVector3D(0.4f, 0.4f, 0.4f), CVector3D(0.6f, 0.6f, 0.6f));



	CLight::SetFogParam(CVector4D(1, 1, 1, 1), 1200, 1400);

	//カメラ初期化
	CCamera::GetCamera()->LookAt(CVector3D(5, 5, 5),
		CVector3D(0, 0, 0),
		CVector3D(0.0, 1.0, 0.0));

	SetCurrentDirectory("data");


	//ポストエフェクトを生成		画面解像度,被写界深度オフセット
	CRendaring::CreatInstance(SCREEN_WIDTH, SCREEN_HEIGHT,CVector3D(0.1f,0.85f,0.5f), CRendaring::RendringType::eForward);
	CRendaring::GetInstance()->SetEdge(false);
	CRendaring::GetInstance()->SetDOF(false);
	CShadow::CreateInscance(100, 20, 4096, 4096);
	CShadow::SetShadowAmbient(0.4f);

	CShader::GetInstance("StaticMesh");
	CShader::GetInstance("SkinMesh");
	CSound::GetInstance();
	CLight::Init();


	//-----------------------------------------------------
	//初期化の命令を書く
	//ゲーム起動時に一度だけ呼ばれる
	//-----------------------------------------------------
	//タイプ順に並び替える
	ADD_RESOURCE("Warrior", CModel::CreateModel("chara/Warrior/Warrior.a3m"));                   //プレイヤー
	ADD_RESOURCE("Goblin", CModel::CreateModel("enemy/Goblin/Goblin.a3m"));                      //ゴブリン(敵1)
	ADD_RESOURCE("Mutant", CModel::CreateModel("enemy/Mutant/Mutant.a3m"));                      //ミュータント(敵2)
	ADD_RESOURCE("Vampire", CModel::CreateModel("enemy/Vampire/Vampire.a3m"));                   //ヴァンパイア(敵3)
	ADD_RESOURCE("BeastMan_Wolf", CModel::CreateModel("enemy/BeastMan_Wolf/BeastMan_Wolf.a3m")); //獣人(狼)(敵4)
	ADD_RESOURCE("BeastMan_Deer", CModel::CreateModel("enemy/BeastMan_Deer/BeastMan_Deer.a3m")); //獣人(鹿)(敵5)
	ADD_RESOURCE("Field", CModel::CreateModel("field/field1/field1.obj", 15, 1, 15));            //フィールド
	ADD_RESOURCE("Tower_Base", CModel::CreateModel("tower/TowerBase/TowerBase.obj", 12, 1, 12)); //タワーの土台
	ADD_RESOURCE("Tower_Arrow", CModel::CreateModel("tower/Bow/Bow.obj", 12, 1, 12));            //矢の攻撃をするタワー
	ADD_RESOURCE("Tower_Cannon", CModel::CreateModel("tower/Cannon/Cannon.obj", 12, 1, 12));     //大砲の攻撃をするタワー
	ADD_RESOURCE("Arrow", CModel::CreateModel("wepon/Arrow/Arrow.obj"));                         //矢
	ADD_RESOURCE("Iron Ball", CModel::CreateModel("wepon/Ball/Ball.obj"));                       //大砲の弾
	ADD_RESOURCE("Castle", CModel::CreateModel("castle/Castle/Castle.obj", 12, 1, 12));          //城
	ADD_RESOURCE("Sword", CModel::CreateModel("wepon/Sword/Sword.obj"));                         //プレイヤーの持つ剣
	ADD_RESOURCE("Shield", CModel::CreateModel("wepon/Shield/Shield.obj"));                      //プレイヤーの持つ盾
	ADD_RESOURCE("Sky", CModel::CreateModel("Field/sky/Sky.obj"));                               //スカイボックス
	ADD_RESOURCE("HPBar", CImage::CreateImage("UI/HPBar/gauge.png"));                            //HPバー

	ADD_RESOURCE("Slash", CModel::CreateModel("effect/Slash/Slash.obj"));                        //ひっかき攻撃のエフェクト
	ADD_RESOURCE("Smoke", CModel::CreateModel("effect/Smoke/Smoke.obj"));                        //煙のエフェクト

	ADD_RESOURCE("BackGround", CImage::CreateImage("scene/background1.png")); //タイトル画面の背景
	ADD_RESOURCE("TitleLogo", CImage::CreateImage("scene/TitleLogo.png"));    //タイトルロゴ
	ADD_RESOURCE("Fade", CImage::CreateImage("scene/Fade.png"));              //フェード用の黒画像
	ADD_RESOURCE("GAME START", CImage::CreateImage("scene/GAME START.png"));  //ゲームスタート
	ADD_RESOURCE("GAME CLEAR", CImage::CreateImage("scene/GAME CLEAR.png"));  //ゲームクリア
	ADD_RESOURCE("GAME OVER", CImage::CreateImage("scene/GAME OVER.png"));    //ゲームオーバー
	ADD_RESOURCE("UI", CImage::CreateImage("UI/UI.png"));                     //UI画像

	ADD_RESOURCE("Icon_Arrow", CImage::CreateImage("UI/Icon/Icon_Arrow.png"));     //弓のアイコン
	ADD_RESOURCE("Icon_Cannon", CImage::CreateImage("UI/Icon/Icon_Cannon.png"));   //大砲のアイコン
	ADD_RESOURCE("Icon_Fire", CImage::CreateImage("UI/Icon/Icon_Fire.png"));       //炎のアイコン
	ADD_RESOURCE("Icon_Ice", CImage::CreateImage("UI/Icon/Icon_Ice.png"));         //氷のアイコン
	ADD_RESOURCE("Icon_Thunder", CImage::CreateImage("UI/Icon/Icon_Thunder.png")); //雷のアイコン

	// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	//日本語入力用フォント指定
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 32.0f, NULL, glyphRangesJapanese);
	//(void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

	ImGui_ImplGlfw_InitForOpenGL(GL::window, true);
	ImGui_ImplOpenGL2_Init();

	// Setup style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	//-------------------------------------------------------------------------	
	
	//タイプによるインデックスの使用/不使用を設定
	TaskManager::SetIndexFlag();

	//new Game(); //ゲームを生成
	new Title(); //タイトルを生成
}


void Release()
{
	CLoadThread::ClearInstance();
	CSound::ClearInstance();
	CResourceManager::ClearInstance();
}

static void ResizeCallback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);

	//画面解像度変動
	CCamera::GetCamera()->SetSize((float)w, (float)h);
	//画面解像度固定
	//CCamera::GetCamera()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	CCamera::GetCamera()->Viewport(0, 0, (float)w, (float)h);
	CCamera::GetCurrent()->Perspective(DtoR(60.0), (float)w / (float)h, 0.5, 1000.0);

	glfwGetWindowPos(window, &GL::window_x, &GL::window_y);
	GL::UpdateWindowRect(GL::window_x, GL::window_y, w, h);
	CInput::UpdateClipCursor(true);

}
static void WheelCallback(GLFWwindow* _window, double _offsetx, double _offsety) {
	CInput::AddMouseWheel((int)_offsety);

}
static void PosCallback(GLFWwindow* _window, int x, int y) {
	GL::window_x = x;
	GL::window_y = y;
	GL::UpdateWindosRect(x, y, GL::window_width, GL::window_height);
	CInput::UpdateClipCursor(true);

}
static void FocusCallback(GLFWwindow* _window, int f) {
	CInput::UpdateClipCursor(f);
	GL::focus = f;
}

static void error_callback(int error, const char* description)
{
	printf("Error: %s\n", description);
}

//フルスクリーン?ウインドウモードの切り替え
//Alt+Enterで切り替える
void CheckFullScreen() {
	static int key_enter = 0;
	int key_enter_buf = key_enter;
	if (key_enter_buf ^ (key_enter = glfwGetKey(GL::window, GLFW_KEY_ENTER)) && key_enter && (glfwGetKey(GL::window, GLFW_KEY_LEFT_ALT) || glfwGetKey(GL::window, GLFW_KEY_RIGHT_ALT))) {
		GL::ChangeFullScreen(!GL::full_screen);
	}
}

int __main(int* argcp, char** argv) {
	// メモリリーク検出
	//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//　.dllのパス指定
	//char path[256];
	//GetCurrentDirectory(256, path);
	//strcat_s(path, 255, "\\dll");
	//SetDllDirectory(path);

	//OpenGL4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) return -1;
	//	glutInit(argcp, argv);

	GL::window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple", nullptr, nullptr);
	glfwGetWindowSize(GL::window, &GL::window_width, &GL::window_height);
	glfwGetWindowPos(GL::window, &GL::window_x, &GL::window_y);

	glfwSetFramebufferSizeCallback(GL::window, ResizeCallback);
	glfwSetScrollCallback(GL::window, WheelCallback);
	glfwSetWindowFocusCallback(GL::window, FocusCallback);
	glfwSetWindowPosCallback(GL::window, PosCallback);
	if (!GL::window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(GL::window);
	glfwSwapInterval(0);
	ResizeCallback(GL::window, SCREEN_WIDTH, SCREEN_HEIGHT);

	GLenum err = glewInit();
	if (err == GLEW_OK) {
		printf("%s\n", glewGetString(GLEW_VERSION));
	}
	else {
		printf("%s\n", glewGetErrorString(err));
		getchar();
		return -1;
	}
	HDC glDc = wglGetCurrentDC();
	GL::hWnd = WindowFromDC(glDc);

	Init();


	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	LARGE_INTEGER time_buf;
	QueryPerformanceCounter(&time_buf);
	float fps = 0;
	while (!glfwWindowShouldClose(GL::window)) {
		CheckFullScreen();
		//各バッファーをクリア
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		MainLoop();
		FONT_T()->Draw(0, 32, 1, 0, 0, "fps:%3d", (int)CFPS::GetFPS(), (int)fps);



		glfwSwapBuffers(GL::window);
		CFPS::Wait();

		glfwPollEvents();
		if (glfwGetKey(GL::window, GLFW_KEY_ESCAPE)) {
			GL::isQuit = true;
			glfwSetWindowShouldClose(GL::window, GL_TRUE);
		}

	}

	glfwTerminate();

	Release();
	return 0;
}

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR argv, INT argc)
{
	return __main(&__argc, __argv);
}

int main(int argc, char** argv)
{
	return __main(&argc, argv);
}
