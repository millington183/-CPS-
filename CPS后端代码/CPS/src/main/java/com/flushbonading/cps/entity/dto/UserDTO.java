package com.flushbonading.cps.entity.dto;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/10 20:07
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "用户业务对象", description = "用户业务对象")
public class UserDTO {
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

    /**
     * 盐值
     */
    @ApiModelProperty(value = "盐值")
    private String salt;
}
