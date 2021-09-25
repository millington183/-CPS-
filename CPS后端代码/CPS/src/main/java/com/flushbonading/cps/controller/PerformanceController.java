package com.flushbonading.cps.controller;


import com.alibaba.fastjson.JSON;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.dto.AddPerformanceDTO;
import com.flushbonading.cps.entity.dto.EditPerformanceDTO;
import com.flushbonading.cps.entity.dto.SearchPerformanceDTO;
import com.flushbonading.cps.entity.vo.PerformanceVO;
import com.flushbonading.cps.entity.vo.PersonalPerformanceVO;
import com.flushbonading.cps.service.PerformanceService;
import com.flushbonading.cps.util.TokenUtils;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import javax.servlet.http.HttpServletRequest;
import java.util.List;

/**
 * <p>
 * 前端控制器
 * </p>
 *
 * @author zyx
 * @since 2021-06-21
 */
@RestController
@RequestMapping("/api/performance")
@Api(value = "绩效模块", tags = "绩效模块")
public class PerformanceController {
    @Autowired
    PerformanceService performanceService;

    @PostMapping("/insert")
    @ApiOperation("增加一个绩效信息")
    public String insertAPerformance(@RequestBody AddPerformanceDTO addPerformance) {
        RespBean respBean = performanceService.insertAPerformance(addPerformance);
        return JSON.toJSONString(respBean);
    }

    @PostMapping("/show/{page}")
    @ApiOperation("查询所有绩效")
    public String selectAllPerformances(@RequestBody SearchPerformanceDTO search, @PathVariable("page") Integer page) {
        List<PerformanceVO> allPerformances = performanceService.selectAllPerformances(search, (page - 1) * 7 + 0);
        return JSON.toJSONString(allPerformances);
    }

    @PostMapping("/totalPages")
    @ApiOperation("查询绩效页数")
    public String getAllPages(@RequestBody SearchPerformanceDTO search) {
        Integer pages = performanceService.getTotalPages(search);
        return JSON.toJSONString(pages);
    }

    @PostMapping("/delete")
    @ApiOperation("通过id(我传过来的id)删除一条绩效")
    public String deletePerformanceByID(@RequestBody String id) {
        RespBean respBean = performanceService.deletePerformanceByID(id);
        return JSON.toJSONString(respBean);
    }

    @PostMapping("/selectOne")
    @ApiOperation("点击修改显示的信息,不显示id,id只是为了方便修改数据")
    public String selectAPerformanceByID(@RequestBody String id) {
        EditPerformanceDTO performance = performanceService.selectAPerformanceByID(id);
        return JSON.toJSONString(performance);
    }

    @PostMapping("/update")
    @ApiOperation("修改绩效")
    public String updatePerformance(@RequestBody EditPerformanceDTO edit) {
        RespBean respBean = performanceService.updatePerformance(edit);
        return JSON.toJSONString(respBean);
    }

    @PostMapping("/personalPerformance/{page}")
    @ApiOperation("个人绩效显示和查询(记得要传表单对象，不然会报错，亲测有效)")
    public String getPersonalPerformanceVOs(@RequestBody String year, @PathVariable("page") Integer page, HttpServletRequest request) {
        System.out.println(year);
        year = year.substring(9, year.length() - 2);
        System.out.println(year);
        String token = request.getHeader("token");
        String staffNumber = TokenUtils.getStaffNumber(token);
        List<PersonalPerformanceVO> performanceVOs = performanceService.getPersonalPerformanceVOs(year, staffNumber, (page - 1) * 6 + 0);
        return JSON.toJSONString(performanceVOs);
    }

    @PostMapping("/personalPerformancePages")
    @ApiOperation("个人绩效所有页面(记得要传表单对象，不然会报错，亲测有效)")
    public String getPersonalPerformancePages(@RequestBody String year, HttpServletRequest request) {
        System.out.println(year);
        year = year.substring(9, year.length() - 2);
        System.out.println(year);
        String token = request.getHeader("token");
        String staffNumber = TokenUtils.getStaffNumber(token);
        Integer pages = performanceService.getPersonalPerformanceTotalPages(year, staffNumber);
        return JSON.toJSONString(pages);
    }
}

