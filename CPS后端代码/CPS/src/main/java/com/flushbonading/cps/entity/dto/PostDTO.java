package com.flushbonading.cps.entity.dto;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/14 9:51
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "PostDTO对象", description = "PostDTO")
public class PostDTO {
    /**
     * 职务id号
     */
    @ApiModelProperty("职务id号")
    private Integer id;

    /**
     * 职务名
     */
    @ApiModelProperty("职务名")
    private String postName;
}
