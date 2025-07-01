
  ______ _____          _____            _____ ______ 
 |  ____/ ____|   /\   |  __ \     /\   / ____|  ____|
 | |__ | |  __   /  \  | |__) |   /  \ | |  __| |__   
 |  __|| | |_ | / /\ \ |  _  /   / /\ \| | |_ |  __|  
 | |   | |__| |/ ____ \| | \ \  / ____ \ |__| | |____ 
 |_|    \_____/_/    \_\_|  \_\/_/    \_\_____|______|
                                      
---

## Zasada działania

1. **Sygnał kwadratowy** to ciąg impulsów (np. z czujnika Halla, enkodera lub impulsatora).
2. Zliczamy ilość impulsów w określonym czasie (np. przez 1 sekundę).
3. Znając liczbę impulsów na jeden obrót oraz obwód koła, możemy wyznaczyć prędkość liniową.


```cpp
const int signalPin = 2;          
volatile unsigned int pulses = 0;
unsigned long previousTime = 0;
float wheelCircumference = X ;    
int pulsesPerRevolution = X;       

void setup() {
  pinMode(signalPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(signalPin), countPulse, RISING);
  Serial.begin(9600);
}

void loop() {
  unsigned long now = millis();
  if (now - previousTime >= 1000) { // Every second
    float revolutions = (float)pulses / pulsesPerRevolution;
    float speed = (revolutions * wheelCircumference) * 3.6; // m/s to km/h
    Serial.print("Speed km/h: ");
    Serial.println(speed);

    pulses = 0;
    previousTime = now;
  }
}

void countPulse() {
  pulses++;
}
```

---

## Wyjaśnienie

- Funkcja **countPulse** zwiększa licznik za każdym razem, gdy pojawi się impuls.
- W pętli głównej co sekundę liczone są obroty i prędkość.
- Prędkość liczona jest jako:  
  `prędkość (km/h) = liczba obrotów w sekundzie * obwód koła (m) * 3.6`

---

## Dostosowanie kodu

- Jeśli czujnik daje więcej impulsów na obrót (np. 20 impulsów/obrót), zmień `pulsesPerRevolution` na odpowiednią wartość.
- Ustaw `wheelCircumference` zgodnie z rzeczywistą długością obwodu koła.

---
