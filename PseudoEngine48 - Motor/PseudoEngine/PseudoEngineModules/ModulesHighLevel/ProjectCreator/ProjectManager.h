#pragma once
#include <string>
#include <vector>

/// <summary>
/// Clase encargada de gestionar proyectos: listar, crear, eliminar, verificar existencia y ejecutar.
/// </summary>
class ProjectManager {
public:
    /// <summary>Obtiene la lista de proyectos existentes.</summary>
    /// <returns>Vector de nombres de proyectos.</returns>
    static std::vector<std::string> ListProjects();

    /// <summary>Crea un nuevo proyecto con el nombre especificado.</summary>
    /// <param name="name">Nombre del proyecto a crear.</param>
    /// <returns>true si se creo correctamente, false si ya existia o hubo error.</returns>
    static bool CreateProject(const std::string& name);

    /// <summary>Elimina un proyecto existente.</summary>
    /// <param name="name">Nombre del proyecto a eliminar.</param>
    /// <returns>true si se elimino correctamente, false si no existe.</returns>
    static bool DeleteProject(const std::string& name);

    /// <summary>Verifica si un proyecto existe.</summary>
    /// <param name="name">Nombre del proyecto a verificar.</param>
    /// <returns>true si existe, false en caso contrario.</returns>
    static bool ProjectExists(const std::string& name);

    /// <summary>Ejecuta un proyecto existente.</summary>
    /// <param name="name">Nombre del proyecto a ejecutar.</param>
    static void RunProject(const std::string& name);

public:
    /// <summary>Obtiene la ruta donde se almacenan los proyectos.</summary>
    /// <returns>Ruta de proyectos como string.</returns>
    static std::string GetProjectsPath();

private:
    /// <summary>Crea un archivo con contenido especificado en una ruta determinada.</summary>
    /// <param name="path">Ruta completa del archivo a crear.</param>
    /// <param name="content">Contenido a escribir dentro del archivo.</param>
    /// <returns>true si se creo y escribio correctamente, false en caso contrario.</returns>
    static bool CreateFileWithContent(const std::string& path, const std::string& content);
};
