package com.flushbonading.cps.entity.vo;

import io.swagger.annotations.ApiModel;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/7/12 9:23
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@ApiModel(value = "ProductDataVO", description = "ProductDataVO")
public class ProductDataVO {
    private String materialId;
    private String counts;
}
