package com.flushbonading.cps.controller;


import com.alibaba.fastjson.JSON;
import com.flushbonading.cps.constant.Tip;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.dto.AddUserDTO;
import com.flushbonading.cps.entity.dto.SearchUsersDTO;
import com.flushbonading.cps.entity.vo.PasswordVO;
import com.flushbonading.cps.entity.vo.UserManageVO;
import com.flushbonading.cps.entity.vo.UserVO;
import com.flushbonading.cps.service.UserService;
import com.flushbonading.cps.util.PasswordUtil;
import com.flushbonading.cps.util.TokenUtils;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.web.bind.annotation.*;

import javax.servlet.http.HttpServletRequest;
import java.util.List;

/**
 * <p>
 * 前端控制器
 * </p>
 *
 * @author zyx
 * @since 2021-06-10
 */
@RestController
@RequestMapping("/api/user")
@Api(tags = "用户模块", value = "用户模块")
public class UserController {
    /**
     * 用户服务对象
     */
    @Autowired
    UserService userService;
    @Autowired
    RedisTemplate<String, Object> redisTemplate;

    /**
     * 修改密码
     *
     * @param request
     * @param passwordVO
     * @return
     */
    @ApiOperation("修改密码")
    @PutMapping("/update/password")
    public String editPassword(HttpServletRequest request, PasswordVO passwordVO) {
        String token = request.getHeader("token");
        RespBean respBean = userService.editPassword(TokenUtils.getStaffNumber(token), passwordVO);
        return JSON.toJSONString(respBean);
    }

    @ApiOperation("分页查询所有用户(用户管理)")
    @PostMapping("/all/message/{page}")
    public String getAllUserMessage(@PathVariable("page") Integer page, @RequestBody SearchUsersDTO search) {
        List<UserManageVO> allUserMessageVO = userService.getAllUserMessage(search, (page - 1) * 7 + 0);
        return JSON.toJSONString(allUserMessageVO);
    }

    @ApiOperation("查询记录总页数")
    @PostMapping("/totalPage")
    public String totalPage(@RequestBody SearchUsersDTO search) {
        return JSON.toJSONString(userService.totalPage(search));
    }

    @ApiOperation("删除用户")
    @PostMapping("/delete")
    public String deleteUser(@RequestBody String staffNumber) {
        System.out.println(staffNumber);
        RespBean deleteUser = userService.deleteUser(staffNumber);
        return JSON.toJSONString(deleteUser);
    }

    @ApiOperation("增加一个用户")
    @PostMapping("/insert")
    public String insertAUser(@RequestBody AddUserDTO addUser) {
        RespBean respBean = userService.insertAUser(addUser);
        return JSON.toJSONString(respBean);
    }

    @PostMapping("/update/{staffNumber}")
    @ApiOperation("修改按钮")
    public String updateUserRole(@RequestBody String roleName, @PathVariable("staffNumber") String staffNumber) {
        RespBean respBean = userService.updateUserRole(roleName, staffNumber);
        return JSON.toJSONString(respBean);
    }

    @PostMapping("/resetPassword")
    @ApiOperation("重置按钮(重置密码)")
    public String resetPassword(@RequestBody String staffNumber) {
        List<String> container = PasswordUtil.initPassword("123456");
        Integer reset = userService.updatePassword(staffNumber, container);
        if (reset.intValue() < 0) {
            return JSON.toJSONString(RespBean.error(Tip.EDIT_ERROR.content()));
        }
        UserVO userVO = UserVO.builder().password("123456").staffNumber(staffNumber).build();
        redisTemplate.opsForValue().set("token:" + staffNumber, TokenUtils.getUserToken(userVO));
        return JSON.toJSONString(RespBean.success(Tip.EDIT_SUCCESS.content()));
    }
}

