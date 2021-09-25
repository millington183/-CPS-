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
 * DepartmentPost对象
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
@TableName("t_department_post")
@ApiModel(value = "DepartmentPost", description = "DepartmentPost")
public class DepartmentPost implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 部门职务id
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Integer id;

    /**
     * 部门id
     */
    @ApiModelProperty("部门id")
    private Integer departmentId;

    /**
     * 职务id
     */
    @ApiModelProperty("职务id")
    private Integer postId;

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
