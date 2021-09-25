package com.flushbonading.cps.controller;

import com.flushbonading.cps.util.QRCodeUtil;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.imageio.ImageIO;
import javax.servlet.http.HttpServletResponse;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.io.OutputStream;

/**
 * 二维码生成工具
 *
 * @author zyx 2134208960@qq.com
 * @date 2021/6/12 19:55
 * @since 1.0.0
 */
@RestController
@RequestMapping("/main/QRcode")
@Api(tags = "二维码模块", value = "二维码模块")
public class QRcodeController {
    @ApiOperation("显示二维码")
    @GetMapping("/getQRcode/{message}")
    public void getQRcode(@PathVariable("message") String message, HttpServletResponse response) {
        // 设置响应流信息
        response.setContentType("image/jpg");
        response.setHeader("Pragma", "no-cache");
        response.setHeader("Cache-Control", "no-cache");
        response.setDateHeader("Expires", 0);

        OutputStream stream = null;
        try {
            stream = response.getOutputStream();
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }

        //获取一个二维码图片
        BufferedImage bi = QRCodeUtil.create(message);

        //以流的形式输出到前端
        try {
            ImageIO.write(bi, "jpg", stream);
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }
}
