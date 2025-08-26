#include "ProjectManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

namespace fs = std::filesystem;

/// <summary>Obtiene la ruta base donde se almacenan los proyectos.</summary>
/// <returns>Ruta de proyectos como string.</returns>
std::string ProjectManager::GetProjectsPath() {
    return "PseudoEngineProjects";
}

/// <summary>Lista todos los proyectos existentes en la ruta base.</summary>
/// <returns>Vector con los nombres de los proyectos encontrados.</returns>
std::vector<std::string> ProjectManager::ListProjects() {
    std::vector<std::string> projects;
    std::string basePath = GetProjectsPath();

    if (!fs::exists(basePath)) {
        fs::create_directory(basePath);
        return projects;
    }

    for (const auto& entry : fs::directory_iterator(basePath)) {
        if (entry.is_directory()) {
            projects.push_back(entry.path().filename().string());
        }
    }
    return projects;
}

/// <summary>Verifica si un proyecto con el nombre dado existe.</summary>
/// <param name="name">Nombre del proyecto.</param>
/// <returns>true si existe, false en caso contrario.</returns>
bool ProjectManager::ProjectExists(const std::string& name) {
    return fs::exists(GetProjectsPath() + "/" + name);
}

/// <summary>Crea un proyecto nuevo con la estructura de carpetas y archivo principal.</summary>
/// <param name="name">Nombre del proyecto a crear.</param>
/// <returns>true si se creo correctamente, false si ocurrio un error.</returns>
bool ProjectManager::CreateProject(const std::string& name) {
    std::string basePath = GetProjectsPath() + "/" + name;

    try {
        fs::create_directories(basePath + "/Assets/Textures");
        fs::create_directories(basePath + "/Scripts/Player");
        fs::create_directories(basePath + "/Scripts/World");
        fs::create_directories(basePath + "/Scripts/Events");
        fs::create_directories(basePath + "/Scripts/Enemies");
        fs::create_directories(basePath + "/Build");

      
        std::string mainContent =
            "#define SDL_MAIN_HANDLED\n" // <--- línea clave
            "#include <SDL.h>\n"
            "#include <iostream>\n"
            "#include \"../../../Math/MathUtils.h\"\n\n"
            "void Update() {\n"
            "    float x = -5.5f;\n"
            "    std::cout << \"absf(-5.5) = \" << absf(x) << std::endl;\n"
            "}\n\n"
            "int main(int argc, char* argv[]) {\n"
            "    std::cout << \"Proyecto " + name + " iniciado!\" << std::endl;\n"
            "    if (SDL_Init(SDL_INIT_VIDEO) != 0) {\n"
            "        std::cerr << \"Error inicializando SDL: \" << SDL_GetError() << std::endl;\n"
            "        return 1;\n"
            "    }\n"
            "    while (true) {\n"
            "        Update();\n"
            "    }\n"
            "    SDL_Quit();\n"
            "    return 0;\n"
            "}\n";

        CreateFileWithContent(basePath + "/Scripts/" + name + ".cpp", mainContent);
        return true;
    }
    catch (...) {
        return false;
    }
}


/// <summary>Elimina un proyecto existente con todas sus carpetas y archivos.</summary>
/// <param name="name">Nombre del proyecto a eliminar.</param>
/// <returns>true si se elimino correctamente, false si ocurrio un error.</returns>
bool ProjectManager::DeleteProject(const std::string& name) {
    try {
        fs::remove_all(GetProjectsPath() + "/" + name);
        return true;
    }
    catch (...) {
        return false;
    }
}

/// <summary>Crea un archivo con contenido especificado en una ruta determinada.</summary>
/// <param name="path">Ruta completa del archivo a crear.</param>
/// <param name="content">Contenido a escribir dentro del archivo.</param>
/// <returns>true si se creo correctamente, false en caso contrario.</returns>
bool ProjectManager::CreateFileWithContent(const std::string& path, const std::string& content) {
    std::ofstream file(path);
    if (!file.is_open()) return false;
    file << content;
    file.close();
    return true;
}

/// <summary>Compila y ejecuta un proyecto existente, incluyendo dependencias de SDL2 y módulos LowLevel.</summary>
/// <param name="name">Nombre del proyecto a ejecutar.</param>
void ProjectManager::RunProject(const std::string& name) {
    std::string projectPath = GetProjectsPath() + "/" + name;
    std::string scriptsPath = projectPath + "/Scripts";
    std::string buildPath = projectPath + "/Build";

    
    if (!fs::exists(buildPath)) {
        fs::create_directory(buildPath);
    }

    std::string exePath = buildPath + "/" + name + ".exe";

    std::string sdl2Include = "C:/SDL2-devel-2.32.6-VC/SDL2-2.32.6/include";
    std::string sdl2Lib = "C:/SDL2-devel-2.32.6-VC/SDL2-2.32.6/lib/x64";
    std::string sdl2Dll = "C:/SDL2-devel-2.32.6-VC/SDL2-2.32.6/lib/x64/SDL2.dll";

    std::string sdl2ImageInclude = "C:/SDL2_image-devel-2.8.8-VC/SDL2_image-2.8.8/include";
    std::string sdl2ImageLib = "C:/SDL2_image-devel-2.8.8-VC/SDL2_image-2.8.8/lib/x64";
    std::string sdl2ImageDll = "C:/SDL2_image-devel-2.8.8-VC/SDL2_image-2.8.8/lib/x64/SDL2_image.dll";

   
    std::vector<std::string> moduleIncludes = {
          "C:/Users/OctoPC/Documents/Ilann Emilio Maya Campos___GitHub/48Engine/PseudoEngine48 - Motor/PseudoEngine/PseudoEngineModules/ModulesLowLevel/Math",
          "C:/Users/OctoPC/Documents/Ilann Emilio Maya Campos___GitHub/48Engine/PseudoEngine48 - Motor/PseudoEngine/PseudoEngineModules/ModulesLowLevel/Collision",
          "C:/Users/OctoPC/Documents/Ilann Emilio Maya Campos___GitHub/48Engine/PseudoEngine48 - Motor/PseudoEngine/PseudoEngineModules/ModulesLowLevel/Input",
          "C:/Users/OctoPC/Documents/Ilann Emilio Maya Campos___GitHub/48Engine/PseudoEngine48 - Motor/PseudoEngine/PseudoEngineModules/ModulesLowLevel/Physics",
          "C:/Users/OctoPC/Documents/Ilann Emilio Maya Campos___GitHub/48Engine/PseudoEngine48 - Motor/PseudoEngine/PseudoEngineModules/ModulesLowLevel/Raycast",
          "C:/Users/OctoPC/Documents/Ilann Emilio Maya Campos___GitHub/48Engine/PseudoEngine48 - Motor/PseudoEngine/PseudoEngineModules/ModulesLowLevel/Render",
          "C:/Users/OctoPC/Documents/Ilann Emilio Maya Campos___GitHub/48Engine/PseudoEngine48 - Motor/PseudoEngine/PseudoEngineModules/ModulesLowLevel/VectorDynam"
    };

    std::vector<std::string> moduleCpps = {
        "C:/Users/OctoPC/Documents/Ilann Emilio Maya Campos___GitHub/48Engine/PseudoEngine48 - Motor/PseudoEngine/PseudoEngineModules/ModulesLowLevel/Math/MathUtils.cpp",
        "C:/Users/OctoPC/Documents/Ilann Emilio Maya Campos___GitHub/48Engine/PseudoEngine48 - Motor/PseudoEngine/PseudoEngineModules/ModulesLowLevel/Math/Vec2.cpp",
        "C:/Users/OctoPC/Documents/Ilann Emilio Maya Campos___GitHub/48Engine/PseudoEngine48 - Motor/PseudoEngine/PseudoEngineModules/ModulesLowLevel/Collision/CollisionSystem.cpp",
        "C:/Users/OctoPC/Documents/Ilann Emilio Maya Campos___GitHub/48Engine/PseudoEngine48 - Motor/PseudoEngine/PseudoEngineModules/ModulesLowLevel/Input/Input.cpp",
        "C:/Users/OctoPC/Documents/Ilann Emilio Maya Campos___GitHub/48Engine/PseudoEngine48 - Motor/PseudoEngine/PseudoEngineModules/ModulesLowLevel/Physics/PhysicsSystem.cpp",
        "C:/Users/OctoPC/Documents/Ilann Emilio Maya Campos___GitHub/48Engine/PseudoEngine48 - Motor/PseudoEngine/PseudoEngineModules/ModulesLowLevel/Raycast/Raycast.cpp",
        "C:/Users/OctoPC/Documents/Ilann Emilio Maya Campos___GitHub/48Engine/PseudoEngine48 - Motor/PseudoEngine/PseudoEngineModules/ModulesLowLevel/Render/Render.cpp"
    };

   
    try {
        fs::copy_file(sdl2Dll, buildPath + "/SDL2.dll", fs::copy_options::overwrite_existing);
        fs::copy_file(sdl2ImageDll, buildPath + "/SDL2_image.dll", fs::copy_options::overwrite_existing);
    }
    catch (...) {
        std::cerr << "Error copiando DLLs de SDL2 o SDL2_image\n";
    }

    std::vector<std::string> allObj;

    
    for (const auto& cpp : moduleCpps) {
        std::string objFile = buildPath + "/" + fs::path(cpp).stem().string() + ".obj";
        allObj.push_back(objFile);

        std::stringstream cmd;
        cmd << "cl /EHsc /c ";
        for (const auto& inc : moduleIncludes) cmd << "/I \"" << inc << "\" ";
        cmd << "/I \"" << sdl2Include << "\" /I \"" << sdl2ImageInclude << "\" ";
        cmd << "\"" << cpp << "\" /Fo\"" << objFile << "\"";

        std::cout << "Compilando módulo: " << cpp << "\n";
        if (system(cmd.str().c_str()) != 0) {
            std::cerr << "Error compilando módulo: " << cpp << "\n";
            return;
        }
    }

    
    for (const auto& entry : fs::recursive_directory_iterator(scriptsPath)) {
        if (entry.path().extension() == ".cpp" && entry.path().filename() != (name + ".cpp")) {
            std::string objFile = buildPath + "/" + entry.path().stem().string() + ".obj";
            allObj.push_back(objFile);

            std::stringstream cmd;
            cmd << "cl /EHsc /c ";
            for (const auto& inc : moduleIncludes) cmd << "/I \"" << inc << "\" ";
            cmd << "/I \"" << sdl2Include << "\" /I \"" << sdl2ImageInclude << "\" ";
            cmd << "\"" << entry.path().string() << "\" /Fo\"" << objFile << "\"";

            std::cout << "Compilando script: " << entry.path().string() << "\n";
            if (system(cmd.str().c_str()) != 0) {
                std::cerr << "Error compilando script: " << entry.path().string() << "\n";
                return;
            }
        }
    }

   
    std::string mainCpp = scriptsPath + "/" + name + ".cpp";
    std::string mainObj = buildPath + "/" + name + ".obj";
    {
        std::stringstream cmd;
        cmd << "cl /EHsc /c ";
        for (const auto& inc : moduleIncludes) cmd << "/I \"" << inc << "\" ";
        cmd << "/I \"" << sdl2Include << "\" /I \"" << sdl2ImageInclude << "\" ";
        cmd << "\"" << mainCpp << "\" /Fo\"" << mainObj << "\"";

        std::cout << "Compilando main: " << mainCpp << "\n";
        if (system(cmd.str().c_str()) != 0) {
            std::cerr << "Error compilando main: " << mainCpp << "\n";
            return;
        }

        allObj.push_back(mainObj);
    }

   
    std::stringstream linkCmd;
    linkCmd << "link ";
    for (const auto& obj : allObj) linkCmd << "\"" << obj << "\" ";
    linkCmd << "/OUT:\"" << exePath << "\" ";
    linkCmd << "/LIBPATH:\"" << sdl2Lib << "\" /LIBPATH:\"" << sdl2ImageLib << "\" ";
    linkCmd << "SDL2.lib SDL2_image.lib"; // solo estas dos

    std::cout << "Linkeando a: " << exePath << "\n";
    if (system(linkCmd.str().c_str()) != 0) {
        std::cerr << "Error en el linkeo.\n";
        return;
    }

    
    std::cout << "Ejecutando .exe...\n";
    std::string runCmd = "start \"\" \"" + exePath + "\"";
    system(runCmd.c_str());
}
