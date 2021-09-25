package com.flushbonading.cps.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.flushbonading.cps.entity.Menu;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * <p>
 * Mapper 接口
 * </p>
 *
 * @author zyx
 * @since 2021-06-11
 */
@Mapper
public interface MenuMapper extends BaseMapper<Menu> {
    /**
     * 根据工号查询该工号所拥有权限的功能
     *
     * @param staffNumber 工号
     * @return Menu类型的List
     */
    List<Menu> queryMenuByStaffNumber(String staffNumber);


    /**
     * 得到所有菜单
     *
     * @return
     */
    List<Menu> getAllMenu();

    /**
     * 得到该角色下的所有菜单
     *
     * @param roleId
     * @return
     */
    List<Menu> getMenusByRoleId(@Param("roleId") Integer roleId);
}
