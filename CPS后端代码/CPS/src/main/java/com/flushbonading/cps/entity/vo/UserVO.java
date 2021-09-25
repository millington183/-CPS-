package com.flushbonading.cps.entity.vo;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/10 14:38
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "登录页交互对象", description = "登录页交互对象")
public class UserVO {
    /**
     * 工号
     */
    @ApiModelProperty(value = "工号")
    private String staffNumber;

    /**
     * 密码
     */
    @ApiModelProperty(value = "密码")
    private String password;
}
