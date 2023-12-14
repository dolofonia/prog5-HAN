#include <iostream>
#include <mosquittopp.h>

const char* broker_address = "your_mqtt_broker_address"; // Replace with your MQTT broker address
const int broker_port = 1883; // Default MQTT port
const char* topic = "test/message";
const char* message = "Hello, this is a test message";

class MyMqttPublisher : public mosqpp::mosquittopp {
public:
    MyMqttPublisher(const char* id) : mosqpp::mosquittopp(id) {
        connect(broker_address, broker_port, 60);
    }

    void on_connect(int rc) override {
        if (rc == 0) {
            std::cout << "Connected to MQTT broker" << std::endl;
            publish(nullptr, topic, strlen(message), message, 0, false);
        } else {
            std::cerr << "Failed to connect to MQTT broker with result code " << rc << std::endl;
        }
    }

    void on_publish(int mid) override {
        std::cout << "Message published with mid " << mid << std::endl;
        disconnect();
    }
};

int main() {
    MyMqttPublisher mqtt_publisher("mqtt_publisher");
    while (true) {
        int rc = mqtt_publisher.loop();
        if (rc) {
            std::cerr << "Error in the MQTT loop: " << mosqpp::strerror(rc) << std::endl;
            break;
        }
    }
    return 0;
}