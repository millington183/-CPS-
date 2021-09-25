package com.flushbonading.cps.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 *
 * </p>
 *
 * @author zyx
 * @since 2021-06-12
 */
@Data
@EqualsAndHashCode(callSuper = false)
@TableName("t_staff")
public class Staff implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 员工id
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Integer id;

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
    private Integer departmentId;

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
    private Integer postId;

    /**
     * 更新时间
     */
    @ApiModelProperty("更新时间")
    private LocalDateTime updateTime;

    /**
     * 创建时间
     */
    @ApiModelProperty("创建时间")
    private LocalDateTime createTime;


}
