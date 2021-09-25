package com.flushbonading.cps.controller;


import com.alibaba.fastjson.JSON;
import com.flushbonading.cps.entity.dto.SearchStaffDeviceDTO;
import com.flushbonading.cps.entity.vo.StaffDeviceVO;
import com.flushbonading.cps.service.StaffDeviceService;
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
 * @since 2021-06-21
 */
@RestController
@RequestMapping("/api/staff-device")
@Api(tags = "上班情况", value = "上班情况")
public class StaffDeviceController {
    @Autowired
    StaffDeviceService staffDeviceService;

    @PostMapping("/show/{page}")
    @ApiOperation("得到所有上班情况")
    public String getAllStaffDeviceDatas(@RequestBody SearchStaffDeviceDTO search, @PathVariable("page") Integer page) {
        List<StaffDeviceVO> allStaffDevice = staffDeviceService.getAllStaffDeviceDatas(search, (page - 1) * 7 + 0);
        return JSON.toJSONString(allStaffDevice);
    }

    @PostMapping("/totalPage")
    @ApiOperation("得到页面总数")
    public String getTotalPages(@RequestBody SearchStaffDeviceDTO search) {
        Integer totalPages = staffDeviceService.getTotalPages(search);
        return JSON.toJSONString(totalPages);
    }
}

