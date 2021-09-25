package com.flushbonading.cps.entity.dto;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/19 16:10
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "EquipmentDTO对象", description = "EquipmentDTO")
public class EquipmentDTO {
    /**
     * 设备号id
     */
    @ApiModelProperty(value = "设备号id")
    private String equipmentId;
    /**
     * 保养时间
     */
    @ApiModelProperty(value = "保养时间")
    private String maintenancePeriod;
}
