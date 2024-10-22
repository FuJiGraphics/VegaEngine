#include "Core/stdafx.h"
#include "ImguiManager.h"

namespace fz {

	bool ImGuiManager::s_enableOverviewDockspace = true;
	const fz::Window* ImGuiManager::s_currWindow = nullptr;

	bool ImGuiManager::Init(const fz::Window& window)
	{
		s_currWindow = &window;
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		return (ImGui::SFML::Init(window.GetHandle()));
	}

	void ImGuiManager::Shutdown()
	{
		ImGui::SFML::Shutdown();
		//if (s_bEnabledImplot)
		//	ImPlot::DestroyContext();
	}

	void ImGuiManager::SetWindow(const fz::Window& window)
	{
		s_currWindow = &window;
	}

	void ImGuiManager::Begin(const sf::Time& dt)
	{
		auto& renderTarget = s_currWindow->GetHandle();
		ImGui::SFML::Update(renderTarget, dt);
		ImGui::SFML::SetCurrentWindow(renderTarget);
		if (s_enableOverviewDockspace)
		{
			ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID);
		}
	}

	void ImGuiManager::End()
	{
		ImGui::SFML::Render(s_currWindow->GetHandle());
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
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

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

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