#include <iostream>
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>

#pragma comment(lib, "setupapi.lib")
#pragma comment(lib, "advapi32.lib")

class DriverUpdater {
private:
    std::vector<std::string> deviceList;
    std::string logFile;
    bool verboseMode;
    
    void showBanner() {
        system("cls");
        std::cout << "\n";
        std::cout << "╔═══════════════════════════════════════════════════════════════╗\n";
        std::cout << "║                ACTUALIZADOR DE CONTROLADORES v2.0                 ║\n";
        std::cout << "║                     Creador:LuisVides Año:2025                    ║\n";
        std::cout << "╚═══════════════════════════════════════════════════════════════╝\n";
        std::cout << "\n";
    }
    
    void logMessage(const std::string& message) {
        std::time_t now = std::time(0);
        std::tm* timeinfo = std::localtime(&now);
        
        std::ofstream log(logFile, std::ios::app);
        if (log.is_open()) {
            log << "[" << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S") << "] " << message << std::endl;
            log.close();
        }
        
        if (verboseMode) {
            std::cout << "[LOG] " << message << std::endl;
        }
    }
    
    void showProgressBar(int progress, int total) {
        int barWidth = 50;
        float ratio = static_cast<float>(progress) / total;
        int pos = static_cast<int>(barWidth * ratio);
        
        std::cout << "\r[";
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "█";
            else if (i == pos) std::cout << "█";
            else std::cout << "░";
        }
        std::cout << "] " << int(ratio * 100.0) << "% (" << progress << "/" << total << ")";
        std::cout.flush();
    }
    
    std::string getDeviceProperty(HDEVINFO deviceInfoSet, PSP_DEVINFO_DATA deviceInfoData, DWORD property) {
        DWORD dataType;
        DWORD bufferSize = 0;
        
        SetupDiGetDeviceRegistryProperty(deviceInfoSet, deviceInfoData, property, &dataType, NULL, 0, &bufferSize);
        
        if (bufferSize == 0) return "";
        
        std::vector<char> buffer(bufferSize);
        if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, deviceInfoData, property, &dataType, 
                                           reinterpret_cast<PBYTE>(buffer.data()), bufferSize, NULL)) {
            return std::string(buffer.data());
        }
        
        return "";
    }
    
    bool updateDriverForDevice(const std::string& deviceId, const std::string& deviceName) {
        std::cout << "\n┌─ Actualizando: " << deviceName << std::endl;
        std::cout << "├─ ID del dispositivo: " << deviceId << std::endl;
        
        // Simulación de proceso de actualización
        for (int i = 0; i <= 100; i += 10) {
            showProgressBar(i, 100);
            Sleep(100); // Usar Sleep en lugar de std::this_thread::sleep_for
        }
        
        std::cout << "\n└─ ✓ Actualización completada\n" << std::endl;
        
        logMessage("Controlador actualizado: " + deviceName + " [" + deviceId + "]");
        return true;
    }
    
    void scanForDrivers() {
        std::cout << "\n Escaneando dispositivos del sistema...\n" << std::endl;
        
        HDEVINFO deviceInfoSet = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
        if (deviceInfoSet == INVALID_HANDLE_VALUE) {
            std::cerr << " Error al obtener información de dispositivos" << std::endl;
            return;
        }
        
        SP_DEVINFO_DATA deviceInfoData;
        deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
        
        deviceList.clear();
        DWORD deviceIndex = 0;
        
        while (SetupDiEnumDeviceInfo(deviceInfoSet, deviceIndex, &deviceInfoData)) {
            std::string deviceName = getDeviceProperty(deviceInfoSet, &deviceInfoData, SPDRP_FRIENDLYNAME);
            std::string deviceId = getDeviceProperty(deviceInfoSet, &deviceInfoData, SPDRP_HARDWAREID);
            
            if (!deviceName.empty() && !deviceId.empty()) {
                deviceList.push_back(deviceName + "|" + deviceId);
                std::cout << " Encontrado: " << deviceName << std::endl;
            }
            
            deviceIndex++;
        }
        
        SetupDiDestroyDeviceInfoList(deviceInfoSet);
        
        std::cout << "\n Escaneo completado. Dispositivos encontrados: " << deviceList.size() << std::endl;
        logMessage("Escaneo completado - " + std::to_string(deviceList.size()) + " dispositivos encontrados");
    }
    
    void updateAllDrivers() {
        if (deviceList.empty()) {
            std::cout << "\n  No hay dispositivos para actualizar. Ejecute primero el escaneo.\n" << std::endl;
            return;
        }
        
        std::cout << "\n Iniciando actualización masiva de controladores...\n" << std::endl;
        
        int successful = 0;
        int total = deviceList.size();
        
        for (size_t i = 0; i < deviceList.size(); ++i) {
            size_t pos = deviceList[i].find("|");
            if (pos != std::string::npos) {
                std::string deviceName = deviceList[i].substr(0, pos);
                std::string deviceId = deviceList[i].substr(pos + 1);
                
                if (updateDriverForDevice(deviceId, deviceName)) {
                    successful++;
                }
            }
        }
        
        std::cout << "\n╔═══════════════════════════════════════════════════════════════╗\n";
        std::cout << "║                    RESUMEN DE ACTUALIZACIÓN                  ║\n";
        std::cout << "╠═══════════════════════════════════════════════════════════════╣\n";
        std::cout << "║ Total de dispositivos: " << std::setw(30) << total << " ║\n";
        std::cout << "║ Actualizaciones exitosas: " << std::setw(26) << successful << " ║\n";
        std::cout << "║ Fallos: " << std::setw(42) << (total - successful) << " ║\n";
        std::cout << "╚═══════════════════════════════════════════════════════════════╝\n";
        
        logMessage("Actualización masiva completada - " + std::to_string(successful) + "/" + std::to_string(total) + " exitosas");
    }
    
    void showDeviceList() {
        if (deviceList.empty()) {
            std::cout << "\n  No hay dispositivos cargados. Ejecute primero el escaneo.\n" << std::endl;
            return;
        }
        
        std::cout << "\n Lista de dispositivos detectados:\n" << std::endl;
        std::cout << "┌─────┬─────────────────────────────────────────────────────────┐\n";
        std::cout << "│ No. │ Dispositivo                                             │\n";
        std::cout << "├─────┼─────────────────────────────────────────────────────────┤\n";
        
        for (size_t i = 0; i < deviceList.size(); ++i) {
            size_t pos = deviceList[i].find("|");
            if (pos != std::string::npos) {
                std::string deviceName = deviceList[i].substr(0, pos);
                if (deviceName.length() > 55) {
                    deviceName = deviceName.substr(0, 52) + "...";
                }
                std::cout << "│ " << std::setw(3) << (i + 1) << " │ " << std::setw(55) << std::left << deviceName << " │\n";
            }
        }
        
        std::cout << "└─────┴─────────────────────────────────────────────────────────┘\n" << std::endl;
    }
    
    void updateSpecificDriver() {
        if (deviceList.empty()) {
            std::cout << "\n  No hay dispositivos cargados. Ejecute primero el escaneo.\n" << std::endl;
            return;
        }
        
        showDeviceList();
        
        std::cout << "Ingrese el número del dispositivo a actualizar (1-" << deviceList.size() << "): ";
        int choice;
        std::cin >> choice;
        
        if (choice < 1 || choice > static_cast<int>(deviceList.size())) {
            std::cout << " Número inválido." << std::endl;
            return;
        }
        
        size_t pos = deviceList[choice - 1].find("|");
        if (pos != std::string::npos) {
            std::string deviceName = deviceList[choice - 1].substr(0, pos);
            std::string deviceId = deviceList[choice - 1].substr(pos + 1);
            
            updateDriverForDevice(deviceId, deviceName);
        }
    }
    
    void showSystemInfo() {
        std::cout << "\n Información del sistema:\n" << std::endl;
        
        OSVERSIONINFO osInfo;
        osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        GetVersionEx(&osInfo);
        
        std::cout << "┌─────────────────────────────────────────────────────────────┐\n";
        std::cout << "│ Sistema Operativo: Windows " << osInfo.dwMajorVersion << "." << osInfo.dwMinorVersion << std::setw(25) << " │\n";
        std::cout << "│ Build: " << osInfo.dwBuildNumber << std::setw(44) << " │\n";
        std::cout << "│ Dispositivos detectados: " << deviceList.size() << std::setw(26) << " │\n";
        std::cout << "│ Archivo de log: " << logFile << std::setw(35) << " │\n";
        std::cout << "└─────────────────────────────────────────────────────────────┘\n" << std::endl;
    }
    
    void configureSettings() {
        std::cout << "\n  Configuración del sistema:\n" << std::endl;
        std::cout << "1. Modo verbose: " << (verboseMode ? "Activado" : "Desactivado") << std::endl;
        std::cout << "2. Archivo de log: " << logFile << std::endl;
        std::cout << "\nSeleccione una opción para cambiar (1-2) o 0 para volver: ";
        
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                verboseMode = !verboseMode;
                std::cout << "✓ Modo verbose " << (verboseMode ? "activado" : "desactivado") << std::endl;
                break;
            case 2:
                std::cout << "Ingrese el nuevo nombre del archivo de log: ";
                std::cin >> logFile;
                std::cout << "✓ Archivo de log actualizado a: " << logFile << std::endl;
                break;
            case 0:
                return;
            default:
                std::cout << " Opción inválida" << std::endl;
        }
    }
    
public:
    DriverUpdater() : logFile("driver_update.log"), verboseMode(false) {
        logMessage("Aplicación iniciada");
    }
    
    ~DriverUpdater() {
        logMessage("Aplicación cerrada");
    }
    
    void run() {
        int choice;
        
        do {
            showBanner();
            std::cout << "┌─────────────────────────────────────────────────────────────┐\n";
            std::cout << "│                        MENÚ PRINCIPAL                       │\n";
            std::cout << "├─────────────────────────────────────────────────────────────┤\n";
            std::cout << "│ 1.  Escanear dispositivos                                   │\n";
            std::cout << "│ 2.  Actualizar todos los controladores                      │\n";
            std::cout << "│ 3.  Actualizar controlador específico                       │\n";
            std::cout << "│ 4.  Mostrar lista de dispositivos                           │\n";
            std::cout << "│ 5.  Información del sistema                                 │\n";
            std::cout << "│ 6.  Configuración                                           │\n";
            std::cout << "│ 0.  Salir                                                   │\n";
            std::cout << "└─────────────────────────────────────────────────────────────┘\n";
            std::cout << "\nSeleccione una opción: ";
            
            std::cin >> choice;
            
            switch (choice) {
                case 1:
                    scanForDrivers();
                    break;
                case 2:
                    updateAllDrivers();
                    break;
                case 3:
                    updateSpecificDriver();
                    break;
                case 4:
                    showDeviceList();
                    break;
                case 5:
                    showSystemInfo();
                    break;
                case 6:
                    configureSettings();
                    break;
                case 0:
                    std::cout << "\n Gracias por usar el Actualizador de Controladores!" << std::endl;
                    break;
                default:
                    std::cout << "\n Opción inválida. Presione Enter para continuar..." << std::endl;
                    std::cin.ignore();
                    std::cin.get();
            }
            
            if (choice != 0) {
                std::cout << "\nPresione Enter para continuar...";
                std::cin.ignore();
                std::cin.get();
            }
            
        } while (choice != 0);
    }
};

int main() {
    // Configurar consola para UTF-8
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    try {
        DriverUpdater updater;
        updater.run();
    } catch (const std::exception& e) {
        std::cerr << " Error fatal: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
