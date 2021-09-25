package com.flushbonading.cps;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.scheduling.annotation.EnableScheduling;

@SpringBootApplication
@EnableScheduling
@MapperScan("com.flushbonading.cps.mapper")
public class CpsApplication {

    public static void main(String[] args) {
        SpringApplication.run(CpsApplication.class, args);
    }
}
