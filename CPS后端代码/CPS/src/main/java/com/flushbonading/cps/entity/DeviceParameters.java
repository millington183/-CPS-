package com.flushbonading.cps.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 *
 * </p>
 *
 * @author zyx
 * @since 2021-06-15
 */
@Data
@EqualsAndHashCode(callSuper = false)
@TableName("t_device_parameters")
public class DeviceParameters implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * id号
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Integer id;

    /**
     * 设备号id
     */
    @ApiModelProperty("设备号id")
    private Integer equipmentId;

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

    /**
     * 是否取消绑定
     */
    @TableField("Not_bind")
    private Integer notBind;

    /**
     * 更新时间
     */
    @ApiModelProperty("更新时间")
    private LocalDateTime updateTime;

    /**
     * 创建时间
     */
    @ApiModelProperty("创建时间")
    private LocalDateTime createTime;


}
