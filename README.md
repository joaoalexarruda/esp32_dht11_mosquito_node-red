# Temperature and Humidity Sensor Project

This project uses an ESP32 and DHT11 sensor to measure temperature and humidity. The data is sent to a Mosquitto broker and visualized on a Node-RED dashboard.

It's an assignment for the course "Internet of Things" at the Instituto Politécnico de Portalegre, in Portugal.

You can find out more about the course [here](https://www.ipportalegre.pt/pt/oferta-formativa/pos-graduacao-data-science-and-digital-transformation).

## Screenshots

![Node-RED Dashboard](https://imgur.com/PkG2q7D.png)

![Node-RED Flow](https://imgur.com/jv2cUAx.png)

![Mosquitto Broker](https://imgur.com/qeqDIId.png)

You can find more screenshots [here](https://imgur.com/a/jabCIWW).

## Hardware Requirements

- ESP32
- DHT11 Temperature and Humidity Sensor
- 10k Ohm resistor
- Breadboard
- Jumper wires

## Software Requirements

- PlatformIO (preferred) or Arduino IDE
- Mosquitto MQTT Broker
- Node-RED

## Setup and Installation

1. **Hardware Setup**: Connect the DHT11 sensor to your ESP32. The connections are as follows:

   - DHT11 VCC to ESP32 3V3
   - DHT11 GND to ESP32 GND
   - DHT11 DATA to ESP32 GPIO 27
   - DHT11 DATA to 10k Ohm resistor
   - 10k Ohm resistor to ESP32 3V3

   ![ESP32 DHT11 Wiring](https://imgur.com/WF8ZJ7I.jpg)

2. **Software Setup**: 
   - Install and setup VSCode + PlatformIO (preferred) or Arduino IDE.
   - Install Mosquitto MQTT Broker.
   - Install Node-RED.
   - Install Node-RED Dashboard.

3. **Code Deployment**: Upload the provided code to your ESP32.

## Running the Project

1. Start the Mosquitto broker.
2. Start Node-RED and open the provided dashboard.
3. Power on the ESP32.

## Code Explanation

The code is all contained in the `src/main.cpp` file. It's divided into 3 main sections:

1. **Libraries**: The libraries used in this project are:

   - `WiFi.h`: Used to connect to a WiFi network.
   - `PubSubClient.h`: Used to connect to a MQTT broker and publish messages.
   - `DHT.h`: Used to read data from the DHT11 sensor.

2. **Constants**: The constants used in this project are:

   - `ssid`: The SSID of the WiFi network to connect to.
   - `password`: The password of the WiFi network to connect to.
   - `mqtt_server`: The IP address of the MQTT broker.
   - `mqtt_port`: The port of the MQTT broker.
   - `DHT_PIN`: The GPIO pin of the ESP32 that the DHT11 sensor is connected to.
   - `DHT_TYPE`: The type of the DHT sensor (DHT11, DHT21 or DHT22).

3. **Functions**: The functions used in this project are:

   - `setup()`: The setup function is called once when the ESP32 boots up. It's used to initialize the serial port, connect to the WiFi network and the MQTT broker, and initialize the DHT sensor.
   - `loop()`: The loop function is called repeatedly after the setup function. It's used to read the temperature and humidity from the DHT sensor and publish them to the MQTT broker.   

   There are also some helper functions used to connect to the WiFi network and the MQTT broker.


## MQTT Broker

Download and install the Mosquitto MQTT Broker from [here](https://mosquitto.org/download/).

## Node-RED

Download and install Node-RED from [here](https://nodered.org/docs/getting-started/local).


## Node-RED Dashboard

Install the Node-RED Dashboard from [here](https://flows.nodered.org/node/node-red-dashboard).

## Troubleshooting

Be sure to follow the hardware setup correctly. If you're using a different ESP32 board, the GPIO pins may be different.

In the mosquitto.conf file, be sure to set the `allow_anonymous` option to `true`.
Also set listener to `1883 0.0.0.0` as seen below.

![Mosquitto Config](https://imgur.com/OqW4wx4.png)

## Future Improvements

- Connect another ESP32 with a DHT11 sensor to the same MQTT broker and display the data on the same dashboard.
- Subscribe multiple devices to the same MQTT broker so they can do actions based on the data received.
- Use a good sensor instead of a cheap DHT11 sensor.
- Implement a better way to handle errors.
- Utilize these sensors in a real-world scenario, like a smart home.