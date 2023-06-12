//
// Created by Robert Ristic on 19.05.23.
//
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <memory>
#include <map>
#include <regex>


#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "glad/glad.h"
#include "imnodes.h"

#include "../include/ModuleEditor.h"

#include "../include/modules/Output.h"
#include "../include/modules/SineOscillator.h"
#include "../include/modules/RectOscillator.h"
#include "../include/modules/SawOscillator.h"
#include "../include/modules/EchoNode.h"
#include "../include/modules/DelayNode.h"
#include "../include/modules/NoiseGenerator.h"
#include "../include/modules/Sweep.h"

ModuleEditor::ModuleEditor() : window(ModuleEditor::create_window(1280, 720, "Simple Synth")), _idGenerator() , openSavePopup(false), openOpenPopup(false){
    ImNodes::CreateContext();
}

void ModuleEditor::glfw_error_callback(int error, const char *description) {
    std::cerr << "[Glfw Error] " << error << ": " << description << "\n";
}

/**
 * @brief create window
 * based on https://github.com/JulesFouchy/Simple-ImGui-Setup
 * CC0 1.0 Universal
 *
 * @param width
 * @param height
 * @param title
 * @return
 */
GLFWwindow* ModuleEditor::create_window(int width, int height, const char* title)
{ // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        std::cerr << "Failed to initialize Glfw\n";
        std::terminate();
    }

#if defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create a window\n";
        std::terminate();
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) { // NOLINT
        std::cerr << "Failed to initialize glad\n";
        std::terminate();
    }
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    // ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags /*& ImGuiConfigFlags_ViewportsEnable*/) {
        style.WindowRounding              = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return window;
}

/**
 * @brief begin frame
 * based on https://github.com/JulesFouchy/Simple-ImGui-Setup
 * CC0 1.0 Universal
 */
void ModuleEditor::begin_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    if (ImGui::GetIO().ConfigFlags) {
        static constexpr ImGuiWindowFlags window_flags =
                ImGuiWindowFlags_MenuBar |
                ImGuiWindowFlags_NoBackground |
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoBringToFrontOnFocus |
                ImGuiWindowFlags_NoNavFocus;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        //ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));

        ImGui::Begin("Synth", nullptr, window_flags);
        ModuleEditor::draw_menu();
        ImGui::PopStyleVar(3);
    }
}

/**
 * @brief end frame
 * based on https://github.com/JulesFouchy/Simple-ImGui-Setup
 * CC0 1.0 Universal
 */
void ModuleEditor::end_frame(GLFWwindow *window, ImVec4 background_color) {

    ImGui::End();
    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(background_color.x, background_color.y, background_color.z, background_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
    //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
    if (ImGui::GetIO().ConfigFlags /*& ImGuiConfigFlags_ViewportsEnable*/) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        //ImGui::UpdatePlatformWindows();
        //ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(window);
}

/**
 * @brief end window
 * from https://github.com/JulesFouchy/Simple-ImGui-Setup
 * CC0 1.0 Universal
 *
 * @param window
 */
void ModuleEditor::shutdown(GLFWwindow* window)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void ModuleEditor::draw_menu() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Save..", "Strg+S")) { openSavePopup = true; }
            if (ImGui::MenuItem("Open..", "Strg+O")) { openOpenPopup = true; }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void ModuleEditor::show() {
    ModuleEditor::begin_frame();
    ImNodes::BeginNodeEditor();

    // Key definitions
    const bool KEY_A = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
                            ImNodes::IsEditorHovered() &&
                            ImGui::IsKeyReleased(ImGuiKey_A);

    const bool KEY_ENTER =  ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
                            ImGui::IsKeyDown(ImGuiKey_Enter);

    const bool KEY_ESCAPE = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
                            ImGui::IsKeyDown(ImGuiKey_Escape);

    const bool KEY_STRG_S = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
                            ImNodes::IsEditorHovered() &&
                            (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) || ImGui::IsKeyDown(ImGuiKey_RightCtrl)) &&
                            ImGui::IsKeyReleased(ImGuiKey_S);

    const bool KEY_STRG_O = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
                            ImNodes::IsEditorHovered() &&
                            (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) || ImGui::IsKeyDown(ImGuiKey_RightCtrl)) &&
                            ImGui::IsKeyReleased(ImGuiKey_O);

    if (KEY_STRG_S) { openSavePopup = true; }
    if (KEY_STRG_O) { openOpenPopup = true; }

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.f, 8.f));
    if (!ImGui::IsAnyItemHovered() && KEY_A)
    {
        ImGui::OpenPopup("add node");
    }

    if (ImGui::BeginPopup("add node"))
    {
        //const ImVec2 click_pos = ImGui::GetMousePosOnOpeningCurrentPopup();

        if (ImGui::MenuItem("output"))
        {
            auto module = std::make_shared<Output>();
            _modules.emplace_back(module);
        }

        if (ImGui::MenuItem("SineOscillator"))
        {
            auto module = std::make_shared<SineOscillator>();
            _modules.emplace_back(module);
        }

        if (ImGui::MenuItem("RectOscillator"))
        {
            auto module = std::make_shared<RectOscillator>();
            _modules.emplace_back(module);
        }

        if (ImGui::MenuItem("NoiseGenerator"))
        {
            auto module = std::make_shared<NoiseGenerator>();
            _modules.emplace_back(module);
        }

        if (ImGui::MenuItem("SawOscillator"))
        {
            auto module = std::make_shared<SawOscillator>();
            _modules.emplace_back(module);
        }

        if (ImGui::MenuItem("Sweep"))
        {
            auto module = std::make_shared<Sweep>();
            _modules.emplace_back(module);
        }

        if (ImGui::MenuItem("delay"))
        {
            auto module = std::make_shared<DelayNode>();
            _modules.emplace_back(module);
        }

        if (ImGui::MenuItem("echo"))
        {
            auto module = std::make_shared<EchoNode>();
            _modules.emplace_back(module);
        }

        ImGui::EndPopup();
    }

    /* draw modules */
    for (const auto& module : _modules)
    {
        module->draw();
    }

    /* draw connections */
    for (const auto& conn : _connections)
    {
        ImNodes::Link(conn.conn_id, conn.input_id, conn.output_id);
    }


    ImGui::PopStyleVar();

    ImNodes::EndNodeEditor();

    /* handle new connections */
    int start_id, end_id;
    if (ImNodes::IsLinkCreated(&start_id, &end_id))
    {
        create_connection(start_id, end_id, IdGenerator::generateId());
    }


    // menu bar -> save
    if (openSavePopup) {
        ImGui::OpenPopup("save");
    }
    if (ImGui::BeginPopup("save")) {
        static char textBuffer[256] = "";
        size_t bufferSize = sizeof(textBuffer) - 1;

        ImGui::Text("Save:");
        ImGui::InputText("##Eingabe", textBuffer, bufferSize);
        if (ImGui::Button("Ok") || KEY_ENTER) {
            this->save(textBuffer);
            openSavePopup = false;
            ImGui::CloseCurrentPopup();
        }
        if (ImGui::Button("Cancel") || KEY_ESCAPE) {
            openSavePopup = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //menu bar -> open
    if (openOpenPopup) {
        ImGui::OpenPopup("open");
    }
    if (ImGui::BeginPopup("open")) {
        static char textBuffer[256] = "";
        size_t bufferSize = sizeof(textBuffer) - 1;

        ImGui::Text("Open:");
        ImGui::InputText("##Eingabe", textBuffer, bufferSize);
        if (ImGui::Button("Ok") || KEY_ENTER) {
            this->load(textBuffer);
            openOpenPopup = false;
            ImGui::CloseCurrentPopup();
        }
        if (ImGui::Button("Cancel") || KEY_ESCAPE) {
            openOpenPopup = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    ModuleEditor::end_frame(window, {0.45f, 0.55f, 0.60f, 1.00f});
}

GLFWwindow *ModuleEditor::getWindow() const {
    return window;
}

ModuleEditor::~ModuleEditor() {
    ModuleEditor::shutdown(window);
}

void ModuleEditor::create_connection(int start_id, int end_id,  int conn_id){
    Connector start(INPUT, 0), end(INPUT, 0);
    std::shared_ptr<Module> start_module, end_module;

    auto input_module = getModuleByConnectorId(start_id);
    auto input_connector = input_module->getConnectorById(start_id);
    auto output_module = getModuleByConnectorId(end_id);
    auto output_connector = output_module->getConnectorById(end_id);
    // TODO check if pointer valid

    /* swap if input is not actually the input */
    if (input_connector->type != INPUT) {
       std::swap(input_module, output_module);
       std::swap(input_connector, output_connector);
    }

    /* if they're not both inputs or outputs create connection*/
    if (start.type != end.type)
    {
        /* add link to list */
        Connection conn(output_module, conn_id, start_id, end_id);
        _connections.emplace_back(conn);
        /* add link to corresponding module */
        input_module->addConnection(conn);
    }

    /* if they're not both inputs or outputs create connection*/
    if (input_connector->type != output_connector->type)
    {
        /* add link to list */
        Connection conn(output_module, IdGenerator::generateId(), start_id, end_id);
        _connections.emplace_back(conn);
        /* add link to corresponding module */
        input_module->addConnection(conn);
    }
}

std::shared_ptr<Module> ModuleEditor::find_module_by_id(int id, Connector &conn){
    std::shared_ptr<Module> module;
    for (const auto &m : _modules)
    {
        auto connections = m->getConnections();
        auto found = std::find_if(connections.begin(), connections.end(),
                                  [id](const Connector& m) -> bool { return m.id == id; });
        if (found != connections.end())
        {
            conn = *found;
            return m;
        }
    }
    throw std::invalid_argument("No module with id=" + std::to_string(id) + " in _modules.");
}

void ModuleEditor::save(std::string filename) {
    /* TODO for new modules:
    *  implement NewModule::serialize_settings
    */

    // save the internal imnodes state
    ImNodes::SaveCurrentEditorStateToIniFile((filename + ".ini").c_str());

    // save all modules
    std::ofstream ostream(filename + ".txt");
    for(auto &module_ptr : _modules) {
        module_ptr->serialize(ostream);
    }

    // save IdGenerator state
    ostream << "[IdGenerator_state]" << std::endl
            << IdGenerator::saveId() << std::endl;
    // save all connections
    ostream << "[connections]" << std::endl;
    for(auto &connection : _connections) {
        ostream << "conn_id=" << connection.conn_id
                << " input_id=" << connection.input_id
                << " output_id=" << connection.output_id
                << std::endl;
    }
}

void ModuleEditor::load(std::string filename) {
    /*  TODO for new modules:
    *   1. include new_module.h in this file
    *   2. implement new constructor so every variable can be set manualy from unserialize function
    *   3. implement unserialize function in new_module.h and new_module.cpp
    *   4. add unserialize function to unserializer_map in ModuleEditor::unserialize
    */

    // delete all modules and connections from current memory
    _modules.clear();
    _connections.clear();

    // Load the internal imnodes state
    ImNodes::LoadCurrentEditorStateFromIniFile((filename + ".ini").c_str());

    // Load all modules with their settings
    std::stringstream buffer;
    std::string line;
    std::ifstream ifstream(filename + ".txt");
    while(std::getline(ifstream, line)){
        //save all lines to buffer until empty line
        //then unserialize this buffer and go on with next line
        //stop when reaching connections
        if (line == "[IdGenerator_state]") {          //set IdGenerator state
            std::getline(ifstream, line);
            IdGenerator::loadId(std::stoi(line));
            continue;
        }
        if(line == "[connections]") {
            break;
        }
        if (line.empty()) {
            //create module
            if (buffer.str().empty()) {
                throw std::invalid_argument("ModuleEditor::load -> Can not unserialize empty buffer.");
            }
            _modules.push_back(unserialize_module(buffer));
            buffer.str("");
            buffer.clear();
        } else {
            buffer << line << std::endl;
        }
    }
    unserialize_connections(ifstream);
}

std::shared_ptr<Module> ModuleEditor::unserialize_module(std::stringstream &module_str) {
    // MODULE_CREATORS MAP
    std::map<std::string, std::shared_ptr<Module>(*)(std::stringstream&, int)> unserializer_map;
    unserializer_map["Delay"] = &DelayNode::unserialize;
    unserializer_map["Echo"] = &EchoNode::unserialize;
    unserializer_map["Noise"] = &NoiseGenerator::unserialize;
    unserializer_map["Output"] = &Output::unserialize;
    unserializer_map["RectOscillator"] = &RectOscillator::unserialize;
    unserializer_map["SawOscillator"] = &SawOscillator::unserialize;
    unserializer_map["SineOscillator"] = &SineOscillator::unserialize;
    

    // unserialize general module data
    // variable buffers
    std::string module_name("");
    int module_id(-1);

    // Read stringstream
    std::string line;
    std::regex pattern;
    std::smatch matches;
    while(std::getline(module_str, line)) {
        
        // search for keywords
        if (line == "[module_name]") {          //get module_name
            std::getline(module_str, line);
            module_name = line;
            auto it = unserializer_map.find(module_name);
            if (it == unserializer_map.end()) {
                throw std::invalid_argument("Module \"" + module_name + "\" not found in unserializer_map");
            }
            continue;
        }
        if (line == "[module_id]") {            //get module_id
            std::getline(module_str, line);
            module_id = std::stoi(line);
            continue;
        }
        if (line == "[module_settings]"){       // go into specific module after all basic data was collected
            if (module_str.str().empty() || module_id == -1) {
                throw std::invalid_argument("Can not create a module with following arguments:\nmodule_str= "+ module_str.str()
                                            + "\nmodule_id= " + std::to_string(module_id));
            }
            return unserializer_map[module_name](module_str, module_id);
        }
    }
    throw std::invalid_argument("Could not unserialize following module_str:\n" + module_str.str());
}

std::shared_ptr<Module> ModuleEditor::getModuleByConnectorId(int id) const {
    for (const auto &m : _modules)
    {
        if (m->getConnectorById(id) != nullptr) {
            return m;
        }
    }
    return nullptr;
}

void ModuleEditor::unserialize_connections(std::istream &istream) {
    std::string line;
    std::regex pattern("conn_id=(\\d+) input_id=(\\d+) output_id=(\\d+)");
    std::smatch matches;

    int conn_id;
    int input_id;
    int output_id;
    while (std::getline(istream, line)) {
        //create all connections
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 4) {
                conn_id = std::stoi(matches[1].str());
                input_id = std::stoi(matches[2].str());
                output_id = std::stoi(matches[3].str());
                create_connection(output_id, input_id, conn_id);
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"con_id=(\\d+) out_id=(\\d+) in_id=(\\d+)\":\n" + line );
            }
        }
    }
}