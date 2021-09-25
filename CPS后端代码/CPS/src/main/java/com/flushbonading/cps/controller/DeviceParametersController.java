package com.flushbonading.cps.controller;


import com.alibaba.fastjson.JSON;
import com.flushbonading.cps.entity.dto.EquipmentSearchDTO;
import com.flushbonading.cps.entity.vo.DeviceParametersVO;
import com.flushbonading.cps.entity.vo.EquipmentDataVO;
import com.flushbonading.cps.service.DeviceParametersService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * <p>
 * 设备前端控制器
 * </p>
 *
 * @author zyx
 * @since 2021-06-15
 */
@RestController
@RequestMapping("/api/device-parameters")
@Api(tags = "设备参数模块", value = "设备参数模块")
public class DeviceParametersController {
    /**
     * 注入设备参数服务类
     */
    @Autowired
    DeviceParametersService deviceParametersService;

    /**
     * 得到某一页面上的所有数据
     *
     * @param search    封装的查询对象
     * @param pageIndex 当前的页面号
     * @return 返回JSON字符串
     */
    @PostMapping("/all/{page}")
    @ApiOperation("设备数据页面根据所在页面号查询所有数据（支持搜索）")
    public String getAllDeviceParameters(@RequestBody EquipmentSearchDTO search, @PathVariable("page") Integer pageIndex) {
        /*
         * 通过计算定位到数据库的具体位置
         * 并通过List容器进行返回
         */
        List<DeviceParametersVO> parameters = deviceParametersService.getAllDeviceParameters(search, (pageIndex - 1) * 7 + 0);
        // 转化为JSON格式并进行返回
        return JSON.toJSONString(parameters);
    }

    /**
     * 得到页面的总数
     *
     * @param search 封装的查询对象 前端把数据放在请求体当中
     * @return 返回数据的JSON字符串
     */
    @ApiOperation("得到总页面数")
    @PostMapping("/totalPages")
    public String getTotalPage(@RequestBody EquipmentSearchDTO search) {
        Integer pages = deviceParametersService.totalPage(search);
        return JSON.toJSONString(pages);
    }

    @GetMapping("/getData/{equipmentId}")
    @ApiOperation("得到某条设备信息(数据展示界面)")
    public EquipmentDataVO getEquipmentData(@PathVariable("equipmentId") String equipment_id) {
        return deviceParametersService.getEquipmentData(equipment_id);
    }

}

