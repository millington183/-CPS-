package com.flushbonading.cps.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.cors.CorsConfiguration;
import org.springframework.web.cors.UrlBasedCorsConfigurationSource;
import org.springframework.web.filter.CorsFilter;

/**
 * 跨域配置类
 *
 * @author zyx 2134208960@qq.com
 * @date 2021/5/18 17:02
 * @since 1.0.0
 */
@Configuration
public class WebConfiguration {
    @Bean
    public CorsFilter webConfig() {
        //通过cors配置信息
        CorsConfiguration config = new CorsConfiguration();
        //允许跨域的源
        //config.addAllowedOrigin("http://localhost:8080");
        config.addAllowedOrigin("http://49.234.81.196:1000");
        //允许的信息
        config.setAllowCredentials(true);
        config.addAllowedMethod("*");
        config.addAllowedHeader("*");
        //添加好url映射路径
        UrlBasedCorsConfigurationSource configurationSource = new UrlBasedCorsConfigurationSource();
        configurationSource.registerCorsConfiguration("/**", config);
        return new CorsFilter(configurationSource);
    }
}
