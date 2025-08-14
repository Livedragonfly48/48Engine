#include "ProjectCreatorUI.h"
#include "ProjectManager.h"
#include <iostream>
#include <vector>

void ProjectCreatorUI::Run() {
    ShowMainMenu();
}

void ProjectCreatorUI::ShowMainMenu() {
    int choice = 0;
    while (true) {
        std::cout << "===== PseudoEngine =====\n" << std::endl;
        std::cout << "Bienvenido Usuario: " << std::endl << std::endl;
        std::cout << "1: INICIAR\n";
        std::cout << "2: SALIR\n" << std::endl;
        std::cin >> choice;

        if (choice == 1) {
            ShowProjectsMenu();
        }
        else if (choice == 2) {
            std::cout << "Saliendo...\n";
            break;
        }
        else {
            std::cout << "Opcion invalida.\n";
        }
    }
}

void ProjectCreatorUI::ShowProjectsMenu() {
    int choice = 0;

    while (true) {
        std::vector<std::string> projects = ProjectManager::ListProjects();

        std::cout << "\n===== Proyectos =====\n" << std::endl;
        if (projects.empty()) {
            std::cout << "(No hay proyectos creados)\n";
        }
        else {
            for (size_t i = 0; i < projects.size(); ++i) {
                std::cout << "- " << projects[i] << "\n";
            }
        }

        std::cout << "\n1: Crear Proyecto\n";
        std::cout << "2: Eliminar Proyecto\n";
        std::cout << "3: Documentacion\n";
        std::cout << "4: Volver al menu principal\n" << std::endl;

        std::cin >> choice;

        if (choice == 1) {
            HandleCreateProject();
        }
        else if (choice == 2) {
            HandleDeleteProject();
        }
        else if (choice == 3) {
            HandleDocumentation();
        }
        else if (choice == 4) {
            break;
        }
        else {
            std::cout << "Opcion invalida.\n";
        }
    }
}

void ProjectCreatorUI::HandleCreateProject() {
    std::string name;
    std::cout << "Ingrese el nombre del nuevo proyecto: ";
    std::cin >> name;

    if (ProjectManager::ProjectExists(name)) {
        std::cout << "Ya existe un proyecto con ese nombre.\n";
        return;
    }

    if (ProjectManager::CreateProject(name)) {
        std::cout << "Proyecto ''" << name << "'' creado exitosamente.\n";
    }
    else {
        std::cout << "Error al crear el proyecto.\n";
    }
}

void ProjectCreatorUI::HandleDeleteProject() {
    std::string name1, name2;
    std::cout << "Ingrese el nombre del proyecto a eliminar: ";
    std::cin >> name1;
    std::cout << "Confirme el nombre del proyecto: ";
    std::cin >> name2;

    if (name1 != name2) {
        std::cout << "Los nombres no coinciden. Cancelando.\n";
        return;
    }

    if (!ProjectManager::ProjectExists(name1)) {
        std::cout << "El proyecto no existe.\n";
        return;
    }

    if (ProjectManager::DeleteProject(name1)) {
        std::cout << "Proyecto eliminado exitosamente.\n";
    }
    else {
        std::cout << "Error al eliminar el proyecto.\n";
    }
}

void ProjectCreatorUI::HandleDocumentation() {
    std::cout << "\n===== Documentacion =====\n";
    std::cout << "En proceso...\n\n";
}
