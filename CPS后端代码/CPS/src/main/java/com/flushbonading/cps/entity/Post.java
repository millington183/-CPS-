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
 * @since 2021-06-13
 */
@Data
@EqualsAndHashCode(callSuper = false)
@Builder
@AllArgsConstructor
@NoArgsConstructor
@TableName("t_post")
@ApiModel(value = "Post对象", description = "Post对象")
public class Post implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 职务id号
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Integer id;

    /**
     * 职务名
     */
    @ApiModelProperty("职务名")
    private String postName;

    /**
     * 基础工资
     */
    @ApiModelProperty("基础工资")
    private Integer baseWage;

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
