package com.flushbonading.cps.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.flushbonading.cps.entity.Menu;
import com.flushbonading.cps.entity.dto.MenuDTO;
import com.flushbonading.cps.entity.vo.MenuVO;
import com.flushbonading.cps.mapper.MenuMapper;
import com.flushbonading.cps.service.MenuService;
import com.flushbonading.cps.util.TokenUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
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
public class MenuServiceImpl extends ServiceImpl<MenuMapper, Menu> implements MenuService {

    /**
     * 菜单映射器
     */
    @Autowired
    MenuMapper menuMapper;
    @Autowired
    RedisTemplate<String, Object> redisTemplate;

    /**
     * 转化为给前端的形式
     *
     * @param token
     * @return
     */
    @Override
    public List<MenuVO> queryMenuByStaffNumber(String token) {
        String staffNumber = TokenUtils.getStaffNumber(token);
        List<MenuVO> menusVO = (List<MenuVO>) redisTemplate.opsForValue().get("menu:" + staffNumber);
        if (menusVO != null) {
            return menusVO;
        }
        List<Menu> menus = menuMapper.queryMenuByStaffNumber(staffNumber);
        menusVO = menuHandler(menus);
        redisTemplate.opsForValue().set("menu:" + staffNumber, menusVO);
        return menusVO;
    }

    @Override
    public List<MenuDTO> queryMenuByRoleId(Integer roleId) {
        List<Menu> allMenu = menuMapper.getAllMenu();
        List<Menu> menusByRoleId = menuMapper.getMenusByRoleId(roleId);
        List<MenuDTO> menuDTOs = new ArrayList<>();
        menuDTOHandler(allMenu, menusByRoleId, menuDTOs);

        List<MenuDTO> result = new ArrayList<>();
        for (MenuDTO menuDTO : menuDTOs) {
            String s = "" + menuDTO.getId().intValue();
            if (s.length() <= 1) {
                result.add(menuDTO);
            }
        }
        return result;
    }

    private void menuDTOHandler(List<Menu> allMenu, List<Menu> menusByRoleId, List<MenuDTO> menuDTOs) {
        int j = 0;
        for (int i = 0; i < allMenu.size(); i++) {
            if (allMenu.get(i).getParent().intValue() == 0) {
                j = i;
            }
            MenuDTO build = MenuDTO.builder()
                    .id(allMenu.get(i).getMenuId())
                    .label(allMenu.get(i).getMenuName())
                    .build();
            if (menusByRoleId.contains(allMenu.get(i))) {
                build.setChecked(true);
            }
            if (allMenu.get(i).getParent().intValue() != 0 && allMenu.get(i).getParent().intValue() == allMenu.get(j).getMenuId()) {
                List<MenuDTO> children = menuDTOs.get(j).getChildren();
                if (children == null) {
                    children = new ArrayList<>();
                }
                children.add(build);
                menuDTOs.get(j).setChildren(children);
            }
            menuDTOs.add(build);
        }

    }

    /**
     * 返回处理后的值
     *
     * @param menus menu类型的List
     * @return 处理后的值
     */
    @Override
    public List<MenuVO> menuHandler(List<Menu> menus) {
        List<MenuVO> menuVOs = new ArrayList<>();
        for (Menu menu : menus) {
            if (menu.getParent().intValue() == 0) {
                MenuVO menuVO = MenuVO.builder()
                        .menuId(menu.getMenuId())
                        .menuName(menu.getMenuName())
                        .icon(menu.getIcon())
                        .path(menu.getPath())
                        .children(getChildren(menu.getMenuId(), menus))
                        .build();
                menuVOs.add(menuVO);
            }
        }
        return menuVOs;
    }

    /**
     * 返回子元素
     *
     * @param parent 父元素id
     * @param menus  menu类型的List
     * @return 返回menuVo类型的List
     */
    private List<MenuVO> getChildren(Integer parent, List<Menu> menus) {
        List<MenuVO> menuVOs = new ArrayList<>();
        for (Menu menu : menus) {
            if (menu.getParent().intValue() == parent.intValue()) {
                MenuVO menuVO = MenuVO.builder()
                        .menuId(menu.getMenuId())
                        .path(menu.getPath())
                        .icon(menu.getIcon())
                        .menuName(menu.getMenuName())
                        .build();
                menuVOs.add(menuVO);
            }
        }
        if (menuVOs.size() > 0) {
            return menuVOs;
        }
        return null;
    }
}
