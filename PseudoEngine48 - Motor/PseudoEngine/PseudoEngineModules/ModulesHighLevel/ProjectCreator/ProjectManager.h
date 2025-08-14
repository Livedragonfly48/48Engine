#pragma once
#include <string>
#include <vector>

class ProjectManager {
public:
    static std::vector<std::string> ListProjects();
    static bool CreateProject(const std::string& name);
    static bool DeleteProject(const std::string& name);
    static bool ProjectExists(const std::string& name);

private:
    static std::string GetProjectsPath();
    static bool CreateFileWithContent(const std::string& path, const std::string& content);
};