# 🚀 Actualizador de Controladores v2.0

Una aplicación avanzada en C++ para escanear y actualizar controladores de dispositivos en sistemas Windows de forma automática y eficiente.

## 🌟 Características Principales

### ✨ Funcionalidades Core
- **Escaneo automático** de todos los dispositivos del sistema
- **Actualización masiva** de controladores con un solo clic
- **Actualización selectiva** de controladores específicos
- **Interfaz de consola** moderna y atractiva
- **Sistema de logging** completo con timestamps
- **Barras de progreso** visuales durante las actualizaciones

### 🛠️ Características Avanzadas
- **Detección automática** de dispositivos conectados
- **Modo verbose** configurable para debugging
- **Información detallada** del sistema operativo
- **Menú interactivo** con navegación intuitiva
- **Manejo robusto de errores** y excepciones
- **Logging automático** de todas las operaciones

## 📋 Requisitos del Sistema

- **Sistema Operativo:** Windows 7/8/10/11 (32-bit o 64-bit)
- **Compilador:** GCC (MinGW) o Microsoft Visual Studio
- **Permisos:** Administrador (requerido para actualizar controladores)
- **RAM:** Mínimo 512 MB
- **Espacio en disco:** 10 MB libres

## 🔧 Instalación y Compilación

### Opción 1: Compilar desde código fuente

```bash
# Clonar o descargar el archivo driver_updater.cpp
# Compilar con GCC/MinGW
g++ -o driver_updater.exe driver_updater.cpp -lsetupapi -ladvapi32 -static-libgcc -static-libstdc++

# Compilar con optimizaciones (recomendado)
g++ -O2 -o driver_updater.exe driver_updater.cpp -lsetupapi -ladvapi32 -static-libgcc -static-libstdc++
```

### Opción 2: Usar Visual Studio

1. Crear nuevo proyecto de consola C++
2. Agregar el archivo `driver_updater.cpp`
3. Configurar las librerías: `setupapi.lib` y `advapi32.lib`
4. Compilar en modo Release

## 🚀 Uso de la Aplicación

### Ejecución
```bash
# Ejecutar como administrador (MUY IMPORTANTE)
driver_up2.cpp.exe
```

### Menú Principal
```
┌─────────────────────────────────────────────────────────────┐
│                        MENÚ PRINCIPAL                       │
├─────────────────────────────────────────────────────────────┤
│ 1. Escanear dispositivos                                    │
│ 2. Actualizar todos los controladores                       │
│ 3. Actualizar controlador específico                        │
│ 4. Mostrar lista de dispositivos                            │
│ 5. Información del sistema                                  │
│ 6.  Configuración                                           │
│ 0.  Salir                                                   │
└─────────────────────────────────────────────────────────────┘
```

## 📖 Guía de Uso Paso a Paso

### 1. Primer Uso
1. **Ejecutar como administrador** (clic derecho → "Ejecutar como administrador")
2. Seleccionar opción **1** para escanear dispositivos
3. Esperar a que complete el escaneo automático
4. Revisar la lista de dispositivos detectados

### 2. Actualización Masiva
1. Seleccionar opción **2** para actualizar todos los controladores
2. Confirmar la operación si se solicita
3. Esperar a que complete el proceso (puede tomar varios minutos)
4. Revisar el resumen de actualizaciones

### 3. Actualización Específica
1. Seleccionar opción **3** para actualizar un controlador específico
2. Elegir el dispositivo de la lista numerada
3. Confirmar la actualización
4. Esperar a que complete el proceso

### 4. Configuración
1. Seleccionar opción **6** para acceder a configuración
2. Activar/desactivar modo verbose para más información
3. Cambiar la ubicación del archivo de log si es necesario

## 📊 Archivos Generados

### driver_update.log
Archivo de registro que contiene:
- Timestamp de cada operación
- Lista de dispositivos escaneados
- Resultado de cada actualización
- Errores y advertencias

Ejemplo de contenido:
```
[2024-01-15 14:30:22] Aplicación iniciada
[2024-01-15 14:30:25] Escaneo completado - 24 dispositivos encontrados
[2024-01-15 14:31:10] Controlador actualizado: NVIDIA GeForce GTX 1060 [PCI\VEN_10DE...]
[2024-01-15 14:31:15] Actualización masiva completada - 22/24 exitosas
```

## ⚠️ Advertencias Importantes

### 🔒 Permisos de Administrador
- **SIEMPRE** ejecutar como administrador
- Sin permisos de administrador, la aplicación no podrá actualizar controladores
- Algunos antivirus pueden bloquear la ejecución inicial

### 🛡️ Seguridad
- La aplicación **NO** descarga controladores de internet
- **NO** modifica archivos del sistema sin autorización
- Todos los cambios son registrados en el log
- Crear un punto de restauración antes de actualizar

### 💾 Respaldo
- **Recomendado:** Crear punto de restauración del sistema
- Respaldar controladores actuales antes de actualizar
- Tener a mano los controladores originales del fabricante

## 🐛 Solución de Problemas

### Error: "No se puede ejecutar"
- **Causa:** Falta de permisos de administrador
- **Solución:** Clic derecho → "Ejecutar como administrador"

### Error: "No se encontraron dispositivos"
- **Causa:** Problema con las APIs del sistema
- **Solución:** Reiniciar como administrador, verificar Windows Update

### Error: "Fallo en la actualización"
- **Causa:** Controlador en uso o protegido
- **Solución:** Reiniciar el sistema y volver a intentar

### Aplicación se cierra inesperadamente
- **Causa:** Falta de librerías del sistema
- **Solución:** Instalar Visual C++ Redistributable

## 🔄 Registro de Cambios

### v2.0 (Actual)
- ✅ Interfaz completamente rediseñada
- ✅ Sistema de logging mejorado
- ✅ Barras de progreso visuales
- ✅ Detección automática de dispositivos
- ✅ Modo verbose configurable
- ✅ Manejo robusto de errores

### v1.0 (Anterior)
- ✅ Funcionalidad básica de escaneo
- ✅ Actualización simple de controladores


### Reportar Bugs
- Usar el sistema de Issues de GitHub
- Incluir información del sistema operativo
- Adjuntar el archivo de log si es posible
- Describir los pasos para reproducir el problema

## 📜 Licencia

Este proyecto está bajo la Licencia MIT. Ver el archivo `LICENSE` para más detalles.

## 👨‍💻 Autor

**Desarrollador:** LuisVides
**Versión:** 2.0
**Fecha:** 05/07/2025

### FAQ
**P: ¿Es seguro usar esta aplicación?**  
R: Sí, la aplicación solo usa APIs oficiales de Windows y no modifica archivos críticos del sistema.

**P: ¿Funciona en Windows 11?**  
R: Sí, es compatible con Windows 7, 8, 10 y 11.

**P: ¿Puedo revertir los cambios?**  
R: Sí, usando el punto de restauración del sistema o reinstalando los controladores originales.

---

**⚡ ¡Mantén tus controladores actualizados para un rendimiento óptimo!**
