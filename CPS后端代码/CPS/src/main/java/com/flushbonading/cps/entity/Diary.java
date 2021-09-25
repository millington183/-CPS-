package com.flushbonading.cps.entity;

import com.baomidou.mybatisplus.annotation.TableName;
import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import java.time.LocalDateTime;
import java.io.Serializable;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Builder;
import lombok.Data;
import lombok.EqualsAndHashCode;

/**
 * <p>
 * 每日每时段生产总数实体类
 * </p>
 *
 * @author zyx
 * @since 2021-06-09
 */
@Data
@EqualsAndHashCode(callSuper = false)
@Builder
@TableName("t_diary")
@ApiModel(value="Diary对象", description="")
public class Diary implements Serializable {
    /**
     * 序列号
     */
    private static final long serialVersionUID=1L;

    /**
     * id号
     */
    @ApiModelProperty(value = "id号")
    @TableId(value = "id", type = IdType.AUTO)
    private Integer id;

    /**
     * 设备号
     */
    @ApiModelProperty(value = "设备号id")
    private Integer equipmentId;

    /**
     * 时间段
     */
    @ApiModelProperty(value = "时间段id")
    private Integer timeId;

    /**
     * 生产数量
     */
    @ApiModelProperty(value = "生产数量")
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
