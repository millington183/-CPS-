package com.flushbonading.cps.util;

import cn.hutool.core.codec.Base64;
import cn.hutool.core.util.RandomUtil;
import cn.hutool.crypto.digest.HMac;
import cn.hutool.crypto.digest.HmacAlgorithm;

import java.util.ArrayList;
import java.util.List;

/**
 * 密码工具
 *
 * @author zyx 2134208960@qq.com
 * @date 2021/6/11 8:08
 * @since 1.0.0
 */
public class PasswordUtil {
    /**
     * 密码校验工具
     *
     * @param userInput        用户输入的密码
     * @param dataBasePassword 数据库中的密码
     * @param salt             盐值
     * @return
     */
    public static boolean verifyPassword(String userInput, String dataBasePassword, String salt) {
        //32位HMAC密码
        byte[] key = salt.getBytes();
        HMac mac = new HMac(HmacAlgorithm.HmacMD5, key);
        String secretPassword = Base64.encode(mac.digestHex(userInput));
        if (secretPassword.equals(dataBasePassword)) {
            return true;
        }
        return false;
    }

    /**
     * 初始化密码
     *
     * @param password 初始的密码
     * @return 返回一个list, 第一个是密码，第二个是盐值
     */
    public static List<String> initPassword(String password) {
        //生成六位随机字符
        byte[] key = RandomUtil.randomString(6).getBytes();
        //根据密码进行加密
        HMac mac = new HMac(HmacAlgorithm.HmacMD5, key);
        String secretPassword = Base64.encode(mac.digestHex(password));

        //构建List
        List<String> list = new ArrayList<>();
        list.add(secretPassword);
        list.add(new String(key));
        return list;
    }

    public static void main(String[] args) {
        List<String> list = initPassword("123456");
        System.out.println(list.get(0));
        System.out.println(list.get(1));
    }
}
