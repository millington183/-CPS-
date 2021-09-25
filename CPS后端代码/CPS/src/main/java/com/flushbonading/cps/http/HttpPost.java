package com.flushbonading.cps.http;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;
import org.springframework.web.client.RestTemplate;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/26 8:49
 * @since 1.0.0
 */
public class HttpPost {
    @Autowired
    RestTemplate template;

    public String post() {
        String url = "http://127.0.0.1:8086/main/test";
        // 封装参数，千万不要替换为Map与HashMap，否则参数无法传递
        MultiValueMap<String, Object> paramMap = new LinkedMultiValueMap<String, Object>();

        // 1、使用postForObject请求接口
        String result = template.postForObject(url, paramMap, String.class);
        System.out.println("result1==================" + result);
        return result;
    }
}
