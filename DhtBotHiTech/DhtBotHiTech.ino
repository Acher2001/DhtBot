
#define WIFI_SSID "Personal"
#define WIFI_PASS "Setzakrita"
#define BOT_TOKEN "7062887077:AAE4Gw6TfyTvMOn96006g98GGUtw8Ws1-OI"
#include <FastBot.h>
#include <DHT.h>

#define DHTPIN 2  // Укажите номер пина, к которому подключен DHT22
#define DHTTYPE DHT22  // Укажите тип датчика (DHT22, DHT11, etc.)

DHT dht(DHTPIN, DHTTYPE);
FastBot bot(BOT_TOKEN);
void setup() {
  connectWiFi();
  bot.attach(newMsg);
  Serial.begin(115200);
  dht.begin();
}
// обработчик сообщений
void newMsg(FB_msg& msg) {
  // выводим ID чата, имя юзера и текст сообщения
  Serial.print(msg.chatID);     // ID чата 
  Serial.print(", ");
  Serial.print(msg.username);   // логин
  Serial.print(", ");
  
  if (msg.text == "/Climatic_data_HiTech") { 
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
      bot.sendMessage("Ошибка при чтении данных с датчика DHT22!", msg.chatID);
    } else {
      String data = "Температура в Хайтеке: " + String(temperature) + "°C\nВлажность в Хайтеке: " + String(humidity) + "%";
      bot.sendMessage(data, msg.chatID);
    }
  }
}

void loop() {
  bot.tick();
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Получаем текущее время

}


void connectWiFi() {
  delay(2000);
  Serial.begin(115200);
  Serial.println();
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 15000) ESP.restart();
  }
  Serial.println("Connected");
}