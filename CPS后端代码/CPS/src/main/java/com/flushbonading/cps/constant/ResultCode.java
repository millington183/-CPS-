package com.flushbonading.cps.constant;

/**
 * 这里申明一些状态码信息
 *
 * @author zyx 2134208960@qq.com
 * @date 2021/5/31 11:33
 * @since 1.0.0
 */
public enum ResultCode {
    /**
     * 声明响应成功信息
     */
    SUCCESS(200, "成功"),
    /**
     * 服务器端代码出错
     */
    ERROR(500, "服务器错误"),
    /**
     * 请求资源路径出错
     */
    NOT_FOUND(404, "找不到资源"),
    /**
     * 拒绝请求，一般是跨域问题,或不允许访问
     */
    FORBIDDEN(403, "验证不通过!");

    /**
     * 响应状态码
     */
    private Integer status;
    /**
     * 响应信息
     */
    private String msg;

    ResultCode(Integer status, String msg) {
        this.status = status;
        this.msg = msg;
    }

    /**
     * 获取响应状态码的方法
     *
     * @return
     */
    public Integer status() {
        return this.status;
    }

    public String message() {
        return this.msg;
    }
    

}
