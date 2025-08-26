#pragma once
#include <string>

/// <summary>
/// Clase que maneja la interfaz de usuario para la creacion y gestion de proyectos en PseudoEngine.
/// </summary>
class ProjectCreatorUI {
public:
    /// <summary>
    /// Inicia la interfaz principal del sistema de creacion de proyectos.
    /// </summary>
    static void Run();

private:
    /// <summary>
    /// Muestra el menu principal con opciones de iniciar proyecto o salir.
    /// </summary>
    static void ShowMainMenu();

    /// <summary>
    /// Muestra el menu de proyectos, permitiendo seleccionar, crear, eliminar o acceder a la documentacion.
    /// </summary>
    static void ShowProjectsMenu();

    /// <summary>
    /// Maneja la creacion de un nuevo proyecto solicitando el nombre al usuario.
    /// </summary>
    static void HandleCreateProject();

    /// <summary>
    /// Maneja la eliminacion de un proyecto existente, solicitando confirmacion al usuario.
    /// </summary>
    static void HandleDeleteProject();

    /// <summary>
    /// Muestra la documentacion de los modulos del sistema.
    /// </summary>
    static void HandleDocumentation();
};
