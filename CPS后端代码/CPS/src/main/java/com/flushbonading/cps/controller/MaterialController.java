package com.flushbonading.cps.controller;


import com.alibaba.fastjson.JSON;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.vo.MaterialVO;
import com.flushbonading.cps.service.MaterialService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * <p>
 * 前端控制器
 * </p>
 *
 * @author zyx
 * @since 2021-06-17
 */
@RestController
@Api(tags = "物料模块", value = "物料模块")
@RequestMapping("/api/material")
public class MaterialController {
    @Autowired
    MaterialService materialService;

    @ApiOperation("显示所有物料信息")
    @PostMapping("/show/{page}")
    public String showMaterials(String materialId, @PathVariable("page") Integer page) {
        System.out.println(materialId);
        List<MaterialVO> materialVOs = materialService.showMaterials(materialId, (page - 1) * 7 + 0);
        return JSON.toJSONString(materialVOs);
    }

    @GetMapping("/totalPage")
    @ApiOperation("页面总数")
    public String totalPages(String materialId) {
        Integer pages = materialService.totalPages(materialId);
        return JSON.toJSONString(pages);
    }

    @PostMapping("/insert")
    @ApiOperation("新增物料")
    public String addAMaterial(@RequestBody MaterialVO material) {
        RespBean respBean = materialService.addAMaterial(material);
        return JSON.toJSONString(respBean);
    }

    @PostMapping("/delete/{materialId}")
    @ApiOperation("删除一个物料")
    public String deleteAMaterial(@PathVariable("materialId") String materialId) {
        RespBean resp = materialService.deleteAMaterialByMaterialId(materialId);
        return JSON.toJSONString(resp);
    }

    @PostMapping("/update")
    @ApiOperation("修改物料信息")
    public String updateAMaterial(@RequestBody MaterialVO material) {
        RespBean resp = materialService.updateAMaterial(material);
        return JSON.toJSONString(resp);
    }
}

