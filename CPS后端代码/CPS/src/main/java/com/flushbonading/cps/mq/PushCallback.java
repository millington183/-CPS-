package com.flushbonading.cps.mq;

import com.flushbonading.cps.mq.handler.DataHandler;
import com.google.protobuf.InvalidProtocolBufferException;
import org.eclipse.paho.client.mqttv3.IMqttAsyncClient;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.springframework.beans.factory.annotation.Autowired;

import java.text.SimpleDateFormat;
import java.util.logging.Logger;

public class PushCallback implements MqttCallback {
    DataHandler handler;
    private IMqttAsyncClient Client;
    private static final Logger logger = Logger.getLogger(PushCallback.class.getCanonicalName());
    private MqClient mqClient;
    private int reConnTimes = 0;

    @Autowired
    public PushCallback(MqClient client, DataHandler handler) {
        mqClient = client;
        this.handler = handler;
    }

    @Override
    public void connectionLost(Throwable cause) {
        logger.info("connect is losted,and try to reconnect,cause = " + cause.getMessage());
        cause.printStackTrace();
        while (true) {
            if (mqClient.reConnect()) {
                break;
            }
            try {
                if (reConnTimes++ > 20) {//前20次每秒重连一次
                    Thread.sleep(1000);
                } else {//超过20次后没10s重连一次
                    Thread.sleep(10000);
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void messageArrived(String topic, MqttMessage message) throws InvalidProtocolBufferException {
        byte[] payload = message.getPayload();
        OnenetMq.Msg obj = OnenetMq.Msg.parseFrom(payload);
        long at = obj.getTimestamp();
        long msgid = obj.getMsgid();
        String body = new String(obj.getData().toByteArray());

        SimpleDateFormat slf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        String time = slf.format(at);

        logger.info("time = " + time +
                ",msg id: " + msgid +
                ", body: " + body);

        handler.parseData(msgid, body);
    }

    @Override
    public void deliveryComplete(IMqttDeliveryToken token) {
        Client = token.getClient();
    }


}
