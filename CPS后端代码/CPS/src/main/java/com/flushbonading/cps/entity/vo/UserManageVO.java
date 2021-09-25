package com.flushbonading.cps.entity.vo;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/13 21:10
 * @since 1.0.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "UserManageVO对象", description = "用来显示用户管理界面")
public class UserManageVO {
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

    /**
     * 部门
     */
    @ApiModelProperty("部门")
    private String departmentName;

    /**
     * 职务
     */
    @ApiModelProperty("职务")
    private String postName;

}
