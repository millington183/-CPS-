package com.flushbonading.cps.service.impl;

import cn.hutool.core.lang.Validator;
import cn.hutool.core.util.PageUtil;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.flushbonading.cps.constant.Tip;
import com.flushbonading.cps.entity.Menu;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.Staff;
import com.flushbonading.cps.entity.User;
import com.flushbonading.cps.entity.dto.AddUserDTO;
import com.flushbonading.cps.entity.dto.SearchUsersDTO;
import com.flushbonading.cps.entity.vo.MenuVO;
import com.flushbonading.cps.entity.vo.PasswordVO;
import com.flushbonading.cps.entity.vo.UserManageVO;
import com.flushbonading.cps.entity.vo.UserVO;
import com.flushbonading.cps.mapper.MenuMapper;
import com.flushbonading.cps.mapper.StaffMapper;
import com.flushbonading.cps.mapper.UserMapper;
import com.flushbonading.cps.service.MenuService;
import com.flushbonading.cps.service.UserService;
import com.flushbonading.cps.util.PasswordUtil;
import com.flushbonading.cps.util.TokenUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * <p>
 * 服务实现类
 * </p>
 *
 * @author zyx
 * @since 2021-06-10
 */
@Service
public class UserServiceImpl extends ServiceImpl<UserMapper, User> implements UserService {

    @Autowired
    UserMapper userMapper;
    @Autowired
    StaffMapper staffMapper;
    @Autowired
    MenuService menuService;
    @Autowired
    MenuMapper menuMapper;
    @Autowired
    RedisTemplate<String, Object> redisTemplate;

    @Override
    public RespBean login(UserVO userVO) {
        /*
            解析出用户名和密码
         */
        String staffNumber = userVO.getStaffNumber();
        String password = userVO.getPassword();

        //校验工号不为空
        Validator.validateNotEmpty(staffNumber, Tip.ERROR_INPUT.content());
        //校验密码不为空
        Validator.validateNotEmpty(password, Tip.ERROR_INPUT.content());
        
        /*
            通过验证则从数据库查询,查看数据库中是否有该用户
         */
        User user = queryUserByStaffNumber(staffNumber);
        Validator.validateNotNull(user, Tip.USER_NOT_EXIST.content());

        /*
            检验密码是否正确
         */
        //取得盐值
        String salt = user.getSalt();
        boolean verify = PasswordUtil.verifyPassword(password, user.getPassword(), salt);
        Validator.validateTrue(verify, Tip.PASSWORD_ERROR.content());
        return RespBean.success(Tip.LOGIN_SUCCESS.content());
    }

    @Override
    public User queryUserByStaffNumber(String staffNumber) {
        /*
            构建查询构造器并查询结果
         */
        System.out.println(staffNumber);
        QueryWrapper<User> userQueryWrapper = new QueryWrapper<>();
        userQueryWrapper.eq("staff_number", staffNumber);
        return userMapper.selectOne(userQueryWrapper);
    }

    /**
     * 修改密码全业务流程
     *
     * @param staffNumber
     * @param passwordVO
     * @return
     */
    @Override
    public RespBean editPassword(String staffNumber, PasswordVO passwordVO) {
        //解析该用户的输入
        String originalPassword = passwordVO.getOriginalPassword();
        String newPassword = passwordVO.getNewPassword();
        String repeatPassword = passwordVO.getRepeatPassword();

        //校验输入
        verifyPutIn(staffNumber, originalPassword, newPassword, repeatPassword);
        Integer updatePassword = updatePassword(staffNumber, PasswordUtil.initPassword(newPassword));
        Validator.validateNotNull(updatePassword, Tip.EDIT_ERROR.content());
        //redisTemplate.delete("token:" + staffNumber);
        redisTemplate.opsForValue().set("token:" + staffNumber, newPassword);
        return RespBean.success(Tip.EDIT_SUCCESS.content());
    }

    /**
     * 修改密码
     *
     * @param staffNumber 工号
     * @param container   存放密码信息的容器
     * @return
     */
    @Override
    public Integer updatePassword(String staffNumber, List<String> container) {
        return userMapper.updatePasswordByStaffNumber(staffNumber, container.get(0), container.get(1));
    }

    /**
     * 查询所有用户信息
     *
     * @return
     */
    @Override
    public List<UserManageVO> getAllUserMessage(SearchUsersDTO search, Integer page) {
        return userMapper.getAllUserMessage(search, page);
    }

    @Override
    public Integer userCounts(SearchUsersDTO search) {
        return userMapper.userCounts(search);
    }

    @Override
    public Integer totalPage(SearchUsersDTO search) {
        return PageUtil.totalPage(userCounts(search), 7);
    }

    @Override
    public RespBean deleteUser(String staffNumber) {
        Validator.validateNotEmpty(staffNumber, Tip.ERROR_INPUT.content());
        Integer deleteUser = userMapper.deleteUser(staffNumber);
        if (deleteUser.intValue() <= 0) {
            return RespBean.error(Tip.DELETE_ERROE.content());
        }
        redisTemplate.delete("menu:" + staffNumber);
        redisTemplate.delete("token:" + staffNumber);
        return RespBean.success(Tip.DELETE_SUCCESS.content());
    }

    @Override
    public RespBean insertAUser(AddUserDTO addUser) {
        String staffNumber = addUser.getStaffNumber();
        String name = addUser.getName();
        String roleName = addUser.getRoleName();

        //校验输入
        verifyAddUser(staffNumber, name, roleName);
        List<String> initPassword = PasswordUtil.initPassword("123456");
        Integer userResult = userMapper.addAUser(addUser, initPassword.get(0), initPassword.get(1));
        Validator.validateNotNull(userResult, Tip.INSERT_ERROR.content());
        UserVO userVO = UserVO.builder().staffNumber(staffNumber).password("123456").build();
        redisTemplate.opsForValue().set("token:" + staffNumber, TokenUtils.getUserToken(userVO));
        return RespBean.success(Tip.INSERT_SUCCESS.content());
    }

    @Override
    public RespBean updateUserRole(String roleName, String staffNumber) {
        Integer updateUser = userMapper.updateUserRole(roleName, staffNumber);
        Validator.validateNotNull(updateUser, Tip.EQUAL_ERROR.content());
        //更新角色要更改缓存
        List<Menu> menus = menuMapper.queryMenuByStaffNumber(staffNumber);
        List<MenuVO> menuVOList = menuService.menuHandler(menus);
        redisTemplate.opsForValue().set("menu:" + staffNumber, menuVOList);
        return RespBean.success(Tip.EDIT_SUCCESS.content());
    }

    private void verifyAddUser(String staffNumber, String name, String roleName) {
        Validator.validateNotEmpty(staffNumber, Tip.ERROR_INPUT.content());
        Validator.validateNotEmpty(name, Tip.ERROR_INPUT.content());
        Validator.validateNotEmpty(roleName, Tip.ERROR_INPUT.content());

        QueryWrapper<User> userWrapper = new QueryWrapper<>();
        userWrapper.eq("staff_number", staffNumber);
        User user = userMapper.selectOne(userWrapper);
        Validator.validateNull(user, Tip.USER_EXIST.content());

        QueryWrapper<Staff> staffWrapper = new QueryWrapper<>();
        staffWrapper.eq("staff_number", staffNumber);
        staffWrapper.eq("name", name);
        Staff staff = staffMapper.selectOne(staffWrapper);
        Validator.validateNotNull(staff, Tip.ADD_USER_ERROR.content());
    }

    private void verifyPutIn(String staffNumber, String originalPassword, String newPassword, String repeatPassword) {
        //校验值是否有空
        Validator.validateNotEmpty(originalPassword, Tip.ERROR_INPUT.content());
        Validator.validateNotEmpty(newPassword, Tip.ERROR_INPUT.content());
        Validator.validateNotEmpty(repeatPassword, Tip.ERROR_INPUT.content());

        //取出数据库里的值
        User user = queryUserByStaffNumber(staffNumber);
        //校验密码是否相同
        boolean verifyPassword = PasswordUtil.verifyPassword(originalPassword, user.getPassword(), user.getSalt());
        Validator.validateTrue(verifyPassword, Tip.ORIGINAL_PASSWORD_ERROR.content());

        //校验两次输入的密码是否相同
        boolean verifyEqual = newPassword.equals(repeatPassword);
        Validator.validateTrue(verifyEqual, Tip.EQUAL_ERROR.content());
    }

}
