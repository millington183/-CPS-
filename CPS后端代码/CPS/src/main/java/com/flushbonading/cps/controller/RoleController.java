package com.flushbonading.cps.controller;


import com.alibaba.fastjson.JSON;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.dto.AddRoleDTO;
import com.flushbonading.cps.entity.dto.EditMenuDTO;
import com.flushbonading.cps.entity.dto.MenuDTO;
import com.flushbonading.cps.entity.dto.RoleSearchDTO;
import com.flushbonading.cps.entity.vo.RoleVO;
import com.flushbonading.cps.entity.vo.ShowRoleVO;
import com.flushbonading.cps.service.MenuService;
import com.flushbonading.cps.service.RoleService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.web.bind.annotation.*;

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
@RequestMapping("/api/role")
@Api(tags = "角色模块", value = "角色模块")
public class RoleController {
    @Autowired
    RoleService roleService;
    @Autowired
    MenuService menuService;
    @Autowired
    RedisTemplate<String, Object> redisTemplate;

    @ApiOperation("显示所有角色的详细信息")
    @PostMapping("/show/{page}")
    public String getAllRolesMessage(@RequestBody RoleSearchDTO search, @PathVariable("page") Integer page) {
        List<ShowRoleVO> message = roleService.getAllRolesMessage(search, 7 * (page - 1) + 0);
        return JSON.toJSONString(message);
    }

    @ApiOperation("得到所有角色(用于显示下拉列表)")
    @GetMapping("/all")
    public String getAll() {
        List<RoleVO> roleVOList = roleService.getAll();
        return JSON.toJSONString(roleVOList);
    }

    @PostMapping("/totalPages")
    @ApiOperation("得到页面总数")
    public String getTotalPages(@RequestBody RoleSearchDTO search) {
        Integer pages = roleService.getTotalPages(search);
        return JSON.toJSONString(pages);
    }

    @PostMapping("/insert")
    @ApiOperation("增加角色")
    public String addARole(@RequestBody AddRoleDTO addRole) {
        RespBean respBean = roleService.addARole(addRole);
        return JSON.toJSONString(respBean);
    }

    @PostMapping("/delete")
    @ApiOperation("删除一个角色")
    public String deleteARole(@RequestBody String roleId) {
        RespBean deleteResponse = roleService.deleteARole(roleId);
        return JSON.toJSONString(deleteResponse);
    }

    @PostMapping("/allMenu/{roleId}")
    @ApiOperation("显示所有权限")
    public String getAllMenu(@PathVariable("roleId") Integer roleId) {
        List<MenuDTO> menuDTOS = (List<MenuDTO>) redisTemplate.opsForValue().get("jurisdiction:" + roleId);
        if (menuDTOS != null) {
            return JSON.toJSONString(menuDTOS);
        }
        menuDTOS = menuService.queryMenuByRoleId(roleId);
        redisTemplate.opsForValue().set("jurisdiction:" + roleId, menuDTOS);
        return JSON.toJSONString(menuDTOS);
    }

    @PostMapping("/editJurisdiction")
    @ApiOperation("修改权限")
    public String editJurisdiction(@RequestBody EditMenuDTO editMenuDTO) {
        System.out.println(editMenuDTO);
        RespBean respBean = roleService.editJurisdiction(editMenuDTO);
        return JSON.toJSONString(respBean);
    }

}

