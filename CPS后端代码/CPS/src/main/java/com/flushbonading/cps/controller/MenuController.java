package com.flushbonading.cps.controller;


import com.alibaba.fastjson.JSON;
import com.flushbonading.cps.entity.vo.MenuVO;
import com.flushbonading.cps.service.MenuService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.servlet.http.HttpServletRequest;
import java.util.List;

/**
 * <p>
 * 前端控制器
 * </p>
 *
 * @author zyx
 * @since 2021-06-11
 */
@RestController
@Api(tags = "菜单模块", value = "菜单模块")
@RequestMapping("/api/menu")
public class MenuController {
    /**
     * 菜单服务对象
     */
    @Autowired
    MenuService menuService;

    @ApiOperation("显示菜单")
    @GetMapping("/all")
    public String showMenu(HttpServletRequest request) {
        String token = request.getHeader("token");
        List<MenuVO> menuVOs = menuService.queryMenuByStaffNumber(token);
        menuVOs.forEach(System.out::println);
        return JSON.toJSONString(menuVOs);
    }
}

