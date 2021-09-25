package com.flushbonading.cps.entity.dto;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/22 10:43
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "EditPerformanceDTO对象", description = "EditPerformanceDTO")
public class EditPerformanceDTO {

    /**
     * id
     */
    @ApiModelProperty("id")
    private String id;
    /**
     * 工号
     */
    @ApiModelProperty("工号")
    private String staffNumber;

    /**
     * 姓名
     */
    @ApiModelProperty("姓名")
    private String name;

    /**
     * 当月生产总数
     */
    @ApiModelProperty("当月生产总数")
    private String counts;

    /**
     * 上班次数
     */
    @ApiModelProperty("上班次数")
    private String numberOfWork;

    /**
     * 请假次数
     */
    @ApiModelProperty("请假次数")
    private String numberOfLeave;

    /**
     * 缺勤次数
     */
    @ApiModelProperty("缺勤次数")
    private String absenteeism;

    /**
     * 迟到次数
     */
    @ApiModelProperty("迟到次数")
    private String numberOfLate;

    /**
     * 奖惩金额
     */
    @ApiModelProperty("奖惩金额")
    private String rewardsPunishments;

    /**
     * 总工资
     */
    @ApiModelProperty("总工资")
    private String totalWage;

    /**
     * 备注
     */
    @ApiModelProperty("备注")
    private String remark;
}
