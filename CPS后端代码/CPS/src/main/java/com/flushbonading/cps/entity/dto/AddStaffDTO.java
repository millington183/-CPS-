package com.flushbonading.cps.entity.dto;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/17 8:54
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "AddStaffDTO对象", description = "AddStaffDTO")
public class AddStaffDTO {
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
     * 性别
     */
    @ApiModelProperty("性别")
    private String gender;

    /**
     * 部门id
     */
    @ApiModelProperty("部门id")
    private String departmentId;

    /**
     * 身份证号
     */
    @ApiModelProperty("身份证号")
    private String idCard;

    /**
     * 手机
     */
    @ApiModelProperty("手机")
    private String phone;

    /**
     * 职务id
     */
    @ApiModelProperty("职务id")
    private String postId;
}
