#include "config.h"
#include "display.h"
#include "music_control.h"
#include <HomeSpan.h>
#include <DHT.h>
#include <DHT_U.h>
esp_timer_handle_t my_timer;

DHT dht(DHTPIN, DHT22);  // Initialize DHT sensor for AM2302 (DHT22 type)

void IRAM_ATTR onTimer(void* arg) {
    Serial.println("Timer tick");
    // Additional code as needed
}

// Inițializare și configurare timer
void initTimer() {
    const esp_timer_create_args_t timer_args = {
        .callback = &onTimer,
        .name = "periodic_timer"};

    esp_timer_handle_t my_timer;
    esp_timer_create(&timer_args, &my_timer);
    esp_timer_start_periodic(my_timer, TIMER_INTERVAL_SEC * 1000000);
}

struct MusicControl : Service::Switch {
    SpanCharacteristic* power;

    MusicControl() : Service::Switch() {
        power = new Characteristic::On();
    }

    boolean update() override {
        if (power->getNewVal()) {
            Serial.println("Action: Play Next Song or Toggle Pause/Play");

            myDFPlayer.play();
            updateDisplay(0);
        }
        power->setVal(false);
        return true;
    }
};

void setup() {
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
    dht.begin();
    initTimer();

    initMusicControl();
    initDisplay();

    homeSpan.begin(Category::Bridges, "MP3 music player");
    homeSpan.setWifiCallback([]() { homeSpan.setPairingCode("31212321"); });
    homeSpan.setQRID("321-12-321");

    new SpanAccessory();
    new Service::AccessoryInformation();
    new Characteristic::Name("Music Player");
    new MusicControl();
    updateDisplay(0);
}

void loop() {
    // Poll HomeSpan for any network activity and to process service routines
    homeSpan.poll();

    // Handle music controls based on button presses
    handleMusicControl();

    // Update sensor readings periodically without blocking other operations
    static unsigned long lastSensorUpdate = 0;
    unsigned long currentMillis = millis();
    const unsigned long sensorUpdateInterval = 2000;  // 2 seconds between sensor updates

    if (currentMillis - lastSensorUpdate >= sensorUpdateInterval) {
        lastSensorUpdate = currentMillis;
        float humidity = dht.readHumidity();
        float temperature = dht.readTemperature();

        if (!isnan(humidity) && !isnan(temperature)) {
            updateSensorReadings(temperature, humidity);
        }
    }

    // Minimal delay to prevent the loop from spinning too quickly
    delay(10);  // Reduce the delay to a minimum to allow for responsive polling and button checks
}
