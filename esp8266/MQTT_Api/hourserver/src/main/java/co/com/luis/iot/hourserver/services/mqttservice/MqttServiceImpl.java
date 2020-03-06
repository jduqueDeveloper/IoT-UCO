package co.com.luis.iot.hourserver.services.mqttservice;

import org.eclipse.paho.client.mqttv3.*;
import org.springframework.stereotype.Service;

import java.util.UUID;

@Service
public class MqttServiceImpl implements MqttService{

    @Override
    public void publish() {
        String host = "tcp://192.168.1.16:1883";
        try {
            MqttClient mqttClient = new MqttClient(host, "java");
            MqttConnectOptions connOpts = new MqttConnectOptions();
            connOpts.setCleanSession(true);
            mqttClient.connect(connOpts);
            MqttMessage message = new MqttMessage("Json sucesfull java".getBytes());
            message.setQos(0);
            mqttClient.publish("jsonstatus", message);
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }



}
