package com.flushbonading.cps.entity.vo;

import com.flushbonading.cps.entity.dto.EnvironmentDTO;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;
import java.util.Map;

/**
 * 主页面所有数据
 *
 * @author zyx 2134208960@qq.com
 * @date 2021/6/9 20:26
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "主页渲染对象", description = "环境信息对象")
public class MainVO {

    /**
     * 环境信息（温度，湿度，粉尘）
     */
    @ApiModelProperty(value = "环境信息（温度，湿度，粉尘）")
    private EnvironmentDTO environmentDTO;

    /**
     * 上班员工数量
     */
    @ApiModelProperty(value = "上班员工数量")
    private Integer peopleCounts;
    /**
     * 每日每时刻生产数量
     */
    @ApiModelProperty(value = "每日每时刻生产数量")
    private List<Map<String, Object>> diaryMessage;
    /**
     * 每种物料的生产数量
     */
    @ApiModelProperty(value = "每种物料的生产数量")
    private List<Map<String, Object>> materialCounts;
}
