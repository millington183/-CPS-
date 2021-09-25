package com.flushbonading.cps.entity.vo;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/7/12 10:29
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "EquipmentDataVO", description = "EquipmentDataVO")
public class EquipmentDataVO {
    /**
     * 压制压力
     */
    @ApiModelProperty("压制压力")
    private Double pressingPressure;

    /**
     * 保压压力
     */
    @ApiModelProperty("保压压力")
    private Double dwellPressure;

    /**
     * 退磁电流
     */
    @ApiModelProperty("退磁电流")
    private Double currentDemagnetization;

    /**
     * 充磁电流
     */
    @ApiModelProperty("充磁电流")
    private Double currentMagnetization;
}
