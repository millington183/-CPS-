package com.flushbonading.cps.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.flushbonading.cps.entity.Menu;
import com.flushbonading.cps.entity.dto.MenuDTO;
import com.flushbonading.cps.entity.vo.MenuVO;

import java.util.List;

/**
 * <p>
 * 服务类
 * </p>
 *
 * @author zyx
 * @since 2021-06-11
 */
public interface MenuService extends IService<Menu> {
    List<MenuVO> queryMenuByStaffNumber(String token);

    List<MenuDTO> queryMenuByRoleId(Integer roleId);

    List<MenuVO> menuHandler(List<Menu> menus);
}
