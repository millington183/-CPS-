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
 * 设备实体类
 * </p>
 *
 * @author zyx
 * @since 2021-06-09
 */
@Data
@EqualsAndHashCode(callSuper = false)
@TableName("t_equipment")
@ApiModel(value = "Equipment对象", description = "")
public class Equipment implements Serializable {

    /**
     * 序列号
     */
    private static final long serialVersionUID = 1L;

    /**
     * id号
     */
    @ApiModelProperty(value = "id号")
    @TableId(value = "id", type = IdType.AUTO)
    private Integer id;

    /**
     * 设备号id
     */
    @ApiModelProperty(value = "设备号id")
    private Integer equipmentId;

    /**
     * 设备名
     */
    @ApiModelProperty(value = "设备名")
    private String equipmentName;

    /**
     * 包装人员工号
     */
    @ApiModelProperty(value = "包装人员工号")
    private String packagingWorker;

    /**
     * 压型人员工号
     */
    @ApiModelProperty(value = "压型人员工号")
    private String producer;

    /**
     * 保养时间
     */
    @ApiModelProperty(value = "保养时间")
    private LocalDateTime maintenancePeriod;

    /**
     * 制作个数
     */
    @ApiModelProperty(value = "制作个数")
    private Long counts;
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
