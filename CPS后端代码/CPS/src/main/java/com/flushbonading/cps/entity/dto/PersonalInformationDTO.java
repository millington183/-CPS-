package com.flushbonading.cps.entity.dto;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/13 15:37
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "PersonalInformationDTO对象", description = "PersonalInformationDTO")
public class PersonalInformationDTO {
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
     * 职务id
     */
    @ApiModelProperty("年龄")
    private Integer age;
}
