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
 * @since 2021-06-21
 */
@Data
@EqualsAndHashCode(callSuper = false)
@TableName("t_performance")
public class Performance implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 绩效id
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Integer id;

    /**
     * 工号
     */
    @ApiModelProperty("工号")
    private String staffNumber;

    /**
     * 当月生产总数
     */
    @ApiModelProperty("当月生产总数")
    private Long counts;

    /**
     * 上班次数
     */
    @ApiModelProperty("上班次数")
    private Integer numberOfWork;

    /**
     * 请假次数
     */
    @ApiModelProperty("请假次数")
    private Integer numberOfLeave;

    /**
     * 缺勤次数
     */
    @ApiModelProperty("缺勤次数")
    private Integer absenteeism;

    /**
     * 迟到次数
     */
    @ApiModelProperty("迟到次数")
    private Integer numberOfLate;

    /**
     * 奖惩金额
     */
    @ApiModelProperty("奖惩金额")
    private Integer rewardsPunishments;

    /**
     * 总工资
     */
    @ApiModelProperty("总工资")
    private Integer totalWage;

    /**
     * 备注
     */
    @ApiModelProperty("备注")
    private String remark;

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
