package com.flushbonading.cps.entity;


import com.flushbonading.cps.constant.ResultCode;
import lombok.Getter;
import lombok.Setter;

/**
 * 响应的统一返回结果对象
 *
 * @author zyx 2134208960@qq.com
 * @date 2021/5/31 9:42
 * @since 1.0.0
 */
@Getter
@Setter
public class RespBean {
    /**
     * 序列号
     */
    private static final long serialVersionUID = 1L;
    /**
     * 响应的后端状态码
     */
    private Integer code;
    /**
     * 响应的结果
     */
    private String message;
    /**
     * 携带回来的数据
     */
    private Object data;

    /**
     * 设置为私有类型，为了不能通过外部进行调用
     *
     * @param code    状态码
     * @param message 向前端传递的消息
     * @param data    向前端传递的数据
     */
    private RespBean(Integer code, String message, Object data) {
        this.code = code;
        this.message = message;
        this.data = data;
    }

    /**
     * 成功调用的方法(不设置传输的数据)
     *
     * @param message 传給前端的消息
     * @return 返回RespBean对象
     */
    public static RespBean success(String message) {
        return new RespBean(ResultCode.SUCCESS.status(), message, null);
    }

    /**
     * 成功调用的方法(设置传输的数据)
     *
     * @param message 传給前端的消息
     * @return 返回RespBean对象
     */
    public static RespBean success(String message, Object data) {
        return new RespBean(ResultCode.SUCCESS.status(), message, data);
    }

    /**
     * 失败调用的方法(不设置传输的数据)
     *
     * @param message 传输给前端的信息
     * @return 返回RespBean对象
     */
    public static RespBean error(String message) {
        return new RespBean(ResultCode.ERROR.status(), message, null);
    }

    /**
     * 失败调用的方法(设置传输的数据)
     *
     * @param message 传输给前端的信息
     * @return 返回RespBean对象
     */
    public static RespBean error(String message, Object data) {
        return new RespBean(ResultCode.ERROR.status(), message, null);
    }

    /**
     * 校验错误
     *
     * @return 返回响应封装对象
     */
    public static RespBean verifyError(String message) {
        return new RespBean(ResultCode.FORBIDDEN.status(), message, null);
    }
}
