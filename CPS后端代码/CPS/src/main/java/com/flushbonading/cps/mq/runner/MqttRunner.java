package com.flushbonading.cps.mq.runner;


import com.flushbonading.cps.mq.MqClient;
import com.flushbonading.cps.mq.handler.DataHandler;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.core.env.Environment;
import org.springframework.stereotype.Component;

/**
 * @Author: zyx
 * @Description:
 * @Date: 2021-07-08 17:07
 **/
@Component
@ComponentScan("com.flushbonading.cps.mapper")
public class MqttRunner implements CommandLineRunner {

    @Autowired
    DataHandler handler;
    @Autowired
    Environment env;

    @Override
    public void run(String... args) throws Exception {
        MqClient mqClient = new MqClient(handler, env);
        mqClient.connect();
    }

}
