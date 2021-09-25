package com.flushbonading.cps.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.User;
import com.flushbonading.cps.entity.dto.AddUserDTO;
import com.flushbonading.cps.entity.dto.SearchUsersDTO;
import com.flushbonading.cps.entity.vo.PasswordVO;
import com.flushbonading.cps.entity.vo.UserManageVO;
import com.flushbonading.cps.entity.vo.UserVO;

import java.util.List;

/**
 * <p>
 * 服务类
 * </p>
 *
 * @author zyx
 * @since 2021-06-10
 */
public interface UserService extends IService<User> {
    /**
     * 登录服务
     *
     * @param userVO 前端信息封装对象
     * @return 返回响应结果
     */
    RespBean login(UserVO userVO);


    /**
     * 通过工号查询用户
     *
     * @param staffNumber
     * @return User对象
     */
    User queryUserByStaffNumber(String staffNumber);

    /**
     * 通过工号修改密码
     *
     * @param staffNumber
     * @return
     */
    RespBean editPassword(String staffNumber, PasswordVO passwordVO);

    /**
     * 修改密码
     *
     * @param staffNumber 工号
     * @param container   存放密码信息的容器
     * @return 返回修改的行
     */
    Integer updatePassword(String staffNumber, List<String> container);

    /**
     * 查询用户信息
     *
     * @param page 页号
     * @return
     */
    List<UserManageVO> getAllUserMessage(SearchUsersDTO search, Integer page);

    /**
     * 得到总记录数
     *
     * @return
     */
    Integer userCounts(SearchUsersDTO search);

    /**
     * 得到总页数
     *
     * @return
     */
    Integer totalPage(SearchUsersDTO search);

    /**
     * 删除用户
     *
     * @param staffNumber
     * @return
     */
    RespBean deleteUser(String staffNumber);

    /**
     * 插入一个用户
     *
     * @param addUser
     * @return
     */
    RespBean insertAUser(AddUserDTO addUser);

    /**
     * 修改权限
     *
     * @param roleName
     * @param staffNumber
     * @return
     */
    RespBean updateUserRole(String roleName, String staffNumber);
}
