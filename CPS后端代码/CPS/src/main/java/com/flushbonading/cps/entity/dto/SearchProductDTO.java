package com.flushbonading.cps.entity.dto;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/20 18:52
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "SearchProductDTO对象", description = "SearchProductDTO")
public class SearchProductDTO {
    /**
     * 设备id
     */
    @ApiModelProperty(value = "设备id")
    private String equipmentId;

    /**
     * 物料牌号
     */
    @ApiModelProperty(value = "物料牌号")
    private String materialId;

    /**
     * 姓名
     */
    @ApiModelProperty(value = "姓名")
    private String name;

    /**
     * 创建时间
     */
    @ApiModelProperty(value = "创建时间")
    private String createTime;

}
