package com.flushbonading.cps;

import com.flushbonading.cps.entity.vo.MenuVO;
import com.flushbonading.cps.service.DiaryService;
import com.flushbonading.cps.service.EquipmentService;
import com.flushbonading.cps.service.MenuService;
import com.flushbonading.cps.service.ProductService;
import com.flushbonading.cps.service.impl.UserServiceImpl;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import java.util.List;

@SpringBootTest
class CpsApplicationTests {
    @Autowired
    ProductService productService;
    @Autowired
    EquipmentService equipmentService;
    @Autowired
    DiaryService diaryService;
    @Autowired
    UserServiceImpl userService;
    @Autowired
    MenuService menuService;

    @Test
    void contextLoads() {
        List<MenuVO> menu = menuService.queryMenuByStaffNumber("user");
        menu.forEach(System.out::println);
    }

    @Test
    void testStaddCounts() {
        Integer integer = equipmentService.staffCounts();
        System.out.println(integer);
    }

}
