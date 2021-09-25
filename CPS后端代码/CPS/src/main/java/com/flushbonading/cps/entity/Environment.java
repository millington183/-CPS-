package com.flushbonading.cps.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Builder;
import lombok.Data;
import lombok.EqualsAndHashCode;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 生产环境实体类
 * </p>
 *
 * @author zyx
 * @since 2021-06-09
 */
@Data
@Builder
@EqualsAndHashCode(callSuper = false)
@TableName("t_environment")
@ApiModel(value = "Environment对象", description = "")
public class Environment implements Serializable {
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
     * 温度
     */
    @ApiModelProperty(value = "温度")
    private Double temperature;

    /**
     * 湿度
     */
    @ApiModelProperty(value = "湿度")
    private Double humidity;

    /**
     * 粉尘浓度
     */
    @ApiModelProperty(value = "粉尘浓度")
    private Double dust;

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
