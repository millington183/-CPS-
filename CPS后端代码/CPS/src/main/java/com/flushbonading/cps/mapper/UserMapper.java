package com.flushbonading.cps.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.flushbonading.cps.entity.User;
import com.flushbonading.cps.entity.dto.AddUserDTO;
import com.flushbonading.cps.entity.dto.SearchUsersDTO;
import com.flushbonading.cps.entity.vo.UserManageVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * <p>
 * Mapper 接口
 * </p>
 *
 * @author zyx
 * @since 2021-06-10
 */
@Mapper
public interface UserMapper extends BaseMapper<User> {
    /**
     * 根据工号修改密码
     *
     * @param staffNumber 工号
     * @param password    密码
     * @param salt        盐值
     * @return 返回修改了的行值
     */
    Integer updatePasswordByStaffNumber(String staffNumber, String password, String salt);

    /**
     * 通过角色id查询所有工号
     *
     * @param roleId
     * @return
     */
    List<String> getStaffNumberByRoleId(@Param("roleId") Integer roleId);

    /**
     * 得到所有用户信息
     *
     * @return 返回用户信息的List类型
     */
    List<UserManageVO> getAllUserMessage(SearchUsersDTO search, Integer page);

    /**
     * 得到总记录数
     *
     * @return
     */
    Integer userCounts(@Param("search") SearchUsersDTO search);

    /**
     * 删除一个用户
     *
     * @param staffNumber
     * @return
     */
    Integer deleteUser(String staffNumber);

    /**
     * 添加用户
     *
     * @param addUser
     * @param password
     * @param salt
     * @return
     */
    Integer addAUser(AddUserDTO addUser, String password, String salt);

    /**
     * 修改权限
     *
     * @param roleName
     * @param staffNumber
     * @return
     */
    Integer updateUserRole(String roleName, String staffNumber);

}
