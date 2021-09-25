package com.flushbonading.cps.entity.dto;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/21 16:21
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "AddPerformanceDTO对象", description = "AddPerformanceDTO")
public class AddPerformanceDTO {
    /**
     * 创建时间
     */
    @ApiModelProperty("创建时间")
    private String createTime;

    /**
     * 工号
     */
    @ApiModelProperty("工号")
    private String staffNumber;

    /**
     * 请假次数
     */
    @ApiModelProperty("请假次数")
    private String numberOfLeave;

    /**
     * 迟到次数
     */
    @ApiModelProperty("迟到次数")
    private String NumberOfLate;

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
     * 备注
     */
    @ApiModelProperty("备注")
    private String remark;
}
