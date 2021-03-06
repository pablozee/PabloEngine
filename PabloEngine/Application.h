#pragma once
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "Renderer/Renderer.h"
#include "Common.h"

class Application
{
public:
	Application();
	virtual ~Application();

	int Run();
	
	void OnEvent(Event& event);

	inline static Application& Get() { return *s_Instance; }

	inline Window& GetWindow() { return *m_Window; }

private:
	bool m_Running = true;
	bool OnWindowClose(WindowCloseEvent& event);
	bool OnWindowResize(WindowResizeEvent& event);

	void CalculateFrameStats();

	Renderer m_Renderer;
	std::unique_ptr<Window> m_Window;
	static Application* s_Instance;

	bool m_AppPaused	   = false;
	bool m_Minimized	   = false;
	bool m_Maximized	   = false;
	bool m_Resizing		   = false;
	bool m_FullScreenState = false;
};
