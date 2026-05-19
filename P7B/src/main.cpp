#include "Audio.h"
#include "SD.h"
#include "FS.h"

// Connexions digitals utilitzades i adaptades per a l'ESP32-S3
#define SD_CS        10
#define SPI_MOSI     11
#define SPI_MISO     13
#define SPI_SCK      12

#define I2S_DOUT     17
#define I2S_BCLK     18
#define I2S_LRC      16

Audio audio;

void setup(){
  Serial.begin(115200);
  delay(1500); 
  
  Serial.println("\n--- INICIANT REPRODUCCTOR D'ÀUDIO ---");

  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);
  
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SD_CS);
  
  Serial.println("Intentant connectar amb la targeta SD...");
  if(!SD.begin(SD_CS, SPI, 4000000)){
    Serial.println("ERROR CRÍTIC: No s'ha pogut inicialitzar la targeta SD!");
    while(true); 
  }
  Serial.println("Targeta SD detectada correctament.");
  
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(10); 

  Serial.println("Intentant carregar el fitxer d'àudio prova.wav...");
  // CORRECCIÓ: Afegit el .wav al final
  audio.connecttoFS(SD, "/prova.wav.wav");
}

void loop(){
  audio.loop();
}

// Funcions de monitorització
void audio_info(const char *info){ Serial.print("INFO ÀUDIO: "); Serial.println(info); }
void audio_id3data(const char *info){ Serial.print("id3data: "); Serial.println(info); }
void audio_eof_mp3(const char *info){ Serial.print("Fitxer finalitzat: "); Serial.println(info); }
void audio_showstation(const char *info){ Serial.print("station "); Serial.println(info); }
void audio_showstreaminfo(const char *info){ Serial.print("streaminfo "); Serial.println(info); }
void audio_showstreamtitle(const char *info){ Serial.print("streamtitle "); Serial.println(info); }
void audio_bitrate(const char *info){ Serial.print("bitrate "); Serial.println(info); }
void audio_commercial(const char *info){ Serial.print("commercial "); Serial.println(info); }
void audio_icyurl(const char *info){ Serial.print("icyurl "); Serial.println(info); }
void audio_lasthost(const char *info){ Serial.print("lasthost "); Serial.println(info); }
void audio_eof_speech(const char *info){ Serial.print("eof_speech "); Serial.println(info); }