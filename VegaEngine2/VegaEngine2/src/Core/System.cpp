#include "pch.h"
#include "System.h"

namespace fz { 

	System::System(int width, int height, const std::string& title)
		: IsInit(false)
		, IsOpen(true)
		, Width(width)
		, Height(height)
		, Title(title)
		, ObjectGenerator(nullptr)
		, m_Window(nullptr)
		, m_ObjectStack(nullptr)
		, m_RenderContext(nullptr)
	{
		this->Init();
	}

	System::~System()
	{
		this->Release();
	}

	bool System::Init()
	{
		if (IsInit)
			return false;

		bool result = true;
		Log.Trace("System 초기화");
		if (Width <= 0 || Height <= 0)
		{
			Log.Error("윈도우 생성 인자 오류 width = {0}, height = {1}", Width, Height);
			result = false;
		}
		else 
		{
			result = this->GenerateWindow();
			if (result)
				result = this->GenerateObjectStack();
			ImGuiManager::Init(*m_Window);
		}
		if (result)
			Log.Trace("System 초기화 완료");
		else
			Log.Error("System 초기화 실패");
		IsInit = result;
		return result;
	}

	bool System::Release()
	{
		if (!IsInit)
			return false;

		bool result = true;
		Log.Trace("System 해제");
		// Release ObjectStack
		{
			this->ReleaseObjectStack();
		}
		// Window
		{ 
			m_Window->Release();
		}
		// ImGui
		{
			ImGuiManager::Release();
		}
		if (result)
			Log.Trace("System 해제 완료");
		else
			Log.Error("System 해제 실패");
		IsInit = !result;
		return result;
	}

	bool System::Reset()
	{
		bool result = true;
		Log.Trace("System 리셋");
		this->ReleaseObjectStack();

		if (result)
			Log.Trace("System 해제 완료");
		else
			Log.Error("System 해제 실패");
		return result;
	}

	void System::Run()
	{
		Log.Trace("System Run...");
		sf::Clock clock;

		m_Window->ActivateOpenGL(true);
		glViewport(0, 0, static_cast<GLsizei>(m_Window->GetWidth()), static_cast<GLsizei>(m_Window->GetHeight()));
		const sf::Texture texture;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		const GLfloat ratio = static_cast<float>(Width) / static_cast<float>(Height);
		glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);

		// Bind the texture
		glEnable(GL_TEXTURE_2D);
		sf::Texture::bind(&texture);

		// Define a 3D cube (6 faces made of 2 triangles composed by 3 vertices)
		// clang-format off
		static constexpr std::array<GLfloat, 180> cube =
		{
			// positions    // texture coordinates
			-20, -20, -20,  0, 0,
			-20,  20, -20,  1, 0,
			-20, -20,  20,  0, 1,
			-20, -20,  20,  0, 1,
			-20,  20, -20,  1, 0,
			-20,  20,  20,  1, 1,

			 20, -20, -20,  0, 0,
			 20,  20, -20,  1, 0,
			 20, -20,  20,  0, 1,
			 20, -20,  20,  0, 1,
			 20,  20, -20,  1, 0,
			 20,  20,  20,  1, 1,

			-20, -20, -20,  0, 0,
			 20, -20, -20,  1, 0,
			-20, -20,  20,  0, 1,
			-20, -20,  20,  0, 1,
			 20, -20, -20,  1, 0,
			 20, -20,  20,  1, 1,

			-20,  20, -20,  0, 0,
			 20,  20, -20,  1, 0,
			-20,  20,  20,  0, 1,
			-20,  20,  20,  0, 1,
			 20,  20, -20,  1, 0,
			 20,  20,  20,  1, 1,

			-20, -20, -20,  0, 0,
			 20, -20, -20,  1, 0,
			-20,  20, -20,  0, 1,
			-20,  20, -20,  0, 1,
			 20, -20, -20,  1, 0,
			 20,  20, -20,  1, 1,

			-20, -20,  20,  0, 0,
			 20, -20,  20,  1, 0,
			-20,  20,  20,  0, 1,
			-20,  20,  20,  0, 1,
			 20, -20,  20,  1, 0,
			 20,  20,  20,  1, 1
		};
		// clang-format on

		// Enable position and texture coordinates vertex components
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), cube.data());
		glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), cube.data() + 3);

		// Disable normal and color vertex components
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		m_Window->ActivateOpenGL(false);
		while (m_Window->IsOpen())
		{
			sf::Time t = clock.restart();
			float dt = t.asSeconds();
			// Event
			m_Window->OnEvent();
			if (!m_Window->IsOpen())
				continue;

			// Update
			for (Object* obj : *m_ObjectStack)
			{
				if (obj != nullptr)
				{
					obj->OnUpdate(dt);
				}
			}

			// clear the buffers
			m_Window->ActivateOpenGL(true);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// We get the position of the mouse cursor (or touch), so that we can move the box accordingly
			sf::Vector2i pos;
			pos = sf::Mouse::getPosition();

			const float x = static_cast<float>(pos.x) * 200.f / static_cast<float>(Width) - 100.f;
			const float y = -static_cast<float>(pos.y) * 200.f / static_cast<float>(Height) + 100.f;
			// Apply some transformations
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(x, y, -100.f);
			glRotatef(clock.getElapsedTime().asSeconds() * 50.f, 1.f, 0.f, 0.f);
			glRotatef(clock.getElapsedTime().asSeconds() * 30.f, 0.f, 1.f, 0.f);
			glRotatef(clock.getElapsedTime().asSeconds() * 90.f, 0.f, 0.f, 1.f);
			// Draw the cube
			glDrawArrays(GL_TRIANGLES, 0, 36);
			m_Window->ActivateOpenGL(false);

			// sf Draw

			// ImGui
			ImGuiManager::Begin(t);
			{
				ImGuiManager::ShowDemo();
			}
			ImGuiManager::End();

			// OpenGLdraw...
			m_Window->OnUpdate();
		}
		Log.Trace("System Run Off");
	}

	void System::OnEvent(fz::Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(System::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(System::OnWindowResize));
		for (Object* obj : *m_ObjectStack)
		{
			if (obj != nullptr)
			{
				obj->OnEvent(e);
			}
		}
	}

	void System::PushObject(Object* object)
	{
		m_ObjectStack->PushObject(object);
	}

	void System::PushOverlay(Object* overlay)
	{
		m_ObjectStack->PushObject(overlay);
	}

	bool System::OnWindowClose(WindowCloseEvent e)
	{
		m_Window->Release();
		return true;
	}

	bool System::OnWindowResize(WindowResizeEvent e)
	{ 
		m_Window->ActivateOpenGL(true);
		m_RenderContext->SetViewport(
			0, 0,
			m_Window->GetWidth(),
			m_Window->GetHeight()
		);
		m_Window->ActivateOpenGL(false);
		return true;
	}

	bool System::GenerateWindow()
	{
		bool result = true;
		WindowMode winMode;
		winMode.Width = Width;
		winMode.Height = Height;
		winMode.Title = Title;
		winMode.Api = WindowAPI::SFML;
		winMode.VSync = true;
		m_Window = Window::Create(winMode);
		// Render Context
		m_RenderContext = RenderContext::Create();
		if (m_Window != nullptr)
		{
			m_Window->SetEventCallback(BIND_EVENT_FUNC(System::OnEvent));
			m_Window->Init(m_RenderContext);
		}
		else
		{
			Log.Error("윈도우 생성중 문제를 알 수 없는 오류가 발생했습니다.");
			result = false;
		}
		if (result)
			Log.Trace("Window 생성 완료");
		else
			Log.Error("Window 생성 실패");
		return result;
	}

	bool System::GenerateObjectStack()
	{
		bool result = true;
		if (m_ObjectStack && m_ObjectStack->size() > 0)
		{
			Log.Warn("Object 스택이 이미 생성 되어 있습니다.");
			result = false;
		}
		else 
		{
			Log.Trace("Object Pool 생성");
			ObjectGenerator = CreateShared<ObjectPool>();
			Log.Trace("Object 스택 생성");
			m_ObjectStack = CreateShared<ObjectStack>(ObjectGenerator);
			if (m_ObjectStack == nullptr)
				result = false;
		}
		if (result)
			Log.Trace("Object 스택 생성 완료");
		else
			Log.Error("Object 스택 생성 실패");
		return result;
	}

	bool System::ReleaseObjectStack()
	{
		bool result = true;
		Log.Trace("Object 스택 해제");
		m_ObjectStack->Release();

		if (result)
			Log.Trace("Object 스택 해제 완료");
		else
			Log.Error("Object 스택 해제 실패");
		return result;
	}

} // namespace fz
