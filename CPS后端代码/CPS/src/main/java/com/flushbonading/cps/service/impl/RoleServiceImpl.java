package com.flushbonading.cps.service.impl;

import cn.hutool.core.lang.Validator;
import cn.hutool.core.util.PageUtil;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.flushbonading.cps.constant.Tip;
import com.flushbonading.cps.entity.Menu;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.Role;
import com.flushbonading.cps.entity.User;
import com.flushbonading.cps.entity.dto.AddRoleDTO;
import com.flushbonading.cps.entity.dto.EditMenuDTO;
import com.flushbonading.cps.entity.dto.MenuDTO;
import com.flushbonading.cps.entity.dto.RoleSearchDTO;
import com.flushbonading.cps.entity.vo.MenuVO;
import com.flushbonading.cps.entity.vo.RoleVO;
import com.flushbonading.cps.entity.vo.ShowRoleVO;
import com.flushbonading.cps.mapper.MenuMapper;
import com.flushbonading.cps.mapper.RoleMapper;
import com.flushbonading.cps.mapper.RoleMenuMapper;
import com.flushbonading.cps.mapper.UserMapper;
import com.flushbonading.cps.service.MenuService;
import com.flushbonading.cps.service.RoleService;
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
 * @since 2021-06-11
 */
@Service
public class RoleServiceImpl extends ServiceImpl<RoleMapper, Role> implements RoleService {
    @Autowired
    RoleMapper roleMapper;
    @Autowired
    UserMapper userMapper;
    @Autowired
    RoleMenuMapper roleMenuMapper;
    @Autowired
    MenuMapper menuMapper;
    @Autowired
    MenuService menuService;
    @Autowired
    RedisTemplate<String, Object> redisTemplate;


    @Override
    public List<ShowRoleVO> getAllRolesMessage(RoleSearchDTO search, Integer pageIndex) {
        return roleMapper.getAllRolesMessage(search, pageIndex);
    }

    @Override
    public List<RoleVO> getAll() {
        return roleMapper.getAll();
    }

    @Override
    public Integer getTotalCounts(RoleSearchDTO search) {
        return roleMapper.getTotalCounts(search);
    }

    @Override
    public Integer getTotalPages(RoleSearchDTO search) {
        return PageUtil.totalPage(getTotalCounts(search), 7);
    }

    @Override
    public RespBean addARole(AddRoleDTO addRole) {
        //校验
        addRoleVerify(addRole);
        Integer roleConst = roleMapper.addARole(addRole);
        Validator.validateNotNull(roleConst, Tip.INSERT_ERROR.content());
        return RespBean.success(Tip.INSERT_SUCCESS.content());
    }

    @Override
    public RespBean deleteARole(String roleId) {
        QueryWrapper<User> wrapper = new QueryWrapper<>();
        wrapper.eq("role_id", roleId);
        User user = userMapper.selectOne(wrapper);
        Validator.validateNull(user, Tip.BELONG_TO_ROLE.content());

        Integer deleteRole = roleMapper.deleteARole(roleId);
        Validator.validateNotNull(deleteRole, Tip.DELETE_ERROE.content());
        Integer deleteRoleMenu = roleMenuMapper.deleteRoleMenuByRoleId(roleId);
        if (deleteRoleMenu.intValue() < 0) {
            return RespBean.error(Tip.DELETE_ERROE.content());
        }
        List<String> numberByRoleId = userMapper.getStaffNumberByRoleId(Integer.parseInt(roleId));
        for (String number : numberByRoleId) {
            redisTemplate.delete("menu:" + number);
            redisTemplate.delete("jurisdiction:" + roleId);
        }
        return RespBean.success(Tip.DELETE_SUCCESS.content());
    }

    @Override
    public Integer editRole(EditMenuDTO editMenuDTO) {
        return roleMapper.editRole(editMenuDTO);
    }

    @Override
    public RespBean editJurisdiction(EditMenuDTO editMenuDTO) {
        System.out.println(editMenuDTO);
        Validator.validateNotEmpty(editMenuDTO.getRoleName(), Tip.ERROR_INPUT.content());
        Integer editRole = editRole(editMenuDTO);
        if (editRole != null) {
            String roleId = editMenuDTO.getRoleId().intValue() + "";
            roleMenuMapper.deleteRoleMenuByRoleId(roleId);
            Integer insertRoleMenu = roleMenuMapper.insertRoleMenu(editMenuDTO.getRoleId(), editMenuDTO.getMenu());
            if (insertRoleMenu != null) {
                List<String> staffNumbers = userMapper.getStaffNumberByRoleId(editMenuDTO.getRoleId());
                for (String staffNumber : staffNumbers) {
                    List<Menu> menus = menuMapper.queryMenuByStaffNumber(staffNumber);
                    List<MenuVO> menuVOS = menuService.menuHandler(menus);
                    redisTemplate.opsForValue().set("menu:" + staffNumber, menuVOS);
                    List<MenuDTO> menuDTOS = menuService.queryMenuByRoleId(editMenuDTO.getRoleId());
                    redisTemplate.opsForValue().set("jurisdiction:" + editMenuDTO.getRoleId(), menuDTOS);
                }
                return RespBean.success(Tip.EDIT_SUCCESS.content());
            }
            return RespBean.error(Tip.EDIT_ERROR.content());
        }
        return RespBean.error(Tip.EDIT_ERROR.content());
    }

    private void addRoleVerify(AddRoleDTO addRole) {
        String roleId = addRole.getRoleId();
        String roleName = addRole.getRoleName();
        String remark = addRole.getRemark();

        Validator.validateNotEmpty(roleId, Tip.ERROR_INPUT.content());
        Validator.validateNotEmpty(roleName, Tip.ERROR_INPUT.content());
        Validator.validateNotEmpty(remark, Tip.ERROR_INPUT.content());

        QueryWrapper<Role> queryWrapper = new QueryWrapper<>();
        queryWrapper.eq("role_id", roleId);
        Role role = roleMapper.selectOne(queryWrapper);
        Validator.validateNull(role, Tip.ID_EXIST.content());

        queryWrapper = new QueryWrapper<>();
        queryWrapper.eq("role_name", roleName);
        role = roleMapper.selectOne(queryWrapper);
        Validator.validateNull(role, Tip.ROLE_NAME_EXIST.content());
    }
}
