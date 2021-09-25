package com.flushbonading.cps.controller;

import com.alibaba.fastjson.JSON;
import com.flushbonading.cps.constant.ResultCode;
import com.flushbonading.cps.constant.Tip;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.vo.UserVO;
import com.flushbonading.cps.mapper.ProductMapper;
import com.flushbonading.cps.service.UserService;
import com.flushbonading.cps.util.TokenUtils;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import javax.servlet.http.HttpServletRequest;
import java.io.IOException;

/**
 * 登录控制器
 *
 * @author zyx 2134208960@qq.com
 * @date 2021/6/10 15:34
 * @since 1.0.0
 */
@RestController
@Api(tags = "登录模块", value = "登录模块")
public class LoginController {
    /**
     * 用户服务对象
     */
    @Autowired
    UserService userService;
    @Autowired
    RedisTemplate<String, Object> redisTemplate;

    @Autowired
    ProductMapper productMapper;

    /**
     * 登录
     *
     * @param request
     * @param userVO
     * @return
     * @throws IOException
     */
    @ApiOperation(value = "登录")
    @PostMapping("/login")
    public String login(HttpServletRequest request, @RequestBody UserVO userVO) throws IOException {
        /*
           构建前端传给后端的对象
         */
        String token = (String) redisTemplate.opsForValue().get("token:" + userVO.getStaffNumber());
        if (token != null) {
            if (token.equals(TokenUtils.getUserToken(userVO))) {
                return JSON.toJSONString(RespBean.success(Tip.LOGIN_SUCCESS.content(), token));
            }
            return JSON.toJSONString(RespBean.error(Tip.PASSWORD_ERROR.content()));
        }
        RespBean login = userService.login(userVO);
        if (login.getCode().intValue() == ResultCode.SUCCESS.status()) {
            login.setData(TokenUtils.getUserToken(userVO));
            redisTemplate.opsForValue().set("token:" + userVO.getStaffNumber(), TokenUtils.getUserToken(userVO));
        }
        return JSON.toJSONString(login);
    }
}
