#include "ProjectCreatorUI.h"
#include "ProjectManager.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib> // para system()

/// <summary>
/// Ejecuta la interfaz principal del ProjectCreator.
/// </summary>
void ProjectCreatorUI::Run() {
    ShowMainMenu();
}

/// <summary>
/// Muestra el menu principal con opciones de iniciar o salir.
/// </summary>
void ProjectCreatorUI::ShowMainMenu() {
    int choice = 0;
    while (true) {
        std::cout << "===== PseudoEngine =====\n\n";
        std::cout << "Bienvenido Usuario: \n\n";
        std::cout << "1: INICIAR\n2: SALIR\n\n";
        std::cin >> choice;

        if (choice == 1) ShowProjectsMenu();
        else if (choice == 2) break;
        else std::cout << "Opcion invalida.\n";
    }
}

/// <summary>
/// Muestra el menu de proyectos, permitiendo seleccionar, crear, eliminar o acceder a la documentacion.
/// </summary>
void ProjectCreatorUI::ShowProjectsMenu() {
    std::string input;
    while (true) {
        std::vector<std::string> projects = ProjectManager::ListProjects();
        std::cout << "\n===== Proyectos =====\n\n";

        if (projects.empty()) std::cout << "(No hay proyectos creados)\n";
        else for (size_t i = 0; i < projects.size(); ++i)
            std::cout << (i < 10 ? "0" : "") << i << ": " << projects[i] << "\n";

        std::cout << "\n1: Crear Proyecto\n2: Eliminar Proyecto\n3: Documentacion\n4: Volver\n\n";
        std::cout << "Ingrese numero de proyecto o opcion: ";
        std::cin >> input;

        // Revisar si es número de proyecto
        bool isNumber = !input.empty() && std::all_of(input.begin(), input.end(), ::isdigit);
        if (isNumber) {
            int index = std::stoi(input);
            if (index >= 0 && index < (int)projects.size()) {
                ProjectManager::RunProject(projects[index]);
                continue;
            }
        }

        if (input == "1") HandleCreateProject();
        else if (input == "2") HandleDeleteProject();
        else if (input == "3") HandleDocumentation();
        else if (input == "4") break;
        else std::cout << "Opcion invalida.\n";
    }
}

/// <summary>
/// Maneja la creacion de un nuevo proyecto solicitando el nombre al usuario.
/// </summary>
void ProjectCreatorUI::HandleCreateProject() {
    std::string name;
    std::cout << "Ingrese el nombre del nuevo proyecto: ";
    std::cin >> name;

    if (ProjectManager::ProjectExists(name)) {
        std::cout << "Ya existe un proyecto con ese nombre.\n";
        return;
    }

    if (ProjectManager::CreateProject(name))
        std::cout << "Proyecto '" << name << "' creado exitosamente.\n";
    else
        std::cout << "Error al crear el proyecto.\n";
}

/// <summary>
/// Maneja la eliminacion de un proyecto existente, solicitando confirmacion al usuario.
/// </summary>
void ProjectCreatorUI::HandleDeleteProject() {
    std::string name1, name2;
    std::cout << "Ingrese el nombre del proyecto a eliminar: ";
    std::cin >> name1;
    std::cout << "Confirme el nombre del proyecto: ";
    std::cin >> name2;

    if (name1 != name2) return;
    if (!ProjectManager::ProjectExists(name1)) return;
    ProjectManager::DeleteProject(name1);
}

/// <summary>
/// Muestra la documentacion de los modulos del sistema.
/// </summary>
void ProjectCreatorUI::HandleDocumentation() {
    std::string input;

    while (true) {
        std::cout << "\n===== Documentacion =====\n";
        std::cout << "1: Modulos High\n";
        std::cout << "2: Modulos LowLevel\n";
        std::cout << "3: Volver\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> input;

        if (input == "1") {
            while (true) {
                std::cout << "\n===== Modulos HighLevel =====\n";
                std::cout << "1: ProjectCreator\n";
                std::cout << "2: Volver\n";
                std::cout << "Seleccione una opcion: ";
                std::cin >> input;

                if (input == "1") {
                    std::string htmlPath = "C:\\Users\\OctoPC\\Documents\\Ilann Emilio Maya Campos___GitHub\\48Engine\\PseudoEngine48 - Motor\\PseudoEngine\\PseudoEngineModules\\Documentacion\\HighLevel\\ProjectCreator\\html\\index.html";
                    std::string command = "start \"\" \"" + htmlPath + "\"";
                    system(command.c_str());
                }
                else if (input == "2") break;
                else std::cout << "Opcion invalida.\n";
            }
        }
        else if (input == "2") {
            while (true) {
                std::cout << "\n===== Modulos LowLevel =====\n";
                std::cout << "1: Math\n2: Raycast\n3: Collision\n4: Physics\n5: Input\n6: Render\n7: VectorDynam\n8: Volver\n";
                std::cout << "Seleccione una opcion: ";
                std::cin >> input;

                std::string basePath = "C:\\Users\\OctoPC\\Documents\\Ilann Emilio Maya Campos___GitHub\\48Engine\\PseudoEngine48 - Motor\\PseudoEngine\\PseudoEngineModules\\Documentacion\\LowLevel\\";
                std::string modulePath;

                if      (input == "1") modulePath = basePath + "Math\\html\\index.html";
                else if (input == "2") modulePath = basePath + "Raycast\\html\\index.html";
                else if (input == "3") modulePath = basePath + "Collision\\html\\index.html";
                else if (input == "4") modulePath = basePath + "Physics\\html\\index.html";
                else if (input == "5") modulePath = basePath + "Input\\html\\index.html";
                else if (input == "6") modulePath = basePath + "Render\\html\\index.html";
                else if (input == "7") modulePath = basePath + "VectorDynam\\html\\index.html";
                else if (input == "8") break;
                else {
                    std::cout << "Opcion invalida.\n";
                    continue;
                }

                std::string command = "start \"\" \"" + modulePath + "\"";
                system(command.c_str());
            }
        }
        else if (input == "3") break;
        else std::cout << "Opcion invalida.\n";
    }
}
