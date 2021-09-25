package com.flushbonading.cps.entity;

import com.baomidou.mybatisplus.annotation.IdType;
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
 * @since 2021-06-21
 */
@Data
@EqualsAndHashCode(callSuper = false)
@TableName("t_staff_device")
public class StaffDevice implements Serializable {

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
     * 包装人员工号
     */
    @ApiModelProperty("包装人员工号")
    private String packagingWorker;

    /**
     * 压型人员工号
     */
    @ApiModelProperty("压型人员工号")
    private String producer;

    /**
     * 制作的总数
     */
    @ApiModelProperty("制作的总数")
    private Long counts;

    /**
     * 工作时长
     */
    @ApiModelProperty("工作时长")
    private LocalDateTime workTime;

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
