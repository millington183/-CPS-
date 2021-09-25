package com.flushbonading.cps.entity.vo;

import io.swagger.annotations.ApiModel;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/7/10 16:58
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "DefectiveDataVO", description = "DefectiveDataVO")
public class DefectiveDataVO {
    private String material;
    private String defective;
    private String createTime;
}
