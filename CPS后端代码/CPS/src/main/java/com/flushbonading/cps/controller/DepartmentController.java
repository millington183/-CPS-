package com.flushbonading.cps.controller;


import com.alibaba.fastjson.JSON;
import com.flushbonading.cps.entity.dto.DepartmentDTO;
import com.flushbonading.cps.service.DepartmentService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

/**
 * <p>
 * 部门前端控制器
 * </p>
 *
 * @author zyx
 * @since 2021-06-13
 */
@RestController
@RequestMapping("/api/department")
@Api(tags = "部门模块", value = "部门模块")
public class DepartmentController {
    /**
     * 自动注入部门服务类
     */
    @Autowired
    DepartmentService departmentService;
    @Autowired
    RedisTemplate<String, Object> redisTemplate;

    /**
     * 得到所有部门,只带有两个参数，id和部门号用作显示下拉列表
     *
     * @return 返回DepartmentDTO字符串
     * @apiNote 访问地址/all
     * @see com.flushbonading.cps.entity.dto.DepartmentDTO
     */
    @ApiOperation("得到所有部门(用于下拉列表)")
    @GetMapping("/all")
    public String getAll() {
        //做页面缓存
        List<DepartmentDTO> allDepartment = (List<DepartmentDTO>) redisTemplate.opsForValue().get("department");
        if (allDepartment != null) {
            return JSON.toJSONString(allDepartment);
        }
        //调用服务中的得到所有部门方法
        allDepartment = departmentService.getAll();
        //存入缓存
        redisTemplate.opsForValue().set("department", allDepartment);
        //转化为JSO并返回
        return JSON.toJSONString(allDepartment);
    }
}

