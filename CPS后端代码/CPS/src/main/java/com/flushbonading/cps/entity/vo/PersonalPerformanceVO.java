package com.flushbonading.cps.entity.vo;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/22 12:55
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@ApiModel(value = "PersonalPerformanceVO对象", description = "PersonalPerformanceVO对象")
public class PersonalPerformanceVO {

    /**
     * 时间
     */
    @ApiModelProperty("时间")
    private String createTime;
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
