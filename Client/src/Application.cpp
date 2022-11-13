#include "Application.h"

#include <iostream>

#include "imgui.h"
#include "render/imgui/imgui_impl_opengl3.h"
#include "render/imgui/imgui_impl_glfw.h"

#include "render/components/MeshRenderer.h"
#include "render/Model.h"
#include "core/Input.h"
#include "core/components/NoclipController.h"

PE::Application::Application() : _initialized(false),
_renderer(),
_window(),
_dimensions(800, 600),
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
	glfwWindowHint(GLFW_SAMPLES, 4); //4 samples for antialiasing

	_window = glfwCreateWindow(_dimensions[0], _dimensions[1], "Skeggy 3 Real??????!?!?", NULL, NULL);
	if (!_window)
	{
		throw "Window failed to initialize";
	}

	glfwMakeContextCurrent(_window);
	glfwSwapInterval(1); //vsync enabled, set to 0 for no vsync

	Input::initializeCallbacks(_window);

	_renderer.initialize();

	//setup IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init("#version 460 core");
	//set style to look cool
	ImGui::StyleColorsDark();

	//create the root object
	_root = std::make_shared<GameObject>();
	_root->setName("Scene Root");
	/*TEMP CODE START*/
	_renderer.getLightingData()->ambient = Color(100, 100, 100);

	//create a material
	Texture doorTex;
	doorTex.loadFromFile("./resources/door.png", true,
		PE::Texture::WRAP_MODE::CLAMP_EDGE,
		PE::Texture::FILTERING::NEAREST_MIPMAP_NEAREST,
		PE::Texture::FILTERING::NEAREST);
	Shader shader;
	shader.compile("./shaders/default.vert", "./shaders/default.frag");
	std::shared_ptr<Material> doorMat(new Material({ doorTex }, {}, WHITE, shader));

	Texture metal;
	metal.loadFromFile("./resources/metal.png", true,
		PE::Texture::WRAP_MODE::CLAMP_EDGE,
		PE::Texture::FILTERING::NEAREST_MIPMAP_NEAREST,
		PE::Texture::FILTERING::NEAREST);
	std::shared_ptr<Material> metalMat(new Material({ metal }, {}, WHITE, shader));

	//create a light
	GameObject* lightObject = createGameObject();
	lightObject->setName("Light");
	lightObject->getTransform()->setPosition(glm::vec3(-3.0f, 1.0f, 0.0f));
	lightObject->addComponent<Light>()->setLight(Light::TYPE::POINT, Color(100, 100, 100));

	//create a model object
	Model model;
	model.loadFromFile("./resources/door.fbx");
	model.setMaterials({ metalMat, doorMat });
	GameObject* doorObject = model.createInstance();
	doorObject->getTransform()->setScale(glm::vec3(0.01f));

	//create another game object for a camera
	GameObject* cameraObject = createGameObject();
	cameraObject->setName("Camera");
	cameraObject->addComponent<Camera>();
	auto nc = cameraObject->addComponent<NoclipController>();
	nc->setSpeed(4.0f);
	nc->setSensitivity(glm::vec2(0.1f));
	cameraObject->getTransform()->setPosition(glm::vec3(-5.0f, 0.0f, 0.0f));

	float yaw = 0.0f;
	/*TEMP CODE END*/

	//initialize all game objects
	_root->onStart();

	_initialized = true;

	while (!glfwWindowShouldClose(_window))
	{
		_deltaTime = (float)glfwGetTime() - _previousTime;
		_previousTime = (float)glfwGetTime();

		//reset delta for mouse input
		Input::_mouseData.delta = glm::vec2(0.0f);

		//poll inputs
		glfwPollEvents();

		//start new imgui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//game object updates
		_root->update(_deltaTime);

		//call render pass
		_renderer.render();

		//call gui pass
		_root->onGUI();
		
		//draw scene graph
		ImGui::Begin("Scene Graph");
		for (auto child : _root->getChildren())
		{
			drawSceneGraph(child);
		}
		ImGui::End();

		//render imgui stuff
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
		temp->onStart();

	GameObject* returnVal = temp.get();

	//add this to be parented to the root object by default
	temp->getTransform()->setParent(_root->getTransform());

	//add to the list
	_gameObjects.push_back(std::move(temp));

	return returnVal;
}

PE::Application::~Application()
{
	_root->onDestroy();

	//cleanup imgui stuff
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	_renderer.cleanUp();
	glfwTerminate();
}

PE::Renderer& PE::Application::getRenderer()
{
	return _renderer;
}

void PE::Application::drawSceneGraph(GameObject* node)
{
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_AllowItemOverlap;
	if (node->getChildren().size() == 0)
		flags |= ImGuiTreeNodeFlags_Leaf;
	if (ImGui::TreeNodeEx(node->getName().c_str(), flags))
	{
		for (auto child : node->getChildren())
		{
			drawSceneGraph(child);
		}
		ImGui::TreePop();
	}
}