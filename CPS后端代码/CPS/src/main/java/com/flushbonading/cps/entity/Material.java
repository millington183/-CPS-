package com.flushbonading.cps.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.*;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 *
 * </p>
 *
 * @author zyx
 * @since 2021-06-17
 */
@Data
@EqualsAndHashCode(callSuper = false)
@Builder
@AllArgsConstructor
@NoArgsConstructor
@TableName("t_material")
@ApiModel(value = "Material对象", description = "Material对象")
public class Material implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * id号
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Integer id;

    /**
     * 物料牌号
     */
    @ApiModelProperty("物料牌号")
    private String materialId;

    /**
     * 铝的比例
     */
    @ApiModelProperty("铝的比例")
    private Double al;

    /**
     * 铁的比例
     */
    @ApiModelProperty("铁的比例")
    private Double fe;

    /**
     * 硼的比例
     */
    @ApiModelProperty("硼的比例")
    private Double b;

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
