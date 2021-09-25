package com.flushbonading.cps.entity.vo;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/17 17:39
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "MaterialVO对象", description = "MaterialVO对象")
public class MaterialVO {
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
}
