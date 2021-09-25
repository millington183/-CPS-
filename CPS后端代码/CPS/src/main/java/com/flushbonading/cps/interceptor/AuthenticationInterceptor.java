package com.flushbonading.cps.interceptor;

import org.springframework.web.servlet.HandlerInterceptor;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/11 11:31
 * @since 1.0.0
 */
public class AuthenticationInterceptor implements HandlerInterceptor {
    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        //不访问后台管理接口直接通过
        if (!request.getRequestURI().contains("api")) {
            return true;
        } else {
            String token = request.getHeader("token");
            if (token != null && token.length() > 0) {
                return true;
            }
        }
        System.out.println("请求被拦截下来了......");
        return false;
    }
}
