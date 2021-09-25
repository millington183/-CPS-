package com.flushbonading.cps.entity.dto;


import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * 环境服务对象
 *
 * @author zyx 2134208960@qq.com
 * @date 2021/6/9 9:43
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "EnvironmentDTO对象", description = "环境信息对象")
public class EnvironmentDTO {
    /**
     * 温度
     */
    @ApiModelProperty(value = "温度")
    private Double temperature;

    /**
     * 湿度
     */
    @ApiModelProperty(value = "湿度")
    private Double humidity;

    /**
     * 粉尘浓度
     */
    @ApiModelProperty(value = "粉尘浓度")
    private Double dust;
}
