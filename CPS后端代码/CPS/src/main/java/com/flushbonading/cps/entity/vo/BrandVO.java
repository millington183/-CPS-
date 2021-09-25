package com.flushbonading.cps.entity.vo;

import io.swagger.annotations.ApiModel;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/7/10 14:55
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "BrandVO", description = "BrandVO")
public class BrandVO {
    private List<String> brandName;
    private List<String> brandData;
}
