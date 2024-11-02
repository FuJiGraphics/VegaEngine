#include "pch.h"
#include "ImguiManager.h"
#include "imgui.h"
#include "ImguiSFML/imgui-SFML.h"

namespace fz {

	const fz::Window* ImGuiManager::s_currWindow = nullptr;

	bool ImGuiManager::Init(const fz::Window& window)
	{
		Log.Trace("ImGui �ʱ�ȭ");
		s_currWindow = &window;
		bool result = ImGui::SFML::Init(*(sf::RenderWindow*)window.GetNativeWindow());
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		if (result)
			Log.Trace("ImGui �ʱ�ȭ �Ϸ�");
		else
			Log.Error("ImGui �ʱ�ȭ ����");
		return (result);
	}

	void ImGuiManager::Release()
	{
		Log.Trace("ImGui ����");
		ImGui::SFML::Shutdown();
		//if (s_bEnabledImplot)
		//	ImPlot::DestroyContext();
		Log.Trace("ImGui �Ϸ�");
	}

	void ImGuiManager::PollEvent(const sf::Event& ev)
	{
		ImGui::SFML::ProcessEvent(*(sf::RenderWindow*)s_currWindow->GetNativeWindow(), ev);
	}

	void ImGuiManager::SetWindow(const fz::Window& window)
	{
		s_currWindow = &window;
	}

	void ImGuiManager::SetDocking(bool enabled)
	{
		ImGuiIO& io = ImGui::GetIO();
		if (enabled)
		{
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		}
		else 
		{
			io.ConfigFlags &= ~ImGuiConfigFlags_DockingEnable;         // Enable Docking
			io.ConfigFlags &= ~ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		}
	}

	void ImGuiManager::Begin(const sf::Time& dt)
	{
		auto& renderTarget = *(sf::RenderWindow*)s_currWindow->GetNativeWindow();
		ImGui::SFML::Update(renderTarget, dt);
		ImGui::SFML::SetCurrentWindow(renderTarget);
		ImGuiIO& io = ImGui::GetIO(); (void)io;
 		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID);
		}
	}

	bool ImGuiManager::IsFocusedWindow()
	{
		return ImGui::IsWindowFocused();
	}

	void ImGuiManager::ActivateInputAll(bool enabled)
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (enabled)
		{
			io.WantCaptureKeyboard = true;
			io.WantCaptureMouse = true;
		}
		else
		{
			io.WantCaptureKeyboard = false; // Ű���� �Է��� ImGui�� ���� �ʵ���
			io.WantCaptureMouse = false;    // ���콺 �Է��� ImGui�� ���� �ʵ���
		}
	}

	void ImGuiManager::ActivateInputKeyboard(bool enabled)
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (enabled)
			io.WantCaptureKeyboard = true;
		else
			io.WantCaptureKeyboard = false; // Ű���� �Է��� ImGui�� ���� �ʵ���
	}

	void ImGuiManager::ActivateInputMouse(bool enabled)
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (enabled)
			io.WantCaptureMouse = true;
		else
			io.WantCaptureMouse = false;    // ���콺 �Է��� ImGui�� ���� �ʵ���
	}

	void ImGuiManager::End()
	{
		ImGui::SFML::Render(*(sf::RenderWindow*)s_currWindow->GetNativeWindow());
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}

	void ImGuiManager::ShowDemo()
	{
		bool show_demo_window = true;
		bool show_another_window = true;
		// ImGui::ShowDemoWindow(&show_demo_window);
		static float f = 0.0f;
		static int counter = 0;

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		// Ư�� ���ǿ� ���� �Է� ����
		bool blockInput = true; // �Է��� ������ ���� ���� (���⼭�� �׻� true�� ����)

		ImGui::Begin("Hello, world!");
		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();

		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

} // namespace fz