//
// Created by Robert Ristic on 19.05.23.
//
#include <iostream>
#include <algorithm>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "glad/glad.h"
#include "imnodes.h"

#include "../include/ModuleEditor.h"

#include "../include/modules/Oscillator.h"
#include "../include/modules/Output.h"
#include "../include/modules/EchoNode.h"
#include "../include/modules/DelayNode.h"


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
        static constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

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

    /* TODO CLEANUP -----------------------------------------------------------------------------------*/

    /* handle new connections */
    int start_attr, end_attr;
    if (ImNodes::IsLinkCreated(&start_attr, &end_attr))
    {
        Connector start(INPUT, 0), end(INPUT, 0);
        /* find start */
        int id = start_attr;
        std::shared_ptr<Module> start_module;
        for (auto &m : _modules)
        {
            auto connections = m->getConnections();
            auto found = std::find_if(connections.begin(), connections.end(),
                                      [id](const Connector& m) -> bool { return m.id == id; });
            if (found != connections.end())
            {
                start = *found;
                start_module = m;
            }
        }

        /* find end TODO don't duplicate code */
        id = end_attr;
        std::shared_ptr<Module> end_module;
        for (const auto &m : _modules)
        {
            auto connections = m->getConnections();
            auto found = std::find_if(connections.begin(), connections.end(),
                                      [id](const Connector& m) -> bool { return m.id == id; });
            if (found != connections.end())
            {
                end = *found;
                end_module = m;
            }
        }

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
            Connection conn(output_ptr, IdGenerator::generateId(), input_id, output_id);
            _connections.emplace_back(conn);
            /* add link to corresponding module */
            input_ptr->addConnection(conn);
        }
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

GLFWwindow *ModuleEditor::getWindow() const {
    return window;
}

ModuleEditor::~ModuleEditor() {
    ModuleEditor::shutdown(window);
}


