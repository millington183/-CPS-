package com.flushbonading.cps.entity.dto;

import io.swagger.annotations.ApiModel;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDateTime;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/7/7 20:33
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "PostDownMaintenanceDTO对象", description = "PostDownMaintenanceDTO")
public class PostDownMaintenanceDTO {
    private String equipmentId;
    private LocalDateTime maintenancePeriod;
}
