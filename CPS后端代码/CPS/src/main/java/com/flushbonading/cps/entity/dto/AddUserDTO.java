package com.flushbonading.cps.entity.dto;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/15 17:02
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "AddUserDTO对象", description = "DepartmentDTO")
public class AddUserDTO {
    /**
     * 员工工号
     */
    @ApiModelProperty("员工工号")
    private String staffNumber;

    /**
     * 员工名
     */
    @ApiModelProperty("员工名")
    private String name;

    /**
     * 角色名
     */
    @ApiModelProperty("角色名")
    private String roleName;
}
