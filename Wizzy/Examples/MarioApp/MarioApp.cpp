#include "pch.h"
#include <Wizzy.h>

struct ExampleComponent : public wz::Component<ExampleComponent>
{
	wz::Texture::Handle hMarioTexture; // The handle to be associated with the mario texture in ResourceManagement
	vec2 position = vec2(0, 0); // The position to render the mario texture at
	wz::Shader::Handle hShader; // The shader to be used in rendering
	mat4 projection; // The view projection to be used for rendering
};

class ExampleSystem : public wz::System
{
public:
	ExampleSystem()
	{
		AddComponentType<ExampleComponent>();

		Subscribe(wz::EventType::app_init);
		Subscribe(wz::EventType::app_update);
		Subscribe(wz::EventType::app_render);
		Subscribe(wz::EventType::window_resize);
	}

	virtual void OnEvent(const wz::Event& e, wz::ComponentGroup& components) const override
	{
		ExampleComponent* component = components.Get<ExampleComponent>();

		switch (e.GetEventType())
		{
			case wz::EventType::app_init:
			{
				WZ_DEBUG("Init event!");

				// Set the root resource directory
				wz::ResourceManagement::SetResourceDir("../res/");

				// IMPORTANT!! Always save handles for resources. If you lose a handle,
				// the only way to access the resource is by knowing it's exact res path/name.
				// Think of resource handles as C++ pointers.
				// Load mario.png from root resource directory ("../res/mario.png")
				component->hMarioTexture = wz::ResourceManagement::Load<wz::Texture>("mario.png");

				// Load the texture shader
				component->hShader = wz::ResourceManagement::Load<wz::Shader>("texture2d.shader");

				// Handles can be redeemed for a reference to the resource. It's recommended
				// that you don't save any form of resource references, and only use the 
				// resource handles.
				// Retrieve the texture associated with the handle, and print some properties
				wz::Texture& marioTexture = wz::ResourceManagement::Get<wz::Texture>(component->hMarioTexture);
				WZ_DEBUG("Texture width: {0}, height: {1}", marioTexture.GetWidth(), marioTexture.GetHeight());

				// Get a reference to the application window
				auto& window = wz::Application::Get().GetWindow();
				// Set the view projection to a normal 2D projection aligned with the window
				component->projection = glm::ortho<float>(0, window.GetWidth(), 0, window.GetHeight());

				// Set the clear background color to blue
				wz::RenderCommand::SetClearColor(wz::Color::blue);

				// Enable blending for transparent background on textures
				wz::RenderCommand::ToggleBlending(true);

				return;
			}
			case wz::EventType::app_update:
			{
				// Cast into respective event type to get the event data
				auto& updateEvent = (const wz::AppUpdateEvent&)e;

				// Move the mario texture each frame based on delta time
				component->position += vec2(5.f * updateEvent.GetDeltaTime());

				return;
			}
			case wz::EventType::app_render:
			{
				// Clear the render pipeline and draw anything rendered to the window
				wz::RenderCommand::Clear();

				// Begin the renderer to be ready to draw a scene using given shader
				wz::Renderer2D::Begin(component->hShader, component->projection);

				// Submit the mario texture for drawing at the position, a scale of 1, a 
				// rotation of 1 and with the color white (to render with default colors)
				wz::Renderer2D::SubmitImage(component->hMarioTexture, component->position, vec2(1.f), 0, wz::Color::white);

				// Tell the renderer we are done submitting and render all submissions
				wz::Renderer2D::End();

				return;
			}
			case wz::EventType::window_resize:
			{
				// Update the projection to the new window size
				auto& window = wz::Application::Get().GetWindow();
				component->projection = glm::ortho<float>(0, window.GetWidth(), 0, window.GetHeight());
			}
		}
	}

};

class MarioApp : public wz::Application
{
public:

	virtual void Init() override
	{
		// Hide core trace messages
		wz::Log::SetCoreLogLevel(LOG_LEVEL_DEBUG);

		WZ_DEBUG("Initializing!");

		// Create an entity with and ExampleComponent
		m_clientEcs.CreateEntity<ExampleComponent>();

		// Register the ExampleSystem to be notified on events
		m_clientSystems.AddSystem<ExampleSystem>();
	}

	virtual void Shutdown() override
	{
		WZ_DEBUG("Shutting down!");
	}
};

// This is essential for the Core library to get an instance of the app!
wz::Application* CreateApplication()
{
	return new MarioApp();
}