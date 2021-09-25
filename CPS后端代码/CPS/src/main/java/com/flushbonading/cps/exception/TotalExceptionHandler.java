package com.flushbonading.cps.exception;

import cn.hutool.core.exceptions.ValidateException;
import com.alibaba.fastjson.JSON;
import com.flushbonading.cps.entity.RespBean;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.ResponseBody;

/**
 * 全局异常处理器
 *
 * @author zyx 2134208960@qq.com
 * @date 2021/6/10 14:53
 * @since 1.0.0
 */
@ControllerAdvice

public class TotalExceptionHandler {
    /**
     * 捕获校验出错
     *
     * @param ve
     * @return
     */
    @ExceptionHandler(ValidateException.class)
    @ResponseBody
    public String validateException(ValidateException ve) {
        return JSON.toJSONString(RespBean.verifyError(ve.getMessage()));
    }
    
}
