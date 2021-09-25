package com.flushbonading.cps.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 产品实体类
 * </p>
 *
 * @author zyx
 * @since 2021-06-09
 */
@Data
@EqualsAndHashCode(callSuper = false)
@TableName("t_product")
@ApiModel(value = "Product对象", description = "")
public class Product implements Serializable {
    /**
     * 序列号
     */
    private static final long serialVersionUID = 1L;
    /**
     * id号
     */
    @ApiModelProperty(value = "id号")
    @TableId(value = "id", type = IdType.AUTO)
    private Long id;

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
    private Integer equipmentId;

    /**
     * 模型号
     */
    @ApiModelProperty(value = "模型号")
    private String modelNumber;

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

    /**
     * 重量
     */
    @ApiModelProperty(value = "重量")
    private Double weight;

    /**
     * 尺寸
     */
    @ApiModelProperty(value = "尺寸")
    private Double size;

    /**
     * 称粉计时
     */
    @ApiModelProperty(value = "称粉计时")
    private Integer saidPowderTime;

    /**
     * 结果
     */
    @ApiModelProperty(value = "结果")
    private Integer result;

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

    /**
     * 更新时间
     */
    @ApiModelProperty(value = "更新时间")
    private LocalDateTime updateTime;

    /**
     * 创建时间
     */
    @ApiModelProperty(value = "创建时间")
    private LocalDateTime createTime;


}
