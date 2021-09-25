package com.flushbonading.cps.entity.vo;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author peiwen 2586966585@qq.com
 * @date 2021/6/11 16:22
 * @since 1.0.0
 */

@Data
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "RoleVO对象", description = "用来传输前后端交互数据")
public class RoleVO {
    /**
     * 角色id
     */
    @ApiModelProperty(value = "角色id")
    private Integer roleId;
    /**
     * 角色名
     */
    @ApiModelProperty("角色名")
    private String roleName;

}