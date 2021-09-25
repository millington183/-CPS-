package com.flushbonading.cps.controller.common;

import com.flushbonading.cps.entity.vo.BrandVO;
import com.flushbonading.cps.entity.vo.PanelDataVO;
import com.flushbonading.cps.service.*;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

/**
 * 主页面模块
 *
 * @author zyx 2134208960@qq.com
 * @date 2021/6/9 21:15
 * @since 1.0.0
 */
@Api(value = "主页面模块", tags = "主页面模块")
@RestController
@RequestMapping("/api/common")
@Slf4j
public class CommonController {
    @Autowired
    EnvironmentService environmentService;
    @Autowired
    EquipmentService equipmentService;
    @Autowired
    DiaryService diaryService;
    @Autowired
    ProductService productService;
    @Autowired
    MaterialService materialService;

    @GetMapping("/allData")
    @ApiOperation("得到页面上所有数据")
    public PanelDataVO getAllData() {
        log.info("请求了数据展示页面");
        List<String> brandName = materialService.getBrandName();
        List<String> brandData = productService.getBrandData(brandName);
        BrandVO brand = BrandVO.builder()
                .brandName(brandName)
                .brandData(brandData)
                .build();
        PanelDataVO panelData = PanelDataVO.builder()
                .environmentData(environmentService.getNowEnvironmentVO())
                .diaryData(diaryService.getDiaryDataVos())
                .brand(brand)
                .yieldData(productService.getYieldData())
                .maintenanceData(equipmentService.getMaintenanceDataVO())
                .defectiveData(productService.getDefectiveData())
                .build();
        return panelData;
    }
}
