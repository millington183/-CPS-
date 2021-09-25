package com.flushbonading.cps.entity.vo;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/7/8 14:44
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "EnvironmentVO对象", description = "EnvironmentVO")
public class EnvironmentVO {
    /**
     * 温度
     */
    @ApiModelProperty(value = "温度")
    private String temperature;

    /**
     * 湿度
     */
    @ApiModelProperty(value = "湿度")
    private String humidity;

    /**
     * 粉尘浓度
     */
    @ApiModelProperty(value = "粉尘浓度")
    private String dust;
}
