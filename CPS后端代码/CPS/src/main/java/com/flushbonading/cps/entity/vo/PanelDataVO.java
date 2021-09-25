package com.flushbonading.cps.entity.vo;

import io.swagger.annotations.ApiModel;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/7/10 11:34
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "DiaryDataVO", description = "DiaryDataVO")
public class PanelDataVO {
    private List<DiaryDataVO> diaryData;
    private EnvironmentVO environmentData;
    private BrandVO brand;
    private List<String> yieldData;
    private List<DefectiveDataVO> defectiveData;
    private MaintenanceDataVO maintenanceData;
}
