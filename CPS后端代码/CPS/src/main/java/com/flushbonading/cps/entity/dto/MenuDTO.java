package com.flushbonading.cps.entity.dto;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/23 10:34
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "MenuDTO对象", description = "MenuDTO")
public class MenuDTO {
    /**
     * 菜单id
     */
    @ApiModelProperty("菜单id")
    private Integer id;

    /**
     * 菜单名
     */
    @ApiModelProperty("菜单名")
    private String label;

    @ApiModelProperty("是否被选中")
    private boolean checked = false;
    /**
     * 子菜单
     */
    @ApiModelProperty("子菜单")
    private List<MenuDTO> children;
}
