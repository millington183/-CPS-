package com.flushbonading.cps.entity.dto;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * 部门实体
 *
 * @author zyx 2134208960@qq.com
 * @date 2021/6/14 9:35
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "DepartmentDTO对象", description = "DepartmentDTO")
public class DepartmentDTO {
    /**
     * 部门id号
     */
    @ApiModelProperty("id号")
    private Integer id;

    /**
     * 部门名
     */
    @ApiModelProperty("部门名")
    private String departmentName;
}
