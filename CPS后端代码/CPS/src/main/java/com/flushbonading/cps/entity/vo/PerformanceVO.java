package com.flushbonading.cps.entity.vo;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/21 19:37
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@ApiModel(value = "PerformanceVO对象", description = "PerformanceVO对象")
public class PerformanceVO {

    @ApiModelProperty("id")
    private String id;
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
     * 姓名
     */
    @ApiModelProperty("姓名")
    private String name;

    /**
     * 基础工资
     */
    @ApiModelProperty("基础工资")
    private String baseWage;

    /**
     * 生产总数
     */
    @ApiModelProperty("生产总数")
    private Long counts;

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

}
