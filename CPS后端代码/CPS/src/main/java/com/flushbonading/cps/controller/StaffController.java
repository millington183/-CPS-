package com.flushbonading.cps.controller;


import com.alibaba.fastjson.JSON;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.dto.AddStaffDTO;
import com.flushbonading.cps.entity.dto.PersonalInformationDTO;
import com.flushbonading.cps.entity.dto.SearchUsersDTO;
import com.flushbonading.cps.entity.vo.StaffVO;
import com.flushbonading.cps.service.StaffService;
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
 * @since 2021-06-12
 */
@RestController
@RequestMapping("/api/staff")
@Api(tags = "员工模块", value = "员工模块")
public class StaffController {
    /**
     * 员工服务对象
     */
    @Autowired
    StaffService staffService;

    @ApiOperation("得到登录人的姓名")
    @GetMapping("/name")
    public String getName(HttpServletRequest request) {
        String token = request.getHeader("token");
        String staffNumber = TokenUtils.getStaffNumber(token);
        String name = staffService.getNameByStaffNumber(staffNumber);
        return JSON.toJSONString(name);
    }

    @ApiOperation("个人信息")
    @PostMapping("/personalInformation")
    public String getPersonalInformation(HttpServletRequest request) {
        String token = request.getHeader("token");
        String staffNumber = TokenUtils.getStaffNumber(token);
        PersonalInformationDTO information = staffService.selectInformationByStaffNumber(staffNumber);
        return JSON.toJSONString(information);
    }

    @ApiOperation("显示所有员工的信息(员工管理)")
    @PostMapping("/all/{page}")
    public String getAll(@RequestBody SearchUsersDTO search, @PathVariable("page") Integer page) {
        //String url = "http://localhost:8086/main/QRcode/getQRcode/";
        String url = "http://49.234.81.196:2000/main/QRcode/getQRcode/";
        List<StaffVO> message = staffService.getAllStaffMessage(search, 6 * (page - 1) + 0);
        for (StaffVO staffVO : message) {
            staffVO.setUrl(url + staffVO.getStaffNumber());
        }
        System.out.println(message.size());
        return JSON.toJSONString(message);
    }

    @PostMapping("/totalPage")
    @ApiOperation("页面总数")
    public String getTotalPage(@RequestBody SearchUsersDTO search) {
        Integer pages = staffService.getTotalPage(search);
        return JSON.toJSONString(pages);
    }

    @ApiOperation("删除员工")
    @PostMapping("/delete")
    public String deleteStaff(@RequestBody String staffNumber) {
        RespBean deleteStaff = staffService.deleteStaff(staffNumber);
        return JSON.toJSONString(deleteStaff);
    }

    @ApiOperation("增加一个员工")
    @PostMapping("/insert")
    public String insertAStaff(@RequestBody AddStaffDTO addStaff) {
        RespBean respBean = staffService.insertAStaff(addStaff);
        return JSON.toJSONString(respBean);
    }

    @PostMapping("/updatePersonalInformation")
    @ApiOperation("修改个人信息")
    public String updatePersonalInformation(@RequestBody PersonalInformationDTO personalInformation) {
        RespBean respBean = staffService.updatePersonalInformation(personalInformation);
        return JSON.toJSONString(respBean);
    }

    @PostMapping("/updateStaff")
    @ApiOperation("修改员工信息")
    public String updateSatffByStaffNumber(@RequestBody AddStaffDTO edit) {
        RespBean respBean = staffService.updateSatffByStaffNumber(edit);
        return JSON.toJSONString(respBean);
    }
}

