#include <Arduino_JSON.h>
#include <Firebase.h>
#include "ESP8266WiFi.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
  
// Credenciais de Rede e do Firebase
#define FIREBASE_HOST "iotboard-ee46a-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "Zzzbx7iQei3d6UANISjLCPEyJQPFDFmjsEU7BJxF"

#define WIFI_SSID "Camila e Aline"; //VARIÁVEL QUE ARMAZENA O NOME DA REDE SEM FIO EM QUE VAI CONECTAR
#define WIFI_PASSWORDd "987877759"; //VARIÁVEL QUE ARMAZENA A SENHA DA REDE SEM FIO EM QUE VAI CONECTAR


// Configurações do servidor NTP
#define NTP_OFFSET   60 * 60     
#define NTP_INTERVAL 60 * 1000   
#define NTP_ADDRESS  "pool.ntp.org"
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);
  
// Periodo entre scans, em segundos
const int period = 2;
  
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  
  // conectando-se ao wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
   
  // Se conectando ao Firebase e iniciando o servidor NTP
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  timeClient.begin();
  
  Serial.println("Setup done");
}
  
void loop() {
  // mantendo o led ligado durante a fase de scan
  digitalWrite(LED_BUILTIN, LOW); //o LED no ESP8266 é ligado de maneira que acende em LOW
  timeClient.update();
  
  // iniciando o scan de redes
  Serial.println("scan start");
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  timeClient.update();
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
  
    // capturando o tempo atual
    unsigned long epochTime =  timeClient.getEpochTime();
    for (int i = 0; i < n; ++i) {
      // enviando o nome da rede(SSID) e a força da rede(RSSI), além do timestamp atual
      Firebase.setInt("wifi_log/" + String(epochTime) +"/" +  WiFi.SSID(i) , WiFi.RSSI(i));
       
      // tratando erros
      if (Firebase.failed()) {
          Serial.print("upload was failed");
          Serial.println(Firebase.error());  
          return;
      }
      delay(500);
    }
  }
  // Esperando um periodo específico até o proximo scan, com o led desligado
  digitalWrite(LED_BUILTIN, HIGH);
  delay(period*60000);
}
