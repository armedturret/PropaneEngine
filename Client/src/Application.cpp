#include "Application.h"

#include "render/components/Model.h"
#include "core/Input.h"
#include "core/components/NoclipController.h"

PE::Application::Application() : _initialized(false),
_renderer(),
_window(),
_dimensions(640, 480),
_deltaTime(0.0),
_previousTime(0.0)
{

}

int PE::Application::run(int argc, char** argv)
{
	//create the window
	if (!glfwInit())
	{
		throw "Failed to initialize glfw";
	}

	//if I wanted to have antialising, using glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //open gl version 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); //forward compatiblity
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //use modern opengl
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //do not allow window resizing

	_window = glfwCreateWindow(_dimensions[0], _dimensions[1], "Skeggy 3 Real??????!?!?", NULL, NULL);
	if (!_window)
	{
		throw "Window failed to initialize";
	}

	glfwMakeContextCurrent(_window);
	glfwSwapInterval(1); //vsync enabled, set to 0 for no vsync

	Input::initializeCallbacks(_window);

	_renderer.initialize();

	//temporarily create a game object with a model
	Model* model = createGameObject()->addComponent<Model>();
	//create a material
	Texture tex;
	tex.loadFromFile("./resources/golden_star.png", true,
		PE::Texture::WRAP_MODE::CLAMP_EDGE,
		PE::Texture::FILTERING::NEAREST_MIPMAP_NEAREST,
		PE::Texture::FILTERING::NEAREST);
	Shader shader;
	shader.compile("./shaders/default.vert", "./shaders/default.frag");
	std::shared_ptr<Material> mat(new Material(tex, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), shader));
	model->loadWithMaterial(mat, false);
	//create another game object for a camera
	GameObject* cameraObject = createGameObject();
	cameraObject->addComponent<Camera>();
	auto nc = cameraObject->addComponent<NoclipController>();
	nc->setSpeed(4.0f);
	nc->setSensitivity(glm::vec2(1.0f));
	cameraObject->getTransform()->setPosition(glm::vec3(-5.0f, 0.0f, 0.0f));

	//initialize all game objects
	for (int i = 0; i < _gameObjects.size(); i++)
	{
		_gameObjects[i].get()->onStart();
	}

	_initialized = true;

	while (!glfwWindowShouldClose(_window))
	{
		_deltaTime = (float)glfwGetTime() - _previousTime;
		_previousTime = (float)glfwGetTime();

		//reset delta for mouse input
		Input::_mouseData.delta = glm::vec2(0.0f);

		//check for input and the like
		glfwPollEvents();

		//game object updates
		for (int i = 0; i < _gameObjects.size(); i++)
		{
			_gameObjects[i].get()->_deltaTime = _deltaTime;
			_gameObjects[i].get()->update();
		}

		//call render pass
		_renderer.render();

		//swap buffers to prevent flickering
		glfwSwapBuffers(_window);
	}

	//don't bother with clean up since called out of scope
	return 0;
}

glm::ivec2 PE::Application::getDimensions() const
{
	return _dimensions;
}

void PE::Application::setDimensions(glm::ivec2 dimensions)
{
	_dimensions = dimensions;
	glfwSetWindowSize(_window, _dimensions[0], _dimensions[1]);
}

PE::GameObject* PE::Application::createGameObject()
{
	//create a unique pointer from the base
	std::shared_ptr<GameObject> temp(new GameObject());

	if (_initialized)
		temp.get()->onStart();

	GameObject* returnVal = temp.get();

	//add to the list
	_gameObjects.push_back(std::move(temp));

	return returnVal;
}

PE::Application::~Application()
{
	for (int i = 0; i < _gameObjects.size(); i++)
	{
		_gameObjects[i].get()->onDestroy();
	}

	_renderer.cleanUp();
	glfwTerminate();
}

PE::Renderer& PE::Application::getRenderer()
{
	return _renderer;
}