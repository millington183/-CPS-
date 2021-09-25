package com.flushbonading.cps.entity.dto;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/25 17:10
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "DeviceParametersDTO对象", description = "DeviceParametersDTO")
public class DeviceParametersDTO {
    /**
     * 设备号id
     */
    @ApiModelProperty("设备号id")
    private String equipmentId;

    /**
     * 压制压力
     */
    @ApiModelProperty("压制压力")
    private String pressingPressure;

    /**
     * 保压压力
     */
    @ApiModelProperty("保压压力")
    private String dwellPressure;

    /**
     * 退磁电流
     */
    @ApiModelProperty("退磁电流")
    private String currentDemagnetization;

    /**
     * 充磁电流
     */
    @ApiModelProperty("充磁电流")
    private String currentMagnetization;
}
