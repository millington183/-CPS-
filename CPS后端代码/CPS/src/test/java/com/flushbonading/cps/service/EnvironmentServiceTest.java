package com.flushbonading.cps.service;

import com.flushbonading.cps.entity.dto.EnvironmentDTO;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/9 10:18
 * @since 1.0.0
 */
@SpringBootTest
public class EnvironmentServiceTest {
    @Autowired
    EnvironmentService environmentService;

    @Test
    public void testQueryEnvironmentMessage() {
        EnvironmentDTO environmentDTO = environmentService.queryEnvironmentMessage();
        System.out.println(environmentDTO);
    }

}
