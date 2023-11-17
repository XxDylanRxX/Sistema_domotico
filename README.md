# Domótica Hogar  con ESP32

Este es un proyecto de sistema domótico para el hogar utilizando ESP32 y la plataforma Blynk. Permite controlar hasta 8 dispositivos mediante la aplicación Blynk.

## Requisitos del Proyecto

1. **Hardware:**
   - ESP32 (u otro compatible)
   - Módulo de relés (8 canales)
   - Sensor de movimiento (PIR)
   - Buzzer
   - Botones y LED indicadores para cada canal de relé
   - Conexiones eléctricas según el esquema

2. **Software:**
   - [Arduino IDE](https://www.arduino.cc/en/software)
   - Controladores USB a UART para ESP32 (ver pasos de instalación más abajo)

## Instalación del Entorno de Desarrollo

### Arduino IDE

1. Descarga e instala [Arduino IDE](https://www.arduino.cc/en/software).

2. Abre Arduino IDE y ve a "File" -> "Preferences".

3. En "Additional Boards Manager URLs", agrega el enlace para la placa ESP32:
 [](https://dl.espressif.com/dl/package_esp32_index.json).

5. Ve a "Tools" -> "Boards" -> "Boards Manager", busca "ESP32" e instala el paquete "esp32" de Espressif Systems.

### Controladores USB a UART para ESP32

1. Conecta tu ESP32 a la computadora mediante un cable USB.

2. Espera a que la computadora detecte el nuevo dispositivo (en administrador de dispositivos).

3. Descarga e instala los controladores USB a UART específicos para tu placa ESP32. Puedes encontrarlos en el sitio web del fabricante de tu módulo ESP32.

## Configuración del Proyecto

1. Abre el archivo `domotica_hogar_prueba.ino` en Arduino IDE.

2. Reemplaza las siguientes líneas con tu configuración de red WiFi y credenciales Blynk:

```cpp
#define BLYNK_TEMPLATE_ID "TMPL29IO9xEIK"
#define BLYNK_TEMPLATE_NAME "Domótica Hogar Prueba"
#define BLYNK_AUTH_TOKEN "pSQg5qM_izTycYxLnpdVCWwiF07PdCYJ"

char ssid[] = "TuSSID";
char pass[] = "TuContraseña";
```
1. Configura las asignaciones de pines según tu conexión de hardware:
```cpp
// Pines de botones y relés
#define button1_pin 5
// Resto de los pines...

// Asignaciones de pines de relé
#define relay1_pin 33
// Resto de los pines...
```
2. Sube el código a tu ESP32.

## Esquema de Conexión
Consulta el esquema de conexión proporcionado en la documentación para asegurarte de que tus componentes estén conectados correctamente.
##  Uso de la Aplicación Blynk
1. Descarga e instala la aplicación Blynk.

2. Abre la plantilla Domótica Hogar Prueba en la aplicación Blynk.

3. Obtén tu Token de Autenticación desde la aplicación Blynk y actualiza la variable BLYNK_AUTH_TOKEN en el código.

4. Conecta tu ESP32 a la red WiFi.


## Información Adicional
Video Tutorial: [Enlace al Video Tutorial](https://youtu.be/fF7agDvPDrI?si=fWMo8Ls-iXXhqYRL).
