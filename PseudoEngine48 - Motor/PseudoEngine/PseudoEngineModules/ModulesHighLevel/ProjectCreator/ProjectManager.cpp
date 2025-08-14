 #include "ProjectManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

std::string ProjectManager::GetProjectsPath() {
    return "PseudoEngineProjects";
}

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

bool ProjectManager::ProjectExists(const std::string& name) {
    return fs::exists(GetProjectsPath() + "/" + name);
}

bool ProjectManager::CreateProject(const std::string& name) {
    std::string basePath = GetProjectsPath() + "/" + name;

    try {
        // Crear estructura de carpetas
        fs::create_directories(basePath + "/Assets/Textures");
        fs::create_directories(basePath + "/Scripts/Player");
        fs::create_directories(basePath + "/Scripts/World");
        fs::create_directories(basePath + "/Scripts/Events");
        fs::create_directories(basePath + "/Scripts/Enemies");

        
        std::string mainContent =
            "#include <iostream>\n"
            "void Update() {\n"
            "    // Update\n"
            "}\n"
            "int main() {\n"
            "    std::cout << \"4848484848484848!\" << std::endl;\n"
            "    while (true) {\n"
            "        Update();\n"
            "    }\n"
            "    return 0;\n"
            "}\n";

        CreateFileWithContent(basePath + "/Scripts/" + name + ".cpp", mainContent);

        return true;
    }
    catch (...) {
        return false;
    }
}

bool ProjectManager::DeleteProject(const std::string& name) {
    try {
        fs::remove_all(GetProjectsPath() + "/" + name);
        return true;
    }
    catch (...) {
        return false;
    }
}

bool ProjectManager::CreateFileWithContent(const std::string& path, const std::string& content) {
    std::ofstream file(path);
    if (!file.is_open()) return false;
    file << content;
    file.close();
    return true;
}


