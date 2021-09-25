package com.flushbonading.cps.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.flushbonading.cps.entity.RoleMenu;
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
public interface RoleMenuMapper extends BaseMapper<RoleMenu> {
    /**
     * 通过role_id删除记录
     *
     * @param roleId
     * @return
     */
    Integer deleteRoleMenuByRoleId(String roleId);

    /**
     * 插入权限
     *
     * @param roleId
     * @param list
     * @return
     */
    Integer insertRoleMenu(@Param("roleId") Integer roleId, @Param("list") List<Integer> list);
}
