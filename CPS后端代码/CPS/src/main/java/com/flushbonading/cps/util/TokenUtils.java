package com.flushbonading.cps.util;

import com.auth0.jwt.JWT;
import com.auth0.jwt.algorithms.Algorithm;
import com.flushbonading.cps.entity.vo.UserVO;

/**
 * 生成token工具类
 *
 * @author zyx 2134208960@qq.com
 * @date 2021/6/10 11:32
 * @since 1.0.0
 */
public class TokenUtils {
    private static final long EXPIRE_TIME = 10 * 60 * 60 * 1000;

    /**
     * 得到token
     *
     * @param user
     * @return
     */
    public static String getUserToken(UserVO user) {
        String token = "";
        token = JWT.create().withAudience(user.getStaffNumber())
                .sign(Algorithm.HMAC256(user.getPassword()));
        return token;
    }

    /**
     * 得到用户的工号
     *
     * @param token token
     * @return 返回工号
     */
    public static String getStaffNumber(String token) {
        return JWT.decode(token).getAudience().get(0);
    }
}