package com.flushbonading.cps.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.flushbonading.cps.entity.Role;
import com.flushbonading.cps.entity.dto.AddRoleDTO;
import com.flushbonading.cps.entity.dto.EditMenuDTO;
import com.flushbonading.cps.entity.dto.RoleSearchDTO;
import com.flushbonading.cps.entity.vo.RoleVO;
import com.flushbonading.cps.entity.vo.ShowRoleVO;
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
public interface RoleMapper extends BaseMapper<Role> {

    /**
     * 得到所有角色
     *
     * @return
     */
    List<RoleVO> getAll();

    /**
     * 查询所有角色详细信息
     *
     * @param search
     * @return
     */
    List<ShowRoleVO> getAllRolesMessage(@Param("search") RoleSearchDTO search, Integer page);

    /**
     * 得到所有页面总数
     *
     * @param search
     * @return
     */
    Integer getTotalCounts(@Param("search") RoleSearchDTO search);

    /**
     * 增加角色
     *
     * @param addRole
     * @return
     */
    Integer addARole(@Param("addRole") AddRoleDTO addRole);

    /**
     * 删除一个角色
     *
     * @param roleId
     * @return
     */
    Integer deleteARole(String roleId);

    /**
     * @param editMenuDTO
     * @return
     */
    Integer editRole(@Param("editMenuDTO") EditMenuDTO editMenuDTO);
}
