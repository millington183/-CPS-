package com.flushbonading.cps.config;


import com.flushbonading.cps.interceptor.AuthenticationInterceptor;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.InterceptorRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

/**
 * 静态资源放行
 *
 * @author zyx 2134208960@qq.com
 * @version 0.1.0
 * @create 2021-03-16 11:18
 * @since 0.1.0
 **/
@Configuration
public class InterceptorConfig implements WebMvcConfigurer {
    @Override
    public void addInterceptors(InterceptorRegistry registry) {
        /*
            放行必要的资源
         */
        registry.addInterceptor(authenticationInterceptor())
                .addPathPatterns("/**")
                .excludePathPatterns("/main", "/", "/js/**", "/callback", "/css/**", "/favicon.ico"
                        , "/swagger-ui.html/**", "/swagger/**", "/swagger-resources/**"
                        , "/v2/**", "/webjars/**", "/configuration", "/doc.html/**");
    }
    
    @Bean
    public AuthenticationInterceptor authenticationInterceptor() {
        return new AuthenticationInterceptor();
    }
}
