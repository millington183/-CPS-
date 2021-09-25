package com.flushbonading.cps.entity.vo;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

/**
 * 菜单渲染对象
 *
 * @author zyx 2134208960@qq.com
 * @date 2021/6/11 16:14
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "菜单渲染对象", description = "菜单渲染对象")
public class MenuVO {
    /**
     * 菜单id
     */
    @ApiModelProperty("菜单id")
    private Integer menuId;

    /**
     * 菜单名
     */
    @ApiModelProperty("菜单名")
    private String menuName;

    /**
     * 菜单icon
     */
    @ApiModelProperty("菜单icon")
    private String icon;

    /**
     * 跳转的路径
     */
    @ApiModelProperty("跳转的路径")
    private String path;

    /**
     * 子项
     */
    @ApiModelProperty("子项")
    private List<MenuVO> children;
}
