package com.flushbonading.cps.entity.vo;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/12 19:24
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@ApiModel(value = "修改密码表单对象", description = "修改密码表单对象")
public class PasswordVO {
    /**
     * 原始密码
     */
    @ApiModelProperty("原始密码")
    private String originalPassword;

    /**
     * 新密码
     */
    @ApiModelProperty("新密码")
    private String newPassword;

    /**
     * 重复密码
     */
    @ApiModelProperty("重复密码")
    private String repeatPassword;
}
