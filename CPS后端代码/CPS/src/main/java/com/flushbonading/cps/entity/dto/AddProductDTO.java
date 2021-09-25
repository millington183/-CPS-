package com.flushbonading.cps.entity.dto;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/25 15:18
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "AddProductDTO对象", description = "AddProductDTO")
public class AddProductDTO {
    /**
     * 产品编号
     */
    @ApiModelProperty("产品编号")
    private String productNumber;
    /**
     * 物料牌号
     */
    @ApiModelProperty(value = "物料牌号")
    private String materialId;

    /**
     * 设备id
     */
    @ApiModelProperty(value = "设备id")
    private String equipmentId;

    /**
     * 模型号
     */
    @ApiModelProperty(value = "模型号")
    private String modelNumber;

    /**
     * 压制压力
     */
    @ApiModelProperty(value = "压制压力")
    private String pressingPressure;

    /**
     * 保压压力
     */
    @ApiModelProperty(value = "保压压力")
    private String dwellPressure;

    /**
     * 退磁电流
     */
    @ApiModelProperty(value = "退磁电流")
    private String currentDemagnetization;

    /**
     * 充磁电流
     */
    @ApiModelProperty(value = "充磁电流")
    private String currentMagnetization;

    /**
     * 重量
     */
    @ApiModelProperty(value = "重量")
    private String weight;

    /**
     * 尺寸
     */
    @ApiModelProperty(value = "尺寸")
    private String size;

    /**
     * 称粉计时
     */
    @ApiModelProperty(value = "称粉计时")
    private String saidPowderTime;

    /**
     * 结果
     */
    @ApiModelProperty(value = "结果")
    private String result;

    /**
     * 包装人员
     */
    @ApiModelProperty(value = "包装人员")
    private String packagingWorker;

    /**
     * 压型人员
     */
    @ApiModelProperty(value = "压型人员")
    private String producer;
}
