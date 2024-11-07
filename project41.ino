#include <Adafruit_LiquidCrystal.h>

// C++ code
//
Adafruit_LiquidCrystal lcd(0);
#define botao 6
// Pinos
const int ledVerde = 9;
const int ledVermelho = 4;
const int buzzer = 5;
const int sensorPIR = 3;
int som_desativado=0;

// Estado do sistema
bool sistemaAtivado = true;

void setup() {
    lcd.begin(16, 2);
    pinMode(ledVerde, OUTPUT);
    pinMode(ledVermelho, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(sensorPIR, INPUT);
    pinMode(botao, INPUT_PULLUP);

    lcd.print("Sistema Pronto");
    lcd.setBacklight(1);
}

void loop() {
    // Verifica o estado do botão
    if (digitalRead(botao) == LOW) {
      while (digitalRead(botao)==LOW){}
        sistemaAtivado = !sistemaAtivado; // Alterna o estado
        delay(300); // Debounce
    }

    // Verifica se o sistema está ativado
    if (sistemaAtivado==true) {
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledVermelho, HIGH);
		som_desativado=0;
        int movimento = digitalRead(sensorPIR);
        if (movimento) {
            lcd.setCursor(0, 0);
            lcd.print("Movimento Detec.");
            tone(buzzer, 1000); // Emite som
        } else {
            lcd.setCursor(0, 0);
            lcd.print("Sistema Ativo  ");
            noTone(buzzer); // Para o som
        }
    } else {
        digitalWrite(ledVerde, HIGH);
        digitalWrite(ledVermelho, LOW);
        lcd.setCursor(0, 0);
        lcd.print("Sistema Desativ.");
      if (som_desativado==0){
      	tone(5,1000);
        delay(1000);
        noTone(buzzer); // Garante que o som esteja desligado
      }
      	som_desativado=1;
    }

    delay(500); // Aguarda 0.5 segundos antes da próxima leitura
}