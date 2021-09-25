package com.flushbonading.cps.entity.dto;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/21 14:15
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "SearchStaffDeviceDTO对象", description = "SearchStaffDeviceDTO")
public class SearchStaffDeviceDTO {
    /**
     * 创建字段的时间
     */
    @ApiModelProperty("创建时间")
    private String createTime;

    /**
     * 工号
     */
    @ApiModelProperty("工号")
    private String staffNumber;
}
