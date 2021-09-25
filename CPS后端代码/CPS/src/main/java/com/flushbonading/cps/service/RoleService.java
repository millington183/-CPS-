package com.flushbonading.cps.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.Role;
import com.flushbonading.cps.entity.dto.AddRoleDTO;
import com.flushbonading.cps.entity.dto.EditMenuDTO;
import com.flushbonading.cps.entity.dto.RoleSearchDTO;
import com.flushbonading.cps.entity.vo.RoleVO;
import com.flushbonading.cps.entity.vo.ShowRoleVO;

import java.util.List;

/**
 * <p>
 * 服务类
 * </p>
 *
 * @author zyx
 * @since 2021-06-11
 */
public interface RoleService extends IService<Role> {
    /**
     * 查询所有角色详细信息
     *
     * @param search
     * @return
     */
    List<ShowRoleVO> getAllRolesMessage(RoleSearchDTO search, Integer pageIndex);

    /**
     * 查询所有角色
     *
     * @return
     */
    List<RoleVO> getAll();

    /**
     * 得到所有记录总数
     *
     * @param search
     * @return
     */
    Integer getTotalCounts(RoleSearchDTO search);

    /**
     * 得到页面总数
     *
     * @param search
     * @return
     */
    Integer getTotalPages(RoleSearchDTO search);

    /**
     * 插入一个角色
     *
     * @param addRole
     * @return
     */
    RespBean addARole(AddRoleDTO addRole);

    /**
     * 删除一个角色
     *
     * @param roleId
     * @return
     */
    RespBean deleteARole(String roleId);

    /**
     * @param editMenuDTO
     * @return
     */
    Integer editRole(EditMenuDTO editMenuDTO);

    RespBean editJurisdiction(EditMenuDTO editMenuDTO);
}
