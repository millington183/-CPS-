package com.flushbonading.cps.controller;


import com.alibaba.fastjson.JSON;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.dto.AddRecordDTO;
import com.flushbonading.cps.entity.dto.MaintenanceRecordDTO;
import com.flushbonading.cps.entity.vo.MaintenanceRecordVO;
import com.flushbonading.cps.service.MaintenanceRecordService;
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
 * @since 2021-06-18
 */
@RestController
@RequestMapping("/api/maintenance-record")
@Api(tags = "设备保养模块", value = "设备保养模块")
public class MaintenanceRecordController {
    @Autowired
    MaintenanceRecordService maintenanceRecordService;

    @PostMapping("/show/{page}")
    @ApiOperation("查询所有保养信息")
    public String getAllMaintenanceRecord(@RequestBody MaintenanceRecordDTO search, @PathVariable("page") Integer page) {
        List<MaintenanceRecordVO> record = maintenanceRecordService.getAllMaintenanceRecord(search, 7 * (page - 1) + 0);
        return JSON.toJSONString(record);
    }

    @PostMapping("/insert")
    @ApiOperation("插入保养记录")
    public String addAMaintenanceRecord(@RequestBody AddRecordDTO maintenanceRecord) {
        RespBean resp = maintenanceRecordService.addAMaintenanceRecord(maintenanceRecord);
        return JSON.toJSONString(resp);
    }

    @PostMapping("/totalPage")
    @ApiOperation("得到页面总数")
    public String getTotalPageCounts(@RequestBody MaintenanceRecordDTO search) {
        Integer pageCounts = maintenanceRecordService.getTotalPageCounts(search);
        return JSON.toJSONString(pageCounts);
    }

    @PostMapping("/delete")
    @ApiOperation("删除一个保养记录")
    public String deleteARecordById(@RequestBody String id) {
        RespBean deleteRecord = maintenanceRecordService.deleteARecordById(id);
        return JSON.toJSONString(deleteRecord);
    }

    @PostMapping("/update/{id}")
    @ApiOperation("修改保养信息")
    public String updateARecord(@RequestBody AddRecordDTO updateRecord, @PathVariable("id") Integer id) {
        RespBean resp = maintenanceRecordService.updateARecord(updateRecord, id);
        return JSON.toJSONString(resp);
    }
}

