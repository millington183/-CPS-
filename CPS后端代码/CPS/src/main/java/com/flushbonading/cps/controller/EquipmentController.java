package com.flushbonading.cps.controller;


import com.alibaba.fastjson.JSON;
import com.flushbonading.cps.entity.User;
import com.flushbonading.cps.entity.vo.EquipmentNameVO;
import com.flushbonading.cps.service.EquipmentService;
import com.flushbonading.cps.service.UserService;
import com.flushbonading.cps.util.TokenUtils;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.servlet.http.HttpServletRequest;
import java.util.List;

/**
 * <p>
 * 设备前端控制器
 * </p>
 *
 * @author zyx
 * @since 2021-06-09
 */
@Api(value = "设备模块", tags = "设备模块")
@RestController
@RequestMapping("/api/equipment")
public class EquipmentController {
    /**
     * 注入设备服务类
     */
    @Autowired
    EquipmentService equipmentService;

    /**
     * 注入用户模块，以便后面使用
     */
    @Autowired
    UserService userService;

    /**
     * 是否需要显示弹窗
     *
     * @param request 前端请求对象
     * @return 返回JSON字符串
     */
    @PostMapping("/isShow")
    @ApiOperation("是否需要显示弹窗提示用户进行保养")
    public String maintenancePeriod(HttpServletRequest request) {
        /*
            新建临时变量
            默认为false,只有有设备距离保养日期不到7天时才会为true
            false表示不显示，true表示显示
         */
        Boolean aBoolean = false;

        //获取请求头中的token,并解析出token中存放的工号
        String token = request.getHeader("token");
        String staffNumber = TokenUtils.getStaffNumber(token);

        //查询该工号的角色
        User user = userService.queryUserByStaffNumber(staffNumber);
        Integer roleId = user.getRoleId();

        //只有角色号为1(即超级用户才会显示弹窗)
        if (roleId == 1) {
            aBoolean = equipmentService.maintenancePeriod();
        }

        //得到JSON字符串并加以返回
        return JSON.toJSONString(aBoolean);
    }

    /**
     * 显示设备中对应的参数
     *
     * @return 返回各种参数的JSON字符串
     */
    @GetMapping("/queryEquipmentInfoNotBind")
    @ApiOperation("显示设备对应参数信息")
    public String queryEquipmentInfoNotBind() {
        /*
           调用查询设备对应参数的服务，并以JSON的格式进行返回
         */
        return JSON.toJSONString(equipmentService.queryEquipmentInfo());
    }

    @ApiOperation("设备下拉列表")
    @GetMapping("/listName")
    public List<EquipmentNameVO> getEquipmentName() {
        return equipmentService.getEquipmentName();
    }
}

