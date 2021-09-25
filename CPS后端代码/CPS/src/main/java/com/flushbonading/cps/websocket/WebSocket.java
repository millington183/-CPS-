package com.flushbonading.cps.websocket;

import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Component;

import javax.websocket.*;
import javax.websocket.server.PathParam;
import javax.websocket.server.ServerEndpoint;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.CopyOnWriteArraySet;

/**
 * @author zyx
 * @version 1.0
 * @description WebSocket客户端
 * @since 2021/06/08 10:07
 */

@ServerEndpoint("/WebSocket/{shopId}")
@Component
@Slf4j
public class WebSocket {

    private Session session;
    private static CopyOnWriteArraySet<WebSocket> webSockets = new CopyOnWriteArraySet<>();
    private static Map<String, Session> sessionPool = new HashMap<>();


    /**
     * 建立连接
     */
    @OnOpen
    public void onOpen(Session session, @PathParam(value = "shopId") String shopId) {
        session.getUserProperties().put("org.apache.tomcat.websocket.BLOCKING_SEND_TIMEOUT", 36000000L);
        this.session = session;
        webSockets.add(this);
        sessionPool.put(shopId, session);
        log.info("【websocket消息】有新的连接，总数为:" + webSockets.size());
        System.out.println("【websocket消息】有新的连接，总数为:" + webSockets.size());
    }

    /**
     * 关闭连接
     */
    @OnClose
    public void onClose() {
        webSockets.remove(this);
        sessionPool.clear();
        log.info("【websocket消息】连接断开，总数为:" + webSockets.size());
        System.out.println("【websocket消息】连接断开，总数为:" + webSockets.size());
    }

    /**
     * 消息到达
     */
    @OnMessage
    public void onMessage(String message) {
        System.out.println("【websocket消息】收到客户端消息:" + message);
    }

    /**
     * 单点发送
     */
    public void sendMessage(String message) {
        for (WebSocket webSocket : webSockets) {
            log.info("【websocket消息】推送消息:" + message);
            System.out.println("【websocket消息】广播消息:" + message);
            try {
                webSocket.session.getBasicRemote().sendText(message);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    @OnError
    public void error(Session session, Throwable t) {
        System.out.println("发生错误，请注意");
        t.printStackTrace();
    }


}