package com.flushbonading.cps.entity.dto;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/19 10:34
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "AddRecordDTO对象", description = "AddRecordDTO")
public class AddRecordDTO {
    /**
     * 设备id
     */
    @ApiModelProperty("设备id")
    private String equipmentId;

    /**
     * 保养人
     */
    @ApiModelProperty("保养人")
    private String name;

    /**
     * 保养内容
     */
    @ApiModelProperty("保养内容")
    private String remark;

    /**
     * 创建时间
     */
    @ApiModelProperty("创建时间")
    private String createTime;
}
