package com.flushbonading.cps.entity.dto;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/21 19:52
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "SearchPerformanceDTO对象", description = "SearchPerformanceDTO")
public class SearchPerformanceDTO {

    /**
     * 姓名
     */
    @ApiModelProperty("姓名")
    private String name;

    /**
     * 学号
     */
    @ApiModelProperty("学号")
    private String staffNumber;

    /**
     * 时间
     */
    @ApiModelProperty("时间")
    private String createTime;
}
