# Temperature and Humidity Sensor Project

This [project](https://github.com/joaoalexarruda/esp32_dht11_mosquito_node-red) uses an ESP32 and DHT11 sensor to measure temperature and humidity. The data is sent to a Mosquitto broker and visualized on a Node-RED dashboard. It's an improvement over [this simpler project](https://github.com/joaoalexarruda/esp32_dht11_webserver_mqtt), which only works on a local network with no dashboard. Have a look at the old one to see the differences.

It's an assignment for the course "Internet of Things" at the Instituto Politécnico de Portalegre, in Portugal.

You can find out more about the course [here](https://www.ipportalegre.pt/pt/oferta-formativa/pos-graduacao-data-science-and-digital-transformation).

## Screenshot

![Node-RED Dashboard and Setup](https://imgur.com/voznaFv.png)

You can find more screenshots [here](https://imgur.com/a/jabCIWW).

## Hardware Requirements

- ESP32
- DHT11 Temperature and Humidity Sensor
- 10k Ohm resistor
- Breadboard
- Jumper wires

![ESP32 DHT11 Breadboard](https://imgur.com/WF8ZJ7I.jpg)

## Software Requirements

- PlatformIO (preferred) or Arduino IDE
- Mosquitto MQTT Broker
- Node-RED

## Setup and Installation

There is a more detailed guide [here](ProjetoFinal_JoaoAlexArrudaDaSilva.pdf).

1. **Hardware Setup**: Connect the DHT11 sensor to your ESP32. The connections are as follows:

   - DHT11 VCC to ESP32 3V3
   - DHT11 GND to ESP32 GND
   - DHT11 DATA to ESP32 GPIO 4
   - DHT11 DATA to 10k Ohm resistor
   - 10k Ohm resistor to ESP32 3V3

   It should look something like this:
   ![ESP32 DHT11 Wiring](https://imgur.com/MiuOGkL.jpg)

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

## MQTT Broker

Download and install the Mosquitto MQTT Broker from [here](https://mosquitto.org/download/).
You can start the broker with the default configuration by running `mosquitto` in the terminal.

## Node-RED

Download and install Node-RED from [here](https://nodered.org/docs/getting-started/local).
You can start Node-RED by running `node-red` in the terminal.

![Node-RED Flow](https://imgur.com/jv2cUAx.png)

It's very easy to create a flow in Node-RED. You can find more information about it [here](https://nodered.org/docs/getting-started/first-flow).


## Node-RED Dashboard

Install the Node-RED Dashboard from [here](https://flows.nodered.org/node/node-red-dashboard).
You can access the dashboard by going to `http://localhost:1880/ui` in your browser.

![Node-RED Dashboard](https://imgur.com/XGUOuPg.png)

## Troubleshooting

Be sure to follow the hardware setup correctly. If you're using a different ESP32 board, the GPIO pins may be different.

Pay attention to the serial output of the ESP32. It's very useful for debugging.

![Serial Output](https://imgur.com/kPssBJ0.png)

In the mosquitto.conf file, be sure to set the `allow_anonymous` option to `true`.
Also set listener to `1883 0.0.0.0` as seen below.

![Mosquitto Config](https://imgur.com/OqW4wx4.png)

## Considerations

- The code has comments explaining what each line does.
- The DHT11 sensor is a very cheap sensor. It's not very accurate and it's not very reliable. It's a good sensor to start with, but it's not recommended for real-world applications.
- It's very easy to install everything if you are running Linux. If you are running Windows, you may have some problems. I recommend using Fedora.
- VSCode + PlatformIO is preferred over the Arduino IDE. It's much easier to use and it has a lot of features, such as code completion, code linting, git integration, etc.
- The ESP32 is a very powerful microcontroller. It's very easy to use and it has a lot of features. It's a good choice for this project.
- Note that the arduino uno showed in the picture is not used in this project. The only microcontroller on is the ESP32.

## Future Improvements

- Connect another ESP32 with a DHT11 sensor to the same MQTT broker and display the data on the same dashboard.
- Subscribe multiple devices to the same MQTT broker so they can do actions based on the data received.
- Get a Raspberry Pi and install the Mosquitto MQTT Broker and Node-RED on it. This way you can have a dedicated device for this project.
- Use a good sensor instead of a cheap DHT11 sensor.
- Implement a better way to handle errors.
- Utilize these sensors in a real-world scenario, like a smart home. For example, turn on the air conditioner when the temperature is too high, or turn on the humidifier when the humidity is too low.