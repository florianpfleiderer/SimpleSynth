//
// Created by Robert Ristic on 19.05.23.
//

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#ifndef SIMPLESYNTH_MODULEEDITOR_H
#define SIMPLESYNTH_MODULEEDITOR_H


#include "IdGenerator.h"

#include "WindowHost.h"
#include "modules/Module.h"


#include <memory>


#include <memory>


class ModuleEditor {
public:

    ModuleEditor();
    ModuleEditor(GLFWwindow* window);
    virtual ~ModuleEditor();
    [[nodiscard]] GLFWwindow* getWindow() const;
    // void setWindow(GLFWwindow* window);
    void show();
    void save(std::string filename);
    void load(std::string filename);
    [[nodiscard]] std::vector<std::shared_ptr<Module>> get_modules() const;
    [[nodiscard]] std::vector<Connection> get_connections() const;

private:
    GLFWwindow* const window;
    const IdGenerator _idGenerator;
    std::vector<std::shared_ptr<Module>> _modules;
    std::vector<Connection> _connections;

    // menu popup flags
    bool openPopup;
    bool saveAsPopup;
    bool newWorkspacePopup;
    bool exitPopup;
    bool quickSave;
    bool play;
    char activeFileName[256];

    void begin_frame();

    /**
     * @brief  Draws a main menu bar (for save/load)
     * 
     */
    void draw_menu();

    /**
     * @brief create one module object from the save-file
     * 
     * @param module_str a single module from the save-file as a seperate stringstream
     * @return std::shared_ptr<Module> to the unserialized module object
     */
    std::shared_ptr<Module> unserialize_module(std::stringstream &module_str);

    /**
     * @brief creates all connection objects from the save-file
     * 
     * @param istream save-file with the file_ptr pointing to the line after "[connections]"
     */
    void unserialize_connections(std::istream &istream);

    /**
     * @brief Create a connection object with one module INPUT and one OUTPUT. start_id and end_id are getting arranged
     *        so that start_id == OUTPUT and end_id == INPUT
     * 
     * @param start_id Module INPUT or OUTPUT
     * @param end_id Module INPUT or OUTPUT
     * @param conn_id Unique id of the connection. Only used for load function
     */
    void create_connection(int start_id, int end_id, int conn_id=IdGenerator::generateId());

    void clear_workspace();

    /**
     * @brief gets the save folder path
     * 
     * @return std::string current path
     */
    std::string getSaveFolderPath();


    [[nodiscard]] std::shared_ptr<Module> getModuleByConnectorId(int id) const;

    static void end_frame(GLFWwindow* window, ImVec4 background_color);
    static void shutdown(GLFWwindow* window);
};


#endif //SIMPLESYNTH_MODULEEDITOR_H
