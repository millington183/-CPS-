package com.flushbonading.cps.controller;


import com.alibaba.fastjson.JSON;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.dto.SearchProductDTO;
import com.flushbonading.cps.entity.vo.ProductVO;
import com.flushbonading.cps.service.ProductService;
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
 * @since 2021-06-09
 */
@Api(value = "产品模块", tags = "产品模块")
@RestController
@RequestMapping("/api/product")
public class ProductController {
    @Autowired
    ProductService productService;

    @ApiOperation("得到所有生产数据(包含查询)")
    @PostMapping("/show/{page}")
    public String getAllProducts(@RequestBody SearchProductDTO search, @PathVariable("page") Integer page) {
        List<ProductVO> message = productService.getAllProductMessage(search, 7 * (page - 1) + 0);
        return JSON.toJSONString(message);
    }

    @ApiOperation("得到页面总数")
    @PostMapping("/totalPage")
    public String getTotalPages(@RequestBody SearchProductDTO search) {
        Integer pages = productService.totalPages(search);
        return JSON.toJSONString(pages);
    }

    @PostMapping("/delete/{id}")
    @ApiOperation("根据id删除产品")
    public String deleteProductById(@PathVariable("id") String id) {
        RespBean resp = productService.deleteProductById(id);
        return JSON.toJSONString(resp);
    }
}

