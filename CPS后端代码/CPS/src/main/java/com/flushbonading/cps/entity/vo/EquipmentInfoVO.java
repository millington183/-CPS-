package com.flushbonading.cps.entity.vo;

import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author peiwen 2586966585@qq.com
 * @date 2021/6/22 17:24
 * @since 1.0.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class EquipmentInfoVO {
    /**
     * 设备id
     */
    @ApiModelProperty(value = "设备id")
    private Integer equipmentId;
    /**
     * 设备名
     */
    @ApiModelProperty(value = "设备名")
    private String equipmentName;
    /**
     * 包装人员姓名
     */
    @ApiModelProperty(value = "包装人员姓名")
    private String packagingWorkerName;
    /**
     * 压型人员姓名
     */
    @ApiModelProperty(value = "压型人员姓名")
    private String producerName;
    /**
     * 保养时间
     */
    @ApiModelProperty(value = "保养时间")
    private String maintenancePeriod;
    /**
     * 压制压力
     */
    @ApiModelProperty(value = "压制压力")
    private Double pressingPressure;
    /**
     * 保压压力
     */
    @ApiModelProperty(value = "保压压力")
    private Double dwellPressure;
    /**
     * 退磁电流
     */
    @ApiModelProperty(value = "退磁电流")
    private Double currentDemagnetization;
    /**
     * 充磁电流
     */
    @ApiModelProperty(value = "充磁电流")
    private Double currentMagnetization;
}