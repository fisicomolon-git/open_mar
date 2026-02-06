// ... (INCLUDES Y DEFINICIONES SON LAS MISMAS)
// Código para el robot pequeño seguidor de lineas y controlado por mando usb. 
//v.01

/* datos leidos del mando usb
hay dos modos, segun pulses la tecla mode en el mando. con y sin led
001 128 128 128 128 015 000 000
sin led:
la primera columna (report[0]) siempre es 001 indica el mando 1. algunos hardware chinos traen 2 mandos con el mismo dongle usb
las dos siguientes report[1] y report[2] son siempre 128 para el modo sin led. 
el analogico derecho (que no es analogico de verdad) actua como x,y,a,b en este modo
  columna 6 (report[5]):
  no pulso nada : 015
  y = 31
  a = 79
  b = 47
  x = 143
columna 7 (report[6]):
no pulso nada = 000
L1= 001
L2 = 004
R1= 002
R2 = 008
select = 16
start =32

CON LED:
Todo igual pero el analogico derecho cambia, ya no son los botones a,b,x,y
columna 2 (report[1])
no pulso nada 128
izquierda = 0
derecha = 255
columna 3 (report[2])
no pulso nada 128
arriba= 0
abajo = 255

*/
#include <Adafruit_TinyUSB.h>
#include <NeoPixelConnect.h>

#define NEOPIXEL_PIN 16 

#define COLOR_BASE      0, 0, 255     
#define COLOR_PULSADO   0, 255, 0     
#define COLOR_ERROR     255, 0, 0     
#define COLOR_DESCONECTADO 255, 255, 0 

Adafruit_USBH_Host USBHost; 
NeoPixelConnect led(NEOPIXEL_PIN, 1, pio0, 0); 
//uint16_t buttonState = 0;
#include <Servo.h>

Servo servo1;
Servo servo2;

// Pines de conexión
const int pinServo1 = 10;
const int pinServo2 = 12;
const int sensorizq = 27;
const int sensorder = 28;
bool estado=1; //estado 1 es seguidor de lineas y si estado 0 es control con el mando
bool cambio=0;

void setLedColor(uint8_t r, uint8_t g, uint8_t b) {
    led.neoPixelFill(r, g, b, true);
}


// --- NUEVO CALLBACK DE CONFIGURACIÓN ---
// Se llama cuando el dispositivo ya está montado y TinyUSB encuentra una interfaz HID.
void tuh_hid_mount_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* desc_report, uint16_t desc_len)
{
    uint8_t const itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);
    
    Serial1.print("HID Dispositivo: Addr = "); Serial1.print(dev_addr);
    Serial1.print(", Protocolo = "); 
    
    if (itf_protocol == HID_ITF_PROTOCOL_KEYBOARD) {
        Serial1.println("Teclado");
    } else if (itf_protocol == HID_ITF_PROTOCOL_MOUSE) {
        Serial1.println("Ratón");
    } else {
        Serial1.print("Otros (GamePad/Custom): "); Serial1.println(itf_protocol);
    }

    // 1. Iniciar la transferencia de datos (Polling)
    if (tuh_hid_receive_report(dev_addr, instance) == 0) {
        Serial1.println("¡Transferencia de datos iniciada con éxito!");
        setLedColor(COLOR_BASE); // Azul
    } else {
        Serial1.println("ERROR: No se pudo iniciar la transferencia de datos (Polling).");
        // Esto indica que el mando no es reconocido por los drivers HID activos.
        setLedColor(COLOR_ERROR); // Rojo
    }
}

// Llamado cuando se retira la interfaz HID.
void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance)
{
  Serial1.print("Interfaz HID desmontada. Direccion: ");
  Serial1.println(dev_addr);
  setLedColor(COLOR_DESCONECTADO); // Amarillo
  estado=1; //modo sieguelineas al desconectar usb
}

// --- CALLBACK DE REPORTE (AÚN USANDO CÓDIGO BRUTO DE DEBUG) ---
// --- CALLBACK DE REPORTE CORREGIDO ---
void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len)
{
    // 1. FILTRO DE ID: El primer byte (report[0]) es el ID del reporte.
    // Si el ID es 02 (o cualquier cosa que no sea 01), lo ignoramos y pedimos el siguiente.
    if (report[0] != 0x01) {
        tuh_hid_receive_report(dev_addr, instance);
        return; // Salimos de la función sin imprimir ni procesar nada
    }

    // --- Si llegamos aquí, es el Reporte 01 (EL BUENO) ---

    //Serial1.print("MANDO (len="); Serial1.print(len); Serial1.print("): ");
    //movemos los servos segun los falsos analogicos del mando

    //report[4]=128; // joystick izquierdo centro
    //report[4]=0; // joystick izquierdo arriba
    //report[4]=255; // joystick izquerdo abajo

    //report[5]=15; // joystick derecho centro
    //report[5]=31; // joystick derecho arriba
    //report[5]=79; // joystick derecho abajo

    /// PRIMERO LEO EL BOTON TAL PARA CAMBIAR EL ESTADO ENTRE TELEDIRIGIDO O SIGUELINEAS

    //if (report[x]==y]){estado=!estado;}
    bool pulsado = false;
    if (estado == 0){ //modo control remoto
      
      if (report[4]==128){servo2.write(90);}
      if (report[4]==0){
        servo2.write(180);
        pulsado=true;}
      if (report[4]==255){
        servo2.write(0);
        pulsado=true;}
      
      if (report[5]==15){servo1.write(90);}
      if (report[5]==31){
        servo1.write(0);
        pulsado=true;}
      if (report[5]==79){
        servo1.write(180);
        pulsado=true;
        }

    }
    
      
    if (report[6]==72 && cambio==0){ //pulso el boton B para cambiar entre siguelineas y contro remoto
    estado=!estado;
    pulsado=true;
    cambio=1;  
    }

    if (report[6]==64){cambio=0;} //el valor 15 indica ningun boton pulsado, reseteo el cabmio. Esto el para que solo cambie el esado 1 vez cada vez que pulsto B
 



      // Imprimimos solo los datos del mando
      for (uint16_t i = 0; i < len; i++) {
          // Formateo visual para que quede alineado
          if (report[i] < 10) Serial1.print("00");
          else if (report[i] < 100) Serial1.print("0");
          
          Serial1.print(report[i], DEC); 
          Serial1.print(" ");
      }
      Serial1.println(); 
    //}

    // Visualización LED (Mantenemos tu lógica original solo para el reporte bueno)
    //if (estado==0){ //modo siguelineas
      //    if (digitalRead(sensorder==1)){
      //  servo1.write(180);
      //  pulsado=true;
      //  }
     // if (digitalRead(sensorder==0)){
     //   servo2.write(180);
     //   pulsado=true;
     //   }
    //}
    if (pulsado) {
        setLedColor(COLOR_PULSADO); // Verde
    } else {
        setLedColor(COLOR_BASE); // Azul
    }
    
    // Continuar el polling para recibir el siguiente dato
    tuh_hid_receive_report(dev_addr, instance);
}

// --- OTROS CALLBACKS (tuh_mount_cb, tuh_umount_cb, setup, loop) SON LOS MISMOS ---

void tuh_mount_cb(uint8_t dev_addr)
{
  Serial1.print("Dispositivo conectado. Direccion: ");
  Serial1.println(dev_addr);
  // El color se establece en tuh_hid_mount_cb
  estado=0; //modo control remoto al conectar el usb
}

void tuh_umount_cb(uint8_t dev_addr)
{
  Serial1.print("Dispositivo desconectado. Direccion: ");
  Serial1.println(dev_addr);
  setLedColor(COLOR_DESCONECTADO); 
}

void setup() {
  Serial1.begin(115200); 
  setLedColor(COLOR_BASE); 

  Serial1.println("--- RP2040 USB Host Gamepad Reader ---");
  
  if (!USBHost.begin(0)) { 
    Serial1.println("ERROR al inicializar USB Host.");
    setLedColor(COLOR_ERROR); 
    while (1) {
        led.neoPixelFill(COLOR_ERROR, true);
        delay(200);
        led.neoPixelClear(true);
        delay(200);
    }
  }
  Serial1.println("USB Host inicializado con éxito. Conecte el Gamepad.");
  servo1.attach(pinServo1);
  servo2.attach(pinServo2);
  pinMode(sensorizq, INPUT);
  pinMode(sensorder, INPUT);
}

void loop() {
  USBHost.task();

  if (estado == 1){ //modo siguelineas. Esto se cambia en el void que leo las pulsaciones, sino no hay mando conectado está en modo siguelineas
      if (digitalRead(sensorder)==1){ //Negro, 
        servo2.write(90);
        }
      if (digitalRead(sensorder)==0){ //blanco
        servo2.write(180);
        }

           
      if (digitalRead(sensorizq)==1){ //Negro, 
        servo1.write(90);
        }
      if (digitalRead(sensorizq)==0){ //blanco
        servo1.write(0);
        }
    
    }
}
