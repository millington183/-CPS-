package com.flushbonading.cps.util;

import cn.hutool.extra.qrcode.QrCodeUtil;

import java.awt.image.BufferedImage;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/5 16:56
 * @since 1.0.0
 */
public class QRCodeUtil {
    public static BufferedImage create(String message) {
        BufferedImage image = QrCodeUtil.generate(message, 300, 300);
        return image;
    }
}
