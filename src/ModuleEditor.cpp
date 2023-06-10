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

#include "../include/modules/Oscillator.h"
#include "../include/modules/Output.h"


ModuleEditor::ModuleEditor() : window(ModuleEditor::create_window(1280, 720, "Simple Synth")), _idGenerator() {
    ImNodes::CreateContext();
}

void ModuleEditor::glfw_error_callback(int error, const char *description) {
    std::cerr << "[Glfw Error] " << error << ": " << description << "\n";
}

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

void ModuleEditor::begin_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    if (ImGui::GetIO().ConfigFlags) {
        static constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        //ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));

        ImGui::Begin("MyMainDockSpace", nullptr, window_flags);
        ImGui::PopStyleVar(3);
        ImGui::End();
    }
}

void ModuleEditor::end_frame(GLFWwindow *window, ImVec4 background_color) {
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

void ModuleEditor::shutdown(GLFWwindow* window)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void ModuleEditor::show() {
    ModuleEditor::begin_frame();
    ModuleEditor::draw_menu();
    ImNodes::BeginNodeEditor();

    const bool open_popup = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
                            ImNodes::IsEditorHovered() &&
                            ImGui::IsKeyReleased(ImGuiKey_A);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.f, 8.f));
    if (!ImGui::IsAnyItemHovered() && open_popup)
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

        if (ImGui::MenuItem("oscillator"))
        {
            auto module = std::make_shared<Oscillator>();
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

    /* TODO CLEANUP -----------------------------------------------------------------------------------*/

    /* handle new connections */
    int start_attr, end_attr;
    if (ImNodes::IsLinkCreated(&start_attr, &end_attr))
    {
        create_connection(start_attr, end_attr);
#if 0
        const bool valid_link = start_type != end_type;
        if (valid_link)
        {
            // Ensure the edge is always directed from the value to
            // whatever produces the value
            if (start_type != NodeType::value)
            {
                std::swap(start_attr, end_attr);
            }
            graph_.insert_edge(start_attr, end_attr);
        }
#endif

        /* TODO CLEANUP -----------------------------------------------------------------------------------*/

        /* TODO delete nodes and connections */
    }

    ModuleEditor::end_frame(window, {0.45f, 0.55f, 0.60f, 1.00f});
}

void ModuleEditor::draw_menu() {
    static constexpr ImGuiWindowFlags menue_bar_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBackground;
    ImGui::Begin("MyMainDockSpace", nullptr, menue_bar_flags);
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open..", "")) { this->load(); }
            if (ImGui::MenuItem("Save", ""))   { this->save(); }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    ImGui::End();
}

GLFWwindow *ModuleEditor::getWindow() const {
    return window;
}

ModuleEditor::~ModuleEditor() {
    ModuleEditor::shutdown(window);
}

void ModuleEditor::create_connection(int start_attr, int end_attr,  int conn_id){
    Connector start(INPUT, 0), end(INPUT, 0);
    std::shared_ptr<Module> start_module, end_module;

    /* find start and end */
    start_module = find_module_by_id(start_attr, start);
    end_module = find_module_by_id(end_attr, end);

    /* swap swap start and end nodes based on connection type */
    int input_id, output_id;
    std::shared_ptr<Module> output_ptr, input_ptr;
    if (start.type == INPUT)
    {
        input_id = start_attr;
        output_id = end_attr;
        output_ptr = end_module;
        input_ptr = start_module;
    } else {
        input_id = end_attr;
        output_id = start_attr;
        output_ptr = start_module;
        input_ptr = end_module;
    }

    /* if they're not both inputs or outputs create connection*/
    if (start.type != end.type)
    {
        /* add link to list */
        Connection conn(output_ptr, conn_id, input_id, output_id);
        _connections.emplace_back(conn);
        /* add link to corresponding module */
        input_ptr->addConnection(conn);
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

void ModuleEditor::save() {
    // save the internal imnodes state
    ImNodes::SaveCurrentEditorStateToIniFile("save_load.ini");

    // save all modules
    std::ofstream ostream("save_test.txt");
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

void ModuleEditor::load() {
    /*  TODO for new modules
    *   1. include new_module.h in this file
    *   2. implement new constructor so every variable can be set manualy from unserialize function
    *   3. implement unserialize function in new_module.h and new_module.cpp
    *   4. add unserialize function to unserializer_map in ModuleEditor::unserialize
    */

    // delete all modules and connections from current memory
    _modules.clear();
    _connections.clear();
    
    // Load the internal imnodes state
    ImNodes::LoadCurrentEditorStateFromIniFile("save_load.ini");
    
    // Load all modules with their settings
    std::stringstream buffer;
    std::string line;
    std::ifstream ifstream("save_test.txt");
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
                throw std::invalid_argument("Can not unserialize empty buffer.");
            }
            _modules.push_back(unserialize_module(buffer));
            buffer.str("");
        } else {
            buffer << line << std::endl;
        }
    }
    ifstream.seekg(0);
    unserialize_connections(ifstream);
}

std::shared_ptr<Module> ModuleEditor::unserialize_module(std::stringstream &module_str)
{
    // MODULE_CREATORS MAP
    std::map<std::string, std::shared_ptr<Module>(*)(std::stringstream&, int, std::vector<Connector>)> unserializer_map;
    unserializer_map["Oscillator"] = &Oscillator::unserialize;
    unserializer_map["Output"] = &Output::unserialize;

    // unserialize general module data
    // Flags
    bool module_connectors_f(false);

    // variable buffers
    std::string module_name("");
    int module_id(-1);
    std::vector<Connector> module_connectors;

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
        if (line == "[module_connectors]") {    //set module_connectors flag
            module_connectors_f = true;
            continue;
        }
        if (line == "[module_settings]"){       // go into specific module after all basic data was collected
            if (module_str.str().empty() || module_id == -1 || module_connectors.size() == 0) {
                throw std::invalid_argument("Can not create a module with following arguments:\nmodule_str= "+ module_str.str()
                                            + "\nmodule_id= " + std::to_string(module_id)
                                            + "\nmodule_connectors.size()= " + std::to_string(module_connectors.size()));
            }
            module_str.seekg(0);
            return unserializer_map[module_name](module_str, module_id, module_connectors);
        }

        // process flags
        if (module_connectors_f) {              //get all module_connectors
            pattern = "id=(\\d+) type=(\\d+)";
            if (std::regex_search(line, matches, pattern)) {
                if (matches.size() == 3) {
                    ConnectorType type;
                    int id = std::stoi(matches[1].str());
                    int type_int = std::stoi(matches[2].str());
                    switch (type_int) {
                    case 0: type = INPUT;
                            break;
                    case 1: type = OUTPUT;
                            break;
                    default:
                        throw std::invalid_argument(std::to_string(type_int) + " is not a valid ConnectorType ENUM");
                    }
                    module_connectors.emplace_back(Connector(type, id));
                    continue;
                } else {
                    throw std::invalid_argument("Following line does not follow the pattern \"id=(\\d+) type=(\\d+)\":\n" + line );
                }
            }
        }
    }
    throw std::invalid_argument("Could not unserialize following module_str:\n" + module_str.str());
}

void ModuleEditor::unserialize_connections(std::istream &istream) {
    std::string line;
    bool connections_f(false);
    std::regex pattern("conn_id=(\\d+) input_id=(\\d+) output_id=(\\d+)");
    std::smatch matches;

    int conn_id;
    int input_id;
    int output_id;
    while (std::getline(istream, line)) {
        // search istream until connections
        if(line == "[connections]") {
            connections_f = true;
            continue;
        }
        //create all connections
        if (connections_f && !line.empty()) {
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
}