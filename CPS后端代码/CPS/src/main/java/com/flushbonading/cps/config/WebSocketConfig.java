package com.flushbonading.cps.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.socket.server.standard.ServerEndpointExporter;

/**
 * WebSocket配置类
 *
 * @author zyx 2134208960@qq.com
 * @date 2021/6/8 8:54
 * @since 1.0.0
 */
@Configuration
public class WebSocketConfig {

    @Bean
    public ServerEndpointExporter serverEndpointExporter() {
        return new ServerEndpointExporter();
    }

//    @Override
//    public void configureMessageBroker(MessageBrokerRegistry config) {
//        /*
//         * 用户可以订阅来自"/topic"和"/user"的消息，
//         * 在Controller中，可通过@SendTo注解指明发送目标，这样服务器就可以将消息发送到订阅相关消息的客户端
//         *
//         * 在本Demo中，使用topic来达到群发效果，使用user进行一对一发送
//         *
//         * 客户端只可以订阅这两个前缀的主题
//         */
//        config.enableSimpleBroker("/topic", "/user");
//        /*
//         * 客户端发送过来的消息，需要以"/app"为前缀，再经过Broker转发给响应的Controller
//         */
//        config.setApplicationDestinationPrefixes("/app");
//    }
//
//    @Override
//    public void registerStompEndpoints(StompEndpointRegistry registry) {
//        /*
//         * 路径"/webSocketEndPoint"被注册为STOMP端点，对外暴露，客户端通过该路径接入WebSocket服务
//         */
//        registry.addEndpoint("/webSocketEndPoint").setAllowedOrigins("*").withSockJS();
//    }


}
