#pragma once
#include <string>

class ProjectCreatorUI {
public:
    static void Run(); 
private:
    static void ShowMainMenu();
    static void ShowProjectsMenu();
    static void HandleCreateProject();
    static void HandleDeleteProject();
    static void HandleDocumentation();
};