package com.flushbonading.cps.constant;

/**
 * 给用户的提示信息
 *
 * @author zyx 2134208960@qq.com
 * @date 2021/6/10 19:56
 * @since 1.0.0
 */
public enum Tip {
    /**
     * 输入错误信息
     */
    ERROR_INPUT("输入不符合要求!"),
    /**
     * 不存在该用户
     */
    USER_NOT_EXIST("不存在该用户!"),
    /**
     * 密码不正确
     */
    PASSWORD_ERROR("密码不正确!"),
    /**
     * 登录成功
     */
    LOGIN_SUCCESS("登录成功"),
    /**
     * 初始密码与原密码不符合!
     */
    ORIGINAL_PASSWORD_ERROR("初始密码与原密码不符合!"),
    /**
     * 两次密码输入不相符
     */
    EQUAL_ERROR("两次密码输入不相符!"),
    /**
     * 修改成功
     */
    EDIT_SUCCESS("修改成功"),
    /**
     * 修改失败
     */
    EDIT_ERROR("修改失败！"),
    /**
     * WebSocket连接超时
     */
    WEBSOCKET_TIMEOUT("WebSocket连接超时"),
    /**
     * 该员工不存在
     */
    STAFF_ERROR("该员工不存在!"),
    /**
     * 删除失败
     */
    DELETE_ERROE("删除失败！"),
    /**
     * 删除成功
     */
    DELETE_SUCCESS("删除成功"),
    /**
     * 用户已存在
     */
    USER_EXIST("用户已存在!"),
    /**
     * 员工已经存在
     */
    STAFF_EXIST("该员工已存在!"),
    /**
     * 绩效已存在！
     */
    STAFF_DEVICE_NOT_EXIST("改时间此员工没有上班"),
    PERFORMANCE_EXIT("绩效已存在！"),
    /**
     * id号已存在
     */
    ID_EXIST("id号已存在"),
    /**
     * 该角色名已存在!
     */
    ROLE_NAME_EXIST("该角色名已存在!"),
    /**
     * 该设备不存在！
     */
    EQUIPMENT_NOT_EXIST("该设备不存在！"),
    /**
     * 该物料已经存在
     */
    MATERIAL_EXIST("该物料已经存在"),
    /**
     * 该员工不存在或工号和姓名不匹配!
     */
    ADD_USER_ERROR("该员工不存在或工号和姓名不匹配!"),

    /**
     * 增加失败
     */
    INSERT_ERROR("增加失败!"),

    /**
     * 增加成功
     */
    INSERT_SUCCESS("增加成功"),
    /**
     * 部门和职务不匹配！
     */
    MATCH_UP_ERROR("部门和职务不匹配！"),
    /**
     * 有用户属于该角色，请先修改用户角色
     */
    BELONG_TO_ROLE("有用户属于该角色，请先修改用户角色"),
    /**
     * 数据发送成功
     */
    POST_SUCCESS("数据发送成功");


    /**
     * 内容
     */
    private String content;


    Tip(String content) {
        this.content = content;
    }

    /**
     * 拿到信息
     *
     * @return 信息的内容
     */
    public String content() {
        return this.content;
    }
}
