#define BLYNK_TEMPLATE_ID "TMPL6TXV8POGb"
#define BLYNK_TEMPLATE_NAME "Gas and Flame Monitor"
#define BLYNK_AUTH_TOKEN "VubJ5G_tlAhG8NhLf4PjKgzq2eTksgKn"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;

// Wi-Fi Credentials
char ssid[] = "Shafat";
char pass[] = "shafat22";

// GPIO Pins
#define MQ2_SENSOR       36  // AO of MQ2 smoke sensor
#define FLAME_SENSOR_D   34  // D0 of Flame sensor
#define RED_LED          25
#define GREEN_LED        26
#define BUZZER_PIN       33
#define ONBOARD_LED      2
#define YELLOW_LED       27

// Blynk Virtual Pins
#define VPIN_SMOKE V1
#define VPIN_FLAME V2
#define VPIN_ALERT V3

int smokeValue = 0;
int flameValue = 1;  // Digital: 0 = detected
bool buzzerOn = false;
bool wifiConnected = false;

unsigned long lastReconnectAttempt = 0;
const unsigned long reconnectInterval = 10000; // every 10s

void readSensors() {
  smokeValue = map(analogRead(MQ2_SENSOR), 0, 4095, 0, 100);
  flameValue = digitalRead(FLAME_SENSOR_D);  // LOW = flame

  bool flameDetected = (flameValue == LOW);
  bool smokeDetected = (smokeValue > 20); // threshold adjustable

  // Debug print
  Serial.print("Smoke: ");
  Serial.print(smokeValue);
  Serial.print("% | Flame: ");
  Serial.println(flameDetected ? "YES" : "NO");

  // LED indicators
  digitalWrite(RED_LED, smokeDetected ? HIGH : LOW);
  digitalWrite(GREEN_LED, flameDetected ? HIGH : LOW);

  // Buzzer control
  if (smokeDetected || flameDetected) {
    if (!buzzerOn) {
      tone(BUZZER_PIN, 2000);
      buzzerOn = true;
    }
    digitalWrite(ONBOARD_LED, HIGH);  // Turn on onboard LED when alert
  } else {
    if (buzzerOn) {
      noTone(BUZZER_PIN);
      buzzerOn = false;
    }
    digitalWrite(ONBOARD_LED, LOW);  // Turn off onboard LED when safe
  }

  // Blynk updates
  if (wifiConnected) {
    Blynk.virtualWrite(VPIN_SMOKE, smokeValue);
    Blynk.virtualWrite(VPIN_FLAME, flameDetected ? "🔥 Flame Detected" : "✅ No Flame");

    if (smokeDetected && flameDetected) {
      Blynk.virtualWrite(VPIN_ALERT, "🔥 Smoke + Flame Detected!");
      Blynk.logEvent("gas_and_flame", "🔥 Gas + Flame Detected!");
    } else if (smokeDetected) {
      Blynk.virtualWrite(VPIN_ALERT, "💨 Smoke Detected");
      Blynk.logEvent("gas", "Smoke Detected!");
    } else if (flameDetected) {
      Blynk.virtualWrite(VPIN_ALERT, "🔥 Flame Detected");
      Blynk.logEvent("flame", "Flame Detected!");
    } else {
      Blynk.virtualWrite(VPIN_ALERT, "✅ Safe");
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(MQ2_SENSOR, INPUT);
  pinMode(FLAME_SENSOR_D, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(ONBOARD_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  noTone(BUZZER_PIN);

  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(ONBOARD_LED, LOW);

  // Initial Wi-Fi connection
  Serial.println("📶 Connecting to Wi-Fi...");
  WiFi.begin(ssid, pass);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 40) {
    Serial.print(".");
    delay(200);
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Wi-Fi Connected!");
    Serial.print("📡 IP: ");
    Serial.println(WiFi.localIP());

    wifiConnected = true;
    digitalWrite(YELLOW_LED, HIGH);     // Turn on yellow when connected
    digitalWrite(ONBOARD_LED, HIGH);    // Blue LED steady = connected
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    timer.setInterval(2000L, readSensors);
  } else {
    Serial.println("\n❌ Wi-Fi failed. Running in offline mode.");
    wifiConnected = false;
    timer.setInterval(2000L, readSensors);
  }
}

void loop() {
  if (wifiConnected && WiFi.status() == WL_CONNECTED) {
    Blynk.run();
    timer.run();
  } else {
    // Retry Wi-Fi every 10s
    unsigned long now = millis();
    if (now - lastReconnectAttempt > reconnectInterval) {
      Serial.println("🔄 Reconnecting Wi-Fi...");
      WiFi.begin(ssid, pass);
      lastReconnectAttempt = now;

      if (WiFi.status() == WL_CONNECTED) {
        Serial.println("✅ Reconnected to Wi-Fi!");
        digitalWrite(YELLOW_LED, HIGH);
        digitalWrite(ONBOARD_LED, HIGH);
        wifiConnected = true;
        Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
      }
    }

    readSensors();  // Local monitoring even without Wi-Fi
  }
}
