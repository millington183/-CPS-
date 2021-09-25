package com.flushbonading.cps.entity.dto;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/15 11:14
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "EquipmentSearchDTO对象", description = "EquipmentSearchDTO")
public class EquipmentSearchDTO {
    /**
     * 设备号id
     */
    @ApiModelProperty("设备号id")
    private String equipmentId;

    /**
     * 创建时间
     */
    @ApiModelProperty("创建时间")
    private String createTime;
}
