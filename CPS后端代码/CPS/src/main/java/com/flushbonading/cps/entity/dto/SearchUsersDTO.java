package com.flushbonading.cps.entity.dto;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/14 8:25
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "SearchUsersDTO对象", description = "SearchUsersDTO")
public class SearchUsersDTO {
    /**
     * 姓名
     */
    @ApiModelProperty("姓名")
    private String name;

    /**
     * 工号
     */
    @ApiModelProperty("工号")
    private String staffNumber;
}
