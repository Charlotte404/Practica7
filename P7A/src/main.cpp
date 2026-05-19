#include <Arduino.h>
#include "AudioGeneratorAAC.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourcePROGMEM.h"
#include "sampleaac.h"

AudioFileSourcePROGMEM *in;
AudioGeneratorAAC *aac;
AudioOutputI2S *out;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Iniciant àudio...");

  // Font AAC en memòria
  in = new AudioFileSourcePROGMEM(sampleaac, sizeof(sampleaac));

  // Decoder
  aac = new AudioGeneratorAAC();

  // Salida I2S
  out = new AudioOutputI2S();

  // 🔊 Guany (Volum de 0.0 a 1.0)
  out->SetGain(0.15);

  // 🎧 PINES I2S SEGURS PER A ESP32-S3
  // Format: SetPinout(BCLK, LRCK, DOUT)
  out->SetPinout(4, 5, 6);

  // Forçar mode Mono
  out->SetOutputModeMono(true);

  // Iniciar reproducció
  if (!aac->begin(in, out)) {
    Serial.println("ERROR: No s'ha pogut iniciar el descodificador AAC");
  } else {
    Serial.println("Reproduint àudio...");
  }
}

void loop() {
  if (aac->isRunning()) {
    if (!aac->loop()) {
      aac->stop();
      Serial.println("Àudio finalitzat");
    }
  } else {
    Serial.println("Reiniciant en 2 segons...");
    delay(2000);

    // 🌟 SOLUCIÓ CORRECTA: Rebobinem el punter de l'àudio a la posició 0
    in->seek(0, SEEK_SET); 

    if (!aac->begin(in, out)) {
      Serial.println("ERROR en reiniciar AAC");
    } else {
      Serial.println("Reproduint àudio de nou...");
    }
  }
}