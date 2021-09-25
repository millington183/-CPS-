package com.flushbonading.cps.entity.vo;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/14 11:29
 * @since 1.0.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@Builder
@ApiModel(value = "StaffVO对象", description = "用来传输前后端交互数据")
public class StaffVO {
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
     * 部门
     */
    @ApiModelProperty("部门")
    private String departmentName;

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
     * 职务
     */
    @ApiModelProperty("职务")
    private String postName;

    /**
     * 职务号
     */
    @ApiModelProperty("部门号")
    private String departmentId;

    /**
     * 职务号
     */
    @ApiModelProperty("职务号")
    private String postId;

    /**
     * 二维码地址
     */
    @ApiModelProperty("二维码地址")
    private String url;
}
