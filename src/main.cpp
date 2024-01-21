// Inclui bibliotecas necessárias
#include <Arduino.h> // Este é o arquivo principal incluído do SDK do Arduino. Ele define todas as funções e tipos base usados na programação do Arduino.
#include <WiFi.h> // Esta é uma biblioteca que permite ao Arduino se conectar a uma rede WiFi. Ela fornece funções para conectar a uma rede, desconectar, verificar o status da conexão, e mais.
#include <PubSubClient.h> // Esta é uma biblioteca cliente para MQTT (Message Queuing Telemetry Transport), um protocolo de mensagens leve para pequenos sensores e dispositivos móveis. É frequentemente usado em aplicações de IoT.
#include <DHT.h> // Esta é uma biblioteca para a série DHT de sensores de temperatura/umidade de baixo custo. Ela fornece funções para ler a temperatura e a umidade desses sensores.
#include <Adafruit_Sensor.h> // Esta é uma classe base para sensores da empresa Adafruit. É usada em conjunto com bibliotecas de sensores específicos (como a biblioteca DHT mencionada acima) para ler dados de sensores Adafruit.

// Wi-Fi login e senha
const char *ssid = "joaoalex1";
const char *password = "joao1579";

// IPv4 e porta
#define mqtt_server "192.168.29.165"
#define mqtt_port 1883

// Pino utilizado no ESP32 e sensor DHT11
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Inicializar cliente Wi-Fi e MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Buffer circular para leituras
const int numReadings = 7;
int readingsIndex = 0;

void setup_wifi() {
  // Conectar ao Wi-Fi
  delay(10);
  Serial.println("Conectando ao Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando...");
  }
  Serial.println("Conectado ao Wi-Fi");
}

void reconnect() {
  // Reconectar ao broker MQTT
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado ao broker MQTT");
    } else {
      Serial.print("Falhou, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void updateReadings(float *readings, float newValue) {
  // Atualizar o buffer circular de leituras
  readings[readingsIndex] = newValue;
  readingsIndex = (readingsIndex + 1) % numReadings;
}

// Inicia arrays com -1
float temperatureReadings[numReadings] = {-1.0};
float humidityReadings[numReadings] = {-1.0};

float calculateMovingAverage(float *readings) {
  float sum = 0;
  int count = 0;

  // Calcular a soma dos valores válidos
  for (int i = 0; i < numReadings; i++) {
    if (readings[i] != -1.0) {
      sum += readings[i];
      count++;
    }
  }

  // Verificar se há pelo menos um valor válido
  if (count > 0) {
    return sum / count;
  } else {
    return -1.0;  // Retorna um valor indicando que não há dados válidos suficientes para calcular média.
  }
}



void setup() {
  // Inicializar o ESP32 e o sensor DHT
  Serial.begin(115200);
  dht.begin();
  // Inicializar o Wi-Fi e o MQTT
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  // Reconectar ao broker MQTT se a conexão cair
  if (!client.connected()) {
    reconnect();
  }

  // Ler temperatura e umidade do sensor DHT
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    // Ignorar leituras inválidas
    Serial.println("Falha ao ler do sensor DHT");
    delay(2000);
    return;
  }

  // Atualizar leituras
  updateReadings(temperatureReadings, temperature);
  updateReadings(humidityReadings, humidity);

  // Calcular médias móveis
  float avgTemperature = calculateMovingAverage(temperatureReadings);
  float avgHumidity = calculateMovingAverage(humidityReadings);

  // Converter valores float para strings para payload MQTT
  char tempStr[8];
  dtostrf(temperature, 2, 2, tempStr);

  char humStr[8];
  dtostrf(humidity, 2, 2, humStr);

  char avgTempStr[8];
  dtostrf(avgTemperature, 2, 2, avgTempStr);

  char avgHumStr[8];
  dtostrf(avgHumidity, 2, 2, avgHumStr);

  // Tópicos MQTT para publicar os dados
  char tempTopic[] = "esp32/temperatura";
  char humTopic[] = "esp32/umidade";
  char avgTempTopic[] = "esp32/media_movel_temperatura";
  char avgHumTopic[] = "esp32/media_movel_umidade";

  // Publicar valores atuais e médias móveis nos tópicos MQTT
  client.publish(tempTopic, tempStr);
  client.publish(humTopic, humStr);
  client.publish(avgTempTopic, avgTempStr);
  client.publish(avgHumTopic, avgHumStr);

  // Imprimir informações de debug
  Serial.println();
  Serial.println("+-------------------+-------------------+");
  Serial.println("| Parâmetro         | Valor             |");
  Serial.println("+-------------------+-------------------+");
  Serial.printf("| Temperatura       | %-17.2f |\n", temperature);
  Serial.printf("| Umidade           | %-17.2f |\n", humidity);
  Serial.printf("| Média Móvel Temp. | %-17.2f |\n", avgTemperature);
  Serial.printf("| Média Móvel Umid. | %-17.2f |\n", avgHumidity);
  Serial.println("+-------------------+-------------------+");
  Serial.println();

  Serial.println("Publicado temperatura no tópico MQTT: " + String(tempTopic));
  Serial.println("Publicado umidade no tópico MQTT: " + String(humTopic));
  Serial.println("Publicada média móvel de temperatura no tópico MQTT: " + String(avgTempTopic));
  Serial.println("Publicada média móvel de umidade no tópico MQTT: " + String(avgHumTopic));

  delay(5000);
}
